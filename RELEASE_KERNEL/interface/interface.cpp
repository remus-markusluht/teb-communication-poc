#include "interface.h"
#include "../module/ia32/ia32.h"

namespace scan
{
	bool check_mask(
		const char* base,
		const char* pattern,
		const char* mask
	) {
		SPOOF_FUNC;

		for (; *mask; ++base, ++pattern, ++mask) {
			if (*mask == oxorany('x') && *base != *pattern) {
				return oxorany(false);
			}
		}

		return oxorany(true);
	};

	uintptr_t find_pattern(
		uintptr_t base_address,
		uint64_t size_of_address,
		const char* pattern,
		const char* mask
	) {
		SPOOF_FUNC;

		size_of_address = size_of_address - strlen(mask);

		for (size_t idx = 0; idx < size_of_address; ++idx) {
			if (check_mask(reinterpret_cast<const char*>(base_address + idx), pattern, mask)) {
				return base_address + idx;
			}
		}

		return oxorany(NULL);
	}

	
	void* split_memory(
		void* start,
		size_t size,
		const void* pattern
	) {
		auto module_start = static_cast<const unsigned char*>(start);
		auto pattern_start = static_cast<const unsigned char*>(pattern);

		for (uintptr_t idx = 0; idx < size - sizeof(pattern); ++idx)
		{
			size_t i = 0;
			for (; i < sizeof(pattern); ++i) {
				if (module_start[idx + i] != pattern_start[i])
					break;
			}

			if (i == sizeof(pattern)) return const_cast<unsigned char*>(&module_start[idx]);
		}

		return nullptr;
	}
	
}

NTSTATUS interface::setup() {
	SPOOF_FUNC;

	this->set_registry_key_path(E(L"\\Registry\\Machine\\SOFTWARE\\NVIDIA Corporation\\Partners"));
	auto status = this->GetRegistryValue(E(L"rax3"), this->client_id);
	if (status != true) {
		silence(E("[sonos::RegistrySetupProtocol!err] Failed to get Registry Value for 'upid'.\n"));
		return STATUS_FAIL_CHECK;
	}
	silence(E("[sonos::RegistrySetupProtocol] Retrieved client_id: %llu\n"), this->client_id);

	PEPROCESS Process;
	NTSTATUS pid_check = ps_lookup_process_by_process_id((HANDLE)this->client_id, &Process);
	if (NT_SUCCESS(pid_check)) {

	}
	else {
		BOOLEAN PidExists = FALSE;
		while (PidExists == FALSE) {
			NTSTATUS status = this->GetRegistryValue(E(L"rax3"), this->client_id);
			if (status != true) {
				return STATUS_FAIL_CHECK;
			}

			pid_check = ps_lookup_process_by_process_id((HANDLE)this->client_id, &Process);
			if (NT_SUCCESS(pid_check)) {
				PidExists = TRUE;
			}
		}
		ob_dereference_object(Process);
	}

	this->client_process =
		reinterpret_cast<PEPROCESS>(PROCESS::get_eprocess(this->client_id));
	if (!this->client_process) {
		silence(E("[sonos::RegistrySetupProtocol!err] Failed to get Client Process for client_id: %llu\n"), this->client_id);
		return STATUS_FAIL_CHECK;
	}
	silence(E("[sonos::RegistrySetupProtocol] Client process obtained: 0x%p\n"), this->client_process);

	this->ProcessBase = ps_get_process_section_base_address(this->client_process); // Update Process Base Address

	this->process_cr3.flags = PROCESS::get_process_cr3(
		reinterpret_cast<uintptr_t>(this->client_process));
	if (!this->process_cr3.flags) {
		silence(E("[sonos::RegistrySetupProtocol!err] Failed to get CR3 flags for client process: 0x%p\n"), this->client_process);
		return STATUS_FAIL_CHECK;
	}
	silence(E("[sonos::RegistrySetupProtocol] CR3 flags obtained: 0x%llx\n"), this->process_cr3.flags);

	status = this->GetRegistryValue(E(L"rax1"), this->TlsIndex);
	if (!status) {
		silence(E("[sonos::RegistrySetupProtocol!err] Failed to get Registry Value for 'tlsindex'.\n"));
		return STATUS_FAIL_CHECK;
	}
	silence(E("[sonos::RegistrySetupProtocol] Retrieved TlsIndex: %u\n"), this->TlsIndex);


	status = this->GetRegistryValue(E(L"rax2"), this->TEBAddress);
	if (!status) {
		silence(E("[sonos::RegistrySetupProtocol!err] Failed to get Registry Value for 'tebaddr'.\n"));
		return STATUS_FAIL_CHECK;
	}
	silence(E("[sonos::RegistrySetupProtocol] Retrieved TEB Address: 0x%p\n"), this->TEBAddress);

	this->ProcessDTB = CR3::GetCR3(this->ProcessBase);
	IA32::TEB rTeb{};
	auto pool = ex_allocate_pool(NonPagedPool, sizeof(IA32::TEB));
	if (!pool) {
		silence(E("[DebugReadTEB] Failed to allocate pool memory for TEB read.\n"));
		return STATUS_SUCCESS;
	}
	status = Read::ReadMemory(TEBAddress, pool, sizeof(IA32::TEB), this->ProcessDTB);
	if (!NT_SUCCESS(status)) {
		ex_free_pool_with_tag(pool, oxorany(0));
		return STATUS_SUCCESS;
	}
	memcpy(&rTeb, pool, sizeof(IA32::TEB));
	this->CommBufferCached = rTeb.TlsSlots[this->TlsIndex];
	ex_free_pool_with_tag(pool, oxorany(0));

	return STATUS_SUCCESS;
}


NTSTATUS interface::GetMEM(interface_thread::pcommargs out_request) {
	if (Read::ReadMemory(this->CommBufferCached, out_request, sizeof(interface_thread::commargs), this->ProcessDTB) != STATUS_SUCCESS) {
		return STATUS_FAIL_CHECK;
	}

	return STATUS_SUCCESS;
}

NTSTATUS interface::SendMEM(interface_thread::pcommargs request) {
	if (Write::WriteMemory(this->CommBufferCached, request, sizeof(interface_thread::commargs), this->ProcessDTB) != STATUS_SUCCESS) {
		return STATUS_FAIL_CHECK;
	}

	return STATUS_SUCCESS;
}

template <typename type>
bool interface::GetRegistryValue(const wchar_t* value_name, type& result_value) {
	UNICODE_STRING unicode_key_path = { oxorany(0) };
	UNICODE_STRING unicode_value_name = { oxorany(0) };
	RtlInitUnicodeString(&unicode_key_path, this->key_path);
	RtlInitUnicodeString(&unicode_value_name, value_name);

	OBJECT_ATTRIBUTES object_attributes = { oxorany(0) };
	InitializeObjectAttributes(&object_attributes, &unicode_key_path,
		OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	HANDLE key_handle = NULL;
	auto status = exports::zw_open_key(&key_handle, oxorany(KEY_READ), &object_attributes);
	if (status != STATUS_SUCCESS) {
		return false;
	}

	ULONG buffer_size = oxorany(sizeof(KEY_VALUE_PARTIAL_INFORMATION) + sizeof(type));
	auto key_value_info = (KEY_VALUE_PARTIAL_INFORMATION*)exports::ex_allocate_pool(NonPagedPool, buffer_size);
	if (!key_value_info) {
		exports::zw_close(key_handle);
		return false;
	}

	status = exports::zw_query_value_key(key_handle, &unicode_value_name, KeyValuePartialInformation, key_value_info, buffer_size, &buffer_size);
	if (status != STATUS_SUCCESS) {
		exports::ex_free_pool_with_tag(key_value_info, oxorany(0));
		exports::zw_close(key_handle);
		return false;
	}

	result_value = *reinterpret_cast<type*> (key_value_info->Data);
	exports::ex_free_pool_with_tag(key_value_info, oxorany(0));
	exports::zw_close(key_handle);

	return true;
}


bool interface::find_gadget(uintptr_t driver_base_address, uintptr_t* used_jmp_rcx_gadget)
{
	SPOOF_FUNC;

	uintptr_t current_executable_section = 0;
	uint64_t current_executable_section_size = 0;

	const auto& status = rwx::discover_next_executable_section(driver_base_address, &current_executable_section, &current_executable_section_size);
	if (current_executable_section == NULL || current_executable_section_size == NULL) {
		silence(E("[sonos::FindGadget] Failed to find an exeuctable(RWX) section in provided address\n"));
		return false;
	}
	dbgsilence(E("[sonos::Context] Executable Section found with (RWX) [%llx]"), current_executable_section);

	silence(E("[sonos::Context] Searching for unique JMP RCX Gadget under the RWX Page\n"));
	silence(E("[sonos::Context] This may take up to 1 Minute...\n"));
	auto jmp_rcx_gadget = scan::find_pattern(current_executable_section, current_executable_section_size, E("\xFF\xE1"), E("xx"));
	if (!jmp_rcx_gadget) {
		silence(E("[sonos::FindGadget] Failed to find JMP RCX Gadget Pattern under the provided section\n"));
		return false;
	}
	silence(E("[sonos::Context] Found a unique JMP RCX Gadget"));
	dbgsilence(E("[sonos::Context] JMP RCX [GADGET] (ndf) [%llx]"), jmp_rcx_gadget);

	*used_jmp_rcx_gadget = jmp_rcx_gadget;
	return TRUE;
}

NTSTATUS interface::create_gadget(uintptr_t driver_base_address, void* thread_function)
{
	SPOOF_FUNC;

	uintptr_t used_jmp_rcx_gadget = 0;
	auto status = find_gadget(driver_base_address, &used_jmp_rcx_gadget);
	if (used_jmp_rcx_gadget == FALSE) {
		silence(E("[sonos::Gadget] Failed to find jmp_rcx gadget\n"));
		return STATUS_FAIL_CHECK;
	}

	dbgsilence(E("[sonos::Gadget] JMP RCX [GADGET] (ndt) [%llx]"), used_jmp_rcx_gadget);

	silence(E("[sonos::Gadget] Creating SystemThread through NTOSKRNL"));
	status = ps_create_system_thread(
			&c_client->thread_handle,
			GENERIC_ALL,
			nullptr,
			nullptr,
			nullptr,
			PKSTART_ROUTINE(used_jmp_rcx_gadget),
			thread_function);

	silence(E("[sonos::Gadget] Created and Closing SystemThread Handle through NTOSKRNL"));
	zw_close(this->thread_handle);
	return STATUS_SUCCESS;
}

bool copy_thread_flags() {
	SPOOF_FUNC;

	silence(E("[sonos::KThread] Modifying KThread and Relative EThread Context data\n"));

	silence(E("[sonos::KThread] stage:1\n"));
	auto current_ethread = ps_get_current_thread();
	if (!current_ethread) {
		return false;
	}

	silence(E("[sonos::KThread] stage:2\n"));
	auto legit_ethread = get_system_thread();
	if (!legit_ethread) {
		return false;
	}

	silence(E("[sonos::KThread] stage:3\n"));
	current_ethread->Win32StartAddress = legit_ethread->Win32StartAddress;
	current_ethread->HideFromDebugger = true;

	silence(E("[sonos::KThread] stage:4\n"));
	auto current_kthread =
		reinterpret_cast<IA32::kthread*>(current_ethread);
	auto legit_kthread =
		reinterpret_cast<IA32::kthread*>(legit_ethread);

	silence(E("[sonos::KThread] stage:5\n"));
	current_kthread->Win32Thread = legit_kthread->Win32Thread;
	current_kthread->ThreadFlags = legit_kthread->ThreadFlags;
	current_kthread->Tag = legit_kthread->Tag;
	silence(E("[sonos::KThread] Modifying APC To Secondary module (1)\n"));
	current_kthread->KernelApcDisable = legit_kthread->KernelApcDisable;

	silence(E("[sonos::KThread] stage:6\n"));
	current_kthread->MiscFlags &= ~(1ul << oxorany(10)); // SystemThread
	current_kthread->MiscFlags &= ~(1ul << oxorany(4)); // AlertAble

	silence(E("[sonos::KThread] Modifying APC To Secondary module (2)\n"));
	current_kthread->MiscFlags &= ~(1ul << oxorany(14)); // ApcQueuable
	
	silence(E("[sonos::KThread] stage:7 - Finished all stages of KThread & EThread Context swapping\n"));
	ob_dereference_object(legit_ethread);
	return true;
}

interface c_client = { };
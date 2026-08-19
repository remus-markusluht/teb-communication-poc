#include "exports.h"

namespace exports {

	[[ nodiscard ]]
	void rtl_init_unicode_string(
		PUNICODE_STRING destination_string,
		PCWSTR source_string
	) {
		auto function_address = NTOS::find_export<addr_t>(E("RtlInitUnicodeString"));
		if (!function_address) {
			return;
		}

		using function_t = void* (
			PUNICODE_STRING destination_string,
			PCWSTR source_string
			);

		reinterpret_cast<function_t*>(function_address) (
			destination_string,
			source_string);
	}



















	LONG_PTR ob_dereference_object(PVOID ObjectHandle) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("ObfDereferenceObject"));
		if (!function_address) {
			return false;
		}

		using function_t = LONG_PTR(
			PVOID ObjectHandle
		);

		return reinterpret_cast<function_t*>(function_address)(ObjectHandle);
	}

	PPEB ps_get_process_peb(PEPROCESS Process) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsGetProcessPeb"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = PPEB(
			PEPROCESS Process
		);

		return reinterpret_cast<function_t*>(function_address)(Process);
	}

	BOOLEAN rtl_delete_element_generic_table_avl(PRTL_AVL_TABLE Table, PVOID Buffer) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("RtlDeleteElementGenericTableAvl"));
		if (!function_address) {
			return false;
		}

		using function_t = BOOLEAN(
			PRTL_AVL_TABLE Table, PVOID Buffer
		);

		return reinterpret_cast<function_t*>(function_address)(Table, Buffer);
	}

	PVOID rtl_lookup_element_generic_table_avl(PRTL_AVL_TABLE Table, PVOID Buffer) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("RtlLookupElementGenericTableAvl"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = PVOID(
			PRTL_AVL_TABLE Table, PVOID Buffer
		);

		return reinterpret_cast<function_t*>(function_address)(Table, Buffer);
	}

	BOOLEAN ex_acquire_exclusive_lite(PERESOURCE PiDDBLock, BOOL Wait) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("ExAcquireResourceExclusiveLite"));
		if (!function_address) {
			return false;
		}

		using function_t = BOOLEAN(
			PERESOURCE PiDDBLock, BOOL Wait
			);

		return reinterpret_cast<function_t*>(function_address)(PiDDBLock, Wait);
	}

	void ex_release_resource_lite(PERESOURCE Resource) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("ExReleaseResourceLite"));
		if (!function_address) {
			return;
		}

		using function_t = void(
			PERESOURCE Resource
		);

		return reinterpret_cast<function_t*>(function_address)(Resource);
	}

	PKTHREAD ke_get_current_thread() {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("KeGetCurrentThread"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = PKTHREAD(
			);
		return reinterpret_cast<function_t*>(function_address)();
	}

	IA32::ethread* ps_get_next_process_thread(PEPROCESS Process, PETHREAD Thread) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsGetNextProcessThread"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = IA32::ethread*(
			PEPROCESS Process, PETHREAD Thread
		);

		return reinterpret_cast<function_t*>(function_address)(Process, Thread);
	}

	void* ps_get_process_section_base_address(
		PEPROCESS Process
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsGetProcessSectionBaseAddress"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = void* (
			PEPROCESS Process
			);

		return reinterpret_cast<function_t*>(function_address)(Process);
	}

	NTSTATUS zw_query_system_information(
		SYSTEM_INFORMATION_CLASS SystemInformationClass,
		PVOID                    SystemInformation,
		ULONG                    SystemInformationLength,
		PULONG                   ReturnLength
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("ZwQuerySystemInformation"));

		if (!function_address) {
			return STATUS_UNSUCCESSFUL;
		}

		using function_t = NTSTATUS(
			SYSTEM_INFORMATION_CLASS,
			PVOID,
			ULONG,
			PULONG
		);

		return reinterpret_cast<function_t*>(function_address)(
			SystemInformationClass,
			SystemInformation,
			SystemInformationLength,
			ReturnLength
			);
	}

	void ke_query_system_time_precise(PLARGE_INTEGER CurrentTime) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("KeQuerySystemTimePrecise"));
		if (!function_address) {
			return;
		}

		using function_t = void(
			PLARGE_INTEGER CurrentTime
		);

		return reinterpret_cast<function_t*>(function_address)(
			CurrentTime
		);
	}

	PVOID mm_get_system_routine_address(
		PUNICODE_STRING SystemRoutineName
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("MmGetSystemRoutineAddress"));
		if (!function_address) {
			return {};
		}
		using function_t = PVOID(
			PUNICODE_STRING SystemRoutineName
		);
		return reinterpret_cast<function_t*>(function_address)(SystemRoutineName);
	}

	PEPROCESS io_get_current_process()
	{
		auto function_address = NTOS::find_export<addr_t>(E("IoGetCurrentProcess"));
		if (!function_address) {
			return {};
		}

		using function_t = PEPROCESS();

		return reinterpret_cast<function_t*>(function_address)();
	}

	NTSTATUS ps_lookup_process_by_process_id(HANDLE ProcessID, PEPROCESS* Process) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsLookupProcessByProcessId"));
		if (!function_address) {
			return STATUS_NOT_FOUND;
		}

		using function_t = NTSTATUS(
			HANDLE ProcessID,
			PEPROCESS* Process
		);

		return reinterpret_cast<function_t*>(function_address)(ProcessID, Process);
	}

	NTSTATUS ps_lookup_thread_by_thread_id(
		std::uint32_t ThreadId,
		IA32::ethread** Thread
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsLookupThreadByThreadId"));
		if (!function_address) {
			return {};
		}

		using function_t = NTSTATUS(
			HANDLE ThreadId,
			IA32::ethread** Thread
		);

		return reinterpret_cast<function_t*>(function_address)(
			reinterpret_cast<HANDLE>(ThreadId),
			Thread
			);
	}

	BOOLEAN ps_is_system_thread(
		IA32::ethread* Thread
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsIsSystemThread"));
		if (!function_address) {
			return {};
		}

		using function_t = BOOLEAN(
			IA32::ethread* Thread
		);

		return reinterpret_cast<function_t*>(function_address)(Thread);
	}

	IA32::ethread* ps_get_current_thread()
	{
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsGetCurrentThread"));
		if (!function_address) {
			return {};
		}

		using function_t = IA32::ethread* ();

		return reinterpret_cast<function_t*>(function_address)();
	}

	IA32::ethread* get_system_thread()
	{
		SPOOF_FUNC;

		for (std::uint32_t thread_id = oxorany(4); thread_id < oxorany(0xffff); thread_id += oxorany(4))
		{
			IA32::ethread* current_thread = nullptr;
			auto status = ps_lookup_thread_by_thread_id(thread_id, &current_thread);
			if (status != STATUS_SUCCESS) {
				continue;
			}

			auto current_kthread =
				reinterpret_cast<IA32::kthread*>(current_thread);
			if (!current_kthread) {
				continue;
			}

			if (!ps_is_system_thread(current_thread)) {
				continue;
			}

			const auto* thread = ps_get_current_thread();
			if (current_thread == thread) {
				continue;
			}

			//if ( !is_address_in_module_list( reinterpret_cast< std::uint64_t >( current_thread->StartAddress ) ) ) {
			//	continue;
			//}

			return current_thread;
		}

		return 0;
	}


	NTSTATUS ps_create_system_thread(
		PHANDLE ThreadHandle,
		ULONG DesiredAccess,
		POBJECT_ATTRIBUTES ObjectAttributes,
		HANDLE ProcessHandle,
		PCLIENT_ID ClientId,
		PKSTART_ROUTINE StartRoutine,
		void* StartContext
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("PsCreateSystemThread"));
		if (!function_address) {
			return {};
		}

		using function_t = NTSTATUS(
			PHANDLE ThreadHandle,
			ULONG DesiredAccess,
			POBJECT_ATTRIBUTES ObjectAttributes,
			HANDLE ProcessHandle,
			PCLIENT_ID ClientId,
			PKSTART_ROUTINE StartRoutine,
			void* StartContext
		);

		return reinterpret_cast<function_t*>(function_address)(
			ThreadHandle,
			DesiredAccess,
			ObjectAttributes,
			ProcessHandle,
			ClientId,
			StartRoutine,
			StartContext
			);
	}

	
	NTSTATUS zw_close(
		HANDLE handle
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("ZwClose"));
		if (!function_address) {
			return {};
		}

		using function_t = NTSTATUS(
			HANDLE handle
		);

		return reinterpret_cast<function_t*>(function_address)(
			handle
			);
	}

	
	NTSTATUS zw_open_key(
		PHANDLE key_handle,
		ACCESS_MASK desired_access,
		POBJECT_ATTRIBUTES object_attributes
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("ZwOpenKey"));
		if (!function_address) {
			return {};
		}

		using function_t = NTSTATUS(
			PHANDLE key_handle,
			ACCESS_MASK desired_access,
			POBJECT_ATTRIBUTES object_attributes
		);

		return reinterpret_cast<function_t*>(function_address)(
			key_handle,
			desired_access,
			object_attributes
			);
	}

	
	NTSTATUS zw_query_value_key(
		HANDLE key_handle,
		PUNICODE_STRING value_name,
		KEY_VALUE_INFORMATION_CLASS key_value_information_class,
		void* key_value_information,
		ULONG length,
		PULONG result_length
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("ZwQueryValueKey"));
		if (!function_address) {
			return {};
		}

		using function_t = NTSTATUS(
			HANDLE key_handle,
			PUNICODE_STRING value_name,
			KEY_VALUE_INFORMATION_CLASS key_value_information_class,
			void* key_value_information,
			ULONG length,
			PULONG result_length
		);

		return reinterpret_cast<function_t*>(function_address)(
			key_handle,
			value_name,
			key_value_information_class,
			key_value_information,
			length,
			result_length);
	}

	
	uintptr_t get_virtual_for_physical(
		uintptr_t physical_address
	) {
		SPOOF_FUNC;

		PHYSICAL_ADDRESS phys_addr{ };
		phys_addr.QuadPart = physical_address;

		auto function_address = NTOS::find_export<addr_t>(E("MmGetVirtualForPhysical"));
		if (!function_address) {
			return {};
		}

		using function_t = void* (
			PHYSICAL_ADDRESS physical_address
			);

		return reinterpret_cast<uintptr_t>(
			reinterpret_cast<function_t*>(function_address)(
				phys_addr
				));
	}

	void mm_unmap_io_space(
		PVOID BaseAddress,
		SIZE_T NumberOfBytes
	) {
		SPOOF_FUNC;
		auto function_address = NTOS::find_export<addr_t>(E("MmUnmapIoSpace"));
		if (!function_address) {
			return;
		}

		using function_t = void(
			PVOID BaseAddress,
			SIZE_T NumberOfBytes
			);

		return reinterpret_cast<function_t*>(function_address) (
			BaseAddress,
			NumberOfBytes);
	}

	void* mm_map_io_space_ex(
		PHYSICAL_ADDRESS PhysicalAddress,
		SIZE_T NumberOfBytes,
		ULONG Protect
	) {
		SPOOF_FUNC;
		auto function_address = NTOS::find_export<addr_t>(E("MmMapIoSpaceEx"));
		if (!function_address) {
			return {};
		}

		using function_t = void* (
			PHYSICAL_ADDRESS PhysicalAddress,
			SIZE_T NumberOfBytes,
			ULONG Protect
			);

		return reinterpret_cast<function_t*>(function_address) (
			PhysicalAddress,
			NumberOfBytes,
			Protect);
	}
	
	void* mm_map_io_space(
		uintptr_t physical_address,
		SIZE_T number_of_bytes
	) {
		SPOOF_FUNC;

		PHYSICAL_ADDRESS phys_addr{ physical_address };

		auto function_address = NTOS::find_export<addr_t>(E("MmMapIoSpace"));
		if (!function_address) {
			return {};
		}

		using function_t = void* (
			PHYSICAL_ADDRESS physical_address,
			SIZE_T number_of_bytes,
			MEMORY_CACHING_TYPE cache_type
			);

		return reinterpret_cast<function_t*>(function_address) (
			phys_addr,
			number_of_bytes,
			MmNonCached);
	}

	
	NTSTATUS mm_copy_memory(
		void* target_address,
		MM_COPY_ADDRESS source_address,
		SIZE_T number_of_bytes,
		ULONG flags,
		PSIZE_T number_of_bytes_transferred
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("MmCopyMemory"));
		if (!function_address) {
			return {};
		}

		using function_t = NTSTATUS(
			void* target_address,
			MM_COPY_ADDRESS source_address,
			SIZE_T number_of_bytes,
			ULONG falgs,
			PSIZE_T number_of_bytes_transferred
		);

		return reinterpret_cast<function_t*>(function_address) (
			target_address,
			source_address,
			number_of_bytes,
			flags,
			number_of_bytes_transferred);
	}

	
	void* map_io_space_ex(
		PHYSICAL_ADDRESS physical_address,
		SIZE_T number_of_bytes,
		ULONG protect
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("MmMapIoSpaceEx"));
		if (!function_address) {
			return {};
		}

		using function_t = void* (
			PHYSICAL_ADDRESS physical_address,
			SIZE_T number_of_bytes,
			ULONG protect
			);

		return reinterpret_cast<function_t*>(function_address) (
			physical_address,
			number_of_bytes,
			protect);
	}

	
	void* mm_allocate_contiguous_memory(
		SIZE_T NumberOfBytes
	) {
		SPOOF_FUNC;

		PHYSICAL_ADDRESS HighestAcceptableAddress{ MAXULONG64 };

		auto function_address = NTOS::find_export<addr_t>(E("MmAllocateContiguousMemory"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = void* (
			SIZE_T NumberOfBytes,
			PHYSICAL_ADDRESS HighestAcceptableAddress
			);

		return reinterpret_cast<function_t*>(function_address)(
			NumberOfBytes,
			HighestAcceptableAddress
			);
	};

	
	void mm_free_contiguous_memory(
		void* BaseAddress
	) {
		SPOOF_FUNC;
		
		auto function_address = NTOS::find_export<addr_t>(E("MmFreeContiguousMemory"));
		if (!function_address) {
			return;
		}

		using function_t = void(
			void* BaseAddress
			);

		reinterpret_cast<function_t*>(function_address)(BaseAddress);
	}

	
	PPHYSICAL_MEMORY_RANGE mm_get_physical_memory_ranges()
	{
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("MmGetPhysicalMemoryRanges"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = PPHYSICAL_MEMORY_RANGE(void);

		return reinterpret_cast<function_t*>(function_address)();
	}

	
	uintptr_t get_physical_address(
		uintptr_t virtual_address
	) {
		SPOOF_FUNC;

		auto function_address = NTOS::find_export<addr_t>(E("MmGetPhysicalAddress"));
		if (!function_address) {
			return {};
		}

		using function_t = PHYSICAL_ADDRESS(
			void* virtual_address
		);

		return reinterpret_cast<function_t*>(function_address)(
			reinterpret_cast<void*>(virtual_address)
			).QuadPart;
	}



	NTSTATUS mm_copy_virtual_memory(
		PEPROCESS source_process,
		void* source_address,
		PEPROCESS target_process,
		void* target_address,
		SIZE_T buffer_size,
		KPROCESSOR_MODE previous_mode,
		PSIZE_T return_size
	) {
		auto function_address = NTOS::find_export<addr_t>(E("MmCopyVirtualMemory"));
		if (!function_address) {
			return {};
		}

		using function_t = NTSTATUS(
			PEPROCESS source_process,
			void* source_address,
			PEPROCESS target_process,
			void* target_address,
			SIZE_T buffer_size,
			KPROCESSOR_MODE previous_mode,
			PSIZE_T return_size
		);

		return reinterpret_cast<function_t*>(function_address) (source_process,
			source_address,
			target_process,
			target_address,
			buffer_size,
			previous_mode,
			return_size);
	}

	
	void* ex_allocate_pool(
		POOL_TYPE pool_type,
		SIZE_T number_of_bytes
	) {
		auto function_address = NTOS::find_export<addr_t>(E("ExAllocatePool"));
		if (!function_address) {
			return nullptr;
		}

		using function_t = void* (
			POOL_TYPE pool_type,
			SIZE_T number_of_bytes
			);

		return reinterpret_cast<function_t*>(function_address)(
			pool_type,
			number_of_bytes);
	}

	
	void ex_free_pool_with_tag(
		void* base_address,
		ULONG tag
	) {
		auto function_address = NTOS::find_export<addr_t>(E("ExFreePoolWithTag"));
		if (!function_address) {
			return;
		}

		using function_t = void(
			void* base_address,
			ULONG tag
			);

		reinterpret_cast<function_t*>(function_address) (
			base_address,
			tag);
	}


	
	bool ps_get_process_exit_status(
		uintptr_t Process
	) {
		auto function_address = NTOS::find_export<addr_t>(E("PsGetProcessExitStatus"));
		if (!function_address) {
			return false;
		}

		using function_t = NTSTATUS(
			uintptr_t Process
		);

		return reinterpret_cast<function_t*>(function_address)(Process) == 0x103;
	}

	
	uintptr_t ps_initial_system_process() {
		auto function_address = NTOS::find_export<addr_t>(E("PsInitialSystemProcess"));
		if (!function_address) {
			return {};
		}

		return *reinterpret_cast<uintptr_t*>(function_address);
	}

	
	unicode_string_t* ps_query_full_process_image_name(
		std::uintptr_t process
	) {
		auto function_address = NTOS::find_export<addr_t>(E("SeLocateProcessImageName"));
		if (!function_address) return { };

		while (function_address[0x0] != 0xec
			|| function_address[0x1] != 0x28
			|| function_address[0x2] != 0xe8)
			function_address++;

		auto ps_rva{ &function_address[0x7] + *reinterpret_cast<std::int32_t*>(&function_address[0x3]) };
		if (!ps_rva)
			return {};

		while (ps_rva[0x0] != 0x0f
			|| ps_rva[0x1] != 0x85
			|| ps_rva[0x6] != 0x48)
			ps_rva++;

		return *reinterpret_cast<unicode_string_t**>
			(process + *reinterpret_cast<std::int32_t*>(&ps_rva[0x9]));
	}
}
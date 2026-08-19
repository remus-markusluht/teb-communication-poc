#include "../Includes.h"

bool handler() {
	const auto status = copy_thread_flags();
	if (!status) {
		silence(E("[sonos::Handler] Failed to spoof KThread data to another module\n"));
		return false;
	}
	silence(E("[sonos::Handler] KThread data of Handler Spoofed to a random module\n"));
	silence(E("[sonos::Handler] Starting Handler Thread Loop (primary driver will now be killed)\n"));
	
	while (true) {
		interface_thread::commargs args{};
		if (c_client->GetMEM(&args) != STATUS_SUCCESS) {
			c_client->setup();
		}

		if (!args.is_client_running) {
			continue;
		}

		if (args.is_operation_completed) {
			continue;
		}

		if (args.target_pid == NULL) {
			continue;
		}

		auto target_process = reinterpret_cast<PEPROCESS> (
			PROCESS::get_eprocess(args.target_pid));
		if (target_process == NULL || target_process == nullptr)
			continue;

		switch (args.operation_type) {
		case interface_thread::request_type::GETBASE:
		{
			args.address2 = (uintptr_t)ps_get_process_section_base_address(target_process);
			break;
		}
		case interface_thread::request_type::GETDTB:
		{
			args.address2 = CR3::GetCR3((PVOID)args.address);
			SavedCR3 = args.address2;
			break;
		}
		case interface_thread::request_type::READ:
		{
			if (args.address && args.buffer && args.is_client_running) {
				void* buf = ex_allocate_pool(oxorany(NonPagedPool), args.size);
				Read::ReadMemory((PVOID)args.address, buf, args.size, SavedCR3);
				Write::WriteMemory((PVOID)args.buffer, buf, args.size, c_client->ProcessDTB);
				ex_free_pool_with_tag(buf, oxorany(0));
			}
			break;
		}
		case interface_thread::request_type::GETMODULE:
		{
			if (args.buffer && args.is_client_running) {
				void* buf = ex_allocate_pool(oxorany(NonPagedPool), args.size);
				Read::ReadMemory((PVOID)args.buffer, buf, args.size, c_client->ProcessDTB);
				
				char* charBuf = (char*)buf;
				if (charBuf[args.size - 1] != '\0') {
					break;
				}
				args.address2 = moduleaddress::GetModuleAddress(target_process, charBuf);
				ex_free_pool_with_tag(buf, oxorany(0));
			}
			break;

		}
		case interface_thread::request_type::WRITE:
		{
			if (args.address && args.buffer && args.is_client_running) {
				void* buf = ex_allocate_pool(oxorany(NonPagedPool), args.size);
				Read::ReadMemory((PVOID)args.buffer, buf, args.size, c_client->ProcessDTB);
				Write::WriteMemory((PVOID)args.address, buf, args.size, SavedCR3);
				ex_free_pool_with_tag(buf, oxorany(0));
			}
			break;
		}
		case interface_thread::request_type::RESTORE:
		{
			break;
		}
		case interface_thread::request_type::KBOOT:
		{
			break;
		}
		case interface_thread::request_type::HEARTBEAT:
		{
			silence(E("Heartbeat Recieved!"));
			break;
		}
		}
		args.is_operation_completed = true;
		c_client->SendMEM(&args);
		if (args.operation_type == interface_thread::request_type::UNLOAD) {
			return false;
		}
	}
	return false;
}

NTSTATUS initialize() {
	SPOOF_FUNC;

    silence(E("[sonos::Initialize] Initialization of Driver Started.\n"));

	silence(E("[sonos::Initialize] Setting Registry KeyPath\n"));
	silence(E("[sonos::Initialize] Executing Registry Setup Protocol\n"));
	if (c_client->setup() != STATUS_SUCCESS) {
		silence(E("[sonos::Initialize!err] c_client.setup() Failed Validation\n"));
		return STATUS_FAIL_CHECK;
	}

	if (ntos_image_base == NULL) {
		silence(E("[sonos::Initialize!err] ntos_image_base is NULL\n"));
		return STATUS_FAIL_CHECK;
	}

	
	silence(E("[sonos::Initialize] Registering Gadget Interface\n"));
	if (c_client->create_gadget(ntos_image_base, handler) != STATUS_SUCCESS) {
		silence(E("[sonos::Initialize!err] c_client.create_gadget() Failed Validation\n"));
		return STATUS_FAIL_CHECK;
	}
	dbgsilence(E("[sonos::Context] created jmp rcx gadget [%llx]\n"), c_client->thread_handle);
	

	/*
	OBJECT_ATTRIBUTES objectAttributes;
	InitializeObjectAttributes(&objectAttributes, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
	PsCreateSystemThread(&c_client->thread_handle, THREAD_ALL_ACCESS, &objectAttributes, nullptr, nullptr, AThreadRoutine, NULL);
	*/
    return STATUS_SUCCESS;
}


NTSTATUS bootstrap() {
	SPOOF_FUNC;
	silence(E("[sonos::Bootstrap] Initialization of Bootstrapper Started.\n"));
	silence(E("[sonos::Bootstrap] Getting NTOSKRNL Image Base\n"));
	ntos_image_base = NTOS::get_ntos_base_address();
	if (ntos_image_base == NULL) {
		silence(E("[sonos::Bootstrap!err] Failed to get NTOSKRNL Image Base\n"));
		return STATUS_FAIL_CHECK;
	}
	kernel_base = ntos_image_base;
	dbgsilence(E("[sonos::Context] NTOS Image Base [%p]\n"), kernel_base);
	return STATUS_SUCCESS;
}

uintptr_t CombinePointer(uint32_t high, uint32_t low) {
	return (static_cast<uint64_t>(high) << oxorany(32)) | low;
}

void SplitPointer(uintptr_t pointer, uint32_t& high, uint32_t& low) {
	high = static_cast<uint32_t>(pointer >> oxorany(32)); // Get the high 32 bits
	low = static_cast<uint32_t>(pointer & oxorany(0xFFFFFFFF)); // Get the low 32 bits
}

NTSTATUS GenerateRandomString(OUT char* RandomString, IN ULONG Length)
{
	char* Dictionary = E("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	ULONG seed = MODULES::RandomNumber(); // Assuming RandomNumber() is defined and returns a valid seed
	unsigned int i;

	for (i = oxorany(0); i < Length - oxorany(1); i++) { // Keep one byte for the null terminator
		unsigned int r = RtlRandomEx(&seed) % (strlen(Dictionary)); // Get a random index
		RandomString[i] = Dictionary[r]; // Assign the random character
	}
	RandomString[Length - oxorany(1)] = '\0'; // Null-terminate the string

	return STATUS_SUCCESS;
}

void ConvertCharToWchar(const char* CharStr, wchar_t* WCharStr, size_t WCharStrSize)
{
	size_t i = 0;
	while (CharStr[i] != '\0' && i < WCharStrSize - 1) {
		WCharStr[i] = (wchar_t)CharStr[i];
		i++;
	}
	WCharStr[i] = L'\0'; // Null-terminate the wide string
}



NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);
	UNREFERENCED_PARAMETER(DriverObject);
	SPOOF_FUNC;
	
	/*
	UNICODE_STRING nReg{ };
	UNICODE_STRING nDrv{ };
	rtl_init_unicode_string(&nReg, E(L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\RmSvc"));
	rtl_init_unicode_string(&nDrv, E(L"\\Driver\\RmSvc"));

	uint32_t high, low;
	uintptr_t driverObjectPointer = reinterpret_cast<uintptr_t>(DriverObject);
	uintptr_t registryPathPointer = reinterpret_cast<uintptr_t>(RegistryPath);
	SplitPointer(driverObjectPointer, high, low);
	void* oDriverObject = reinterpret_cast<void*>(CombinePointer(high, low));
	UNREFERENCED_PARAMETER(DriverObject);
	SplitPointer(registryPathPointer, high, low);
	void* oRegistryPath = reinterpret_cast<void*>(CombinePointer(high, low));
	reinterpret_cast<PDRIVER_OBJECT>(oDriverObject)->DriverName = nDrv;
	UNREFERENCED_PARAMETER(RegistryPath);
	RtlFreeUnicodeString(&nReg);
	RtlFreeUnicodeString(&nDrv);
	*/

	silence(E("[sonos::DriverEntry] MainThread Mapped and In-Execution - Start of DriverEntry\n"));
	// silence(E("[sonos::DriverEntry] Entering Guarded Region\n"));
	// KeEnterGuardedRegion();



	NTSTATUS status = bootstrap();
	if (status != STATUS_SUCCESS) {
		silence(E("[sonos::DriverEntry] Global Bootstrapping Failed\n"));
		return STATUS_FAIL_CHECK;
	}
	
	status = initialize();
	if (status != STATUS_SUCCESS) {
		silence(E("[sonos::DriverEntry] Initialize Failed\n"));
		return STATUS_FAIL_CHECK;
	}
	
	// silence(E("[sonos::DriverEntry] Leaving Guarded Region\n"));
	// KeLeaveGuardedRegion();
	silence(E("[sonos::DriverEntry] MainThread Returning (status) - End of DriverEntry\n"));
	return status;
}
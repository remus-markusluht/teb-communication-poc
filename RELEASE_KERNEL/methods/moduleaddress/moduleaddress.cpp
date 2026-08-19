#include "moduleaddress.h"

_declspec(noinline) uintptr_t attach_process(uintptr_t process)
{
	auto current_thread = (uintptr_t)ke_get_current_thread();
	if (!current_thread)
		return oxorany(0);
	auto apc_state = *(uintptr_t*)(current_thread + oxorany(0x98));
	auto old_process = *(uintptr_t*)(apc_state + oxorany(0x20));
	*(uintptr_t*)(apc_state + oxorany(0x20)) = process;
	auto dir_table_base = *(uintptr_t*)(process + oxorany(0x28));
	__writecr3(dir_table_base);
	return old_process;
}

extern "C"
{
	NTKERNELAPI PPEB PsGetProcessPeb(IN PEPROCESS Process);
}

typedef struct _PEB_LDR_DATA {
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY ModuleListLoadOrder;
	LIST_ENTRY ModuleListMemoryOrder;
	LIST_ENTRY ModuleListInitOrder;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	BYTE Reserved1[16];
	PVOID Reserved2[10];
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef void(__stdcall* PPS_POST_PROCESS_INIT_ROUTINE)(void);

typedef struct _PEB {
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID Reserved3[2];
	PPEB_LDR_DATA Ldr;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID Reserved4[3];
	PVOID AtlThunkSListPtr;
	PVOID Reserved5;
	ULONG Reserved6;
	PVOID Reserved7;
	ULONG Reserved8;
	ULONG AtlThunkSListPtr32;
	PVOID Reserved9[45];
	BYTE Reserved10[96];
	PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
	BYTE Reserved11[128];
	PVOID Reserved12[1];
	ULONG SessionId;
} PEB, * PPEB;

typedef struct _LDR_DATA_TABLE_ENTRY
{
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    union
    {
        LIST_ENTRY HashLinks;
        PVOID SectionPointer;
    };
    ULONG CheckSum;
    union
    {
        ULONG TimeDateStamp;
        PVOID LoadedImports;
    };
    PVOID EntryPointActivationContext;
    PVOID PatchInformation;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

namespace moduleaddress {
	uintptr_t GetModuleAddress(PEPROCESS client, char* module_name) {
		SPOOF_FUNC;
		uintptr_t out = 0;
		uintptr_t o_process = 0;
		ANSI_STRING ansi_name;
		RtlInitAnsiString(&ansi_name, module_name);
		UNICODE_STRING compare_name;
		RtlAnsiStringToUnicodeString(&compare_name, &ansi_name, TRUE);
		o_process = attach_process((uintptr_t)client);
		if (!o_process)
			return STATUS_UNSUCCESSFUL;
		PPEB pPeb = ps_get_process_peb(client);
		if (pPeb)
		{
			PPEB_LDR_DATA pLdr = (PPEB_LDR_DATA)pPeb->Ldr;
			if (pLdr)
			{
				for (PLIST_ENTRY listEntry = (PLIST_ENTRY)pLdr->ModuleListLoadOrder.Flink;
					listEntry != &pLdr->ModuleListLoadOrder;
					listEntry = (PLIST_ENTRY)listEntry->Flink) {
					PLDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(listEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
					if (RtlCompareUnicodeString(&pEntry->BaseDllName, &compare_name, oxorany(TRUE)) == oxorany(0))
					{
						out = (uint64_t)pEntry->DllBase;
						break;
					}
				}
			}
		}
		attach_process(o_process);
		RtlFreeUnicodeString(&compare_name);
		ob_dereference_object(client);

		return out;
	}
}
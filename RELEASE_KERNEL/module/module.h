#pragma once
#include "../Includes.h"

using addr_t = unsigned char*;
using double_t = double;
using float_t = float;
using function_t = HANDLE(
    PEPROCESS Process
);

template <typename... Args>
void silence(PCSTR Msg, Args... args) {
    SPOOF_FUNC;
    if (DEBUGPRINT == TRUE) {
        DbgPrint(Msg, args...);
    }
    else {
        return;
    }
}

template <typename... Args>
void dbgsilence(PCSTR Msg, Args... args) {
    SPOOF_FUNC;
    if (ADVANCEDPRINT == TRUE) {
        DbgPrint(Msg, args...);
    }
    else {
        return;
    }
}

namespace crt {

    INT klower(int c);
    INT kwcscmp(const wchar_t* s1, const wchar_t* s2);
    CHAR* kLowerStr(CHAR* Str);
    SIZE_T kstrlen(const char* str);
    INT kstrncmp(const char* s1, const char* s2, size_t n);
    INT kstrcmp(const char* s1, const char* s2);
    INT kmemcmp(const void* s1, const void* s2, size_t n);

    /*
    CHAR* kstrstr(const char* s, const char* find);
    INT kMemcmp(const void* str1, const void* str2, size_t count);
    void* memcpy(void* dest, const void* src, size_t len);
    VOID* kmemset(void* dest, UINT8 c, size_t count);
    */

    char* stristr(const char* str1, const char* str2);
}

_declspec(noinline) auto resolve_address(
    uintptr_t Instruction,
    ULONG OffsetOffset,
    ULONG InstructionSize
) -> uintptr_t;

PVOID resolve_relative_address(
    _In_ PVOID Instruction,
    _In_ ULONG OffsetOffset,
    _In_ ULONG InstructionSize
);

namespace MODULES {

    auto get_kernel_export(uintptr_t Base, LPCSTR routine_name) -> UINT64;
    auto get_pattern(uintptr_t base, size_t range, const char* pattern, const char* mask) -> uintptr_t;
    auto find_pattern(uintptr_t Base, CHAR* Pattern, CHAR* Mask, char* Scan_Section = E(".text")) -> uintptr_t;
    PERESOURCE GetPsLoaded();
    UCHAR RandomNumber();

    /*
    PVOID FindPatternImage(
        PCHAR Base,
        PCHAR Pattern,
        PCHAR Mask
    );
    */

    // __declspec(noinline) auto find_ps_loaded_modules_list() -> PLIST_ENTRY;
    // _declspec(noinline) auto get_kernel_module_from_loaded_modules_list(const char* name) -> uintptr_t;

}

namespace NTOS {

    _declspec(noinline) auto get_ntos_base_address() -> uintptr_t;

    template <class type_t>
    type_t find_export(const char* export_name);
}

namespace PROCESS {
    uintptr_t attach(uintptr_t e_process);
    uintptr_t get_eprocess(uint32_t process_id);
    //uintptr_t get_eprocess(const wchar_t* process_name);
    uintptr_t get_process_cr3(uintptr_t e_process);
}
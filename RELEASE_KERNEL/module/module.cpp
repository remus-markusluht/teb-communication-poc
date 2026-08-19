#include "module.h"
#define IterateList(type, list_head, variable_name)                             \
    for (variable_name = (type*)((list_head)->Flink);                          \
         variable_name != (type*)(list_head);                                   \
         variable_name = (type*)variable_name->InLoadOrderLinks.Flink)

namespace crt
{
    INT klower(int c)
    {
        if (c >= 'A' && c <= 'Z')
            return c + 'a' - 'A';
        else
            return c;
    }

    INT kwcscmp(const wchar_t* s1, const wchar_t* s2)
    {
        while (*s1 == *s2++)
            if (*s1++ == '\0')
                return (0);
        /* XXX assumes wchar_t = int */
        return (*(const unsigned int*)s1 - *(const unsigned int*)--s2);
    }

    CHAR* kLowerStr(CHAR* Str)
    {
        for (CHAR* S = Str; *S; ++S)
        {
            *S = (CHAR)klower(*S);
        }
        return Str;
    }

    SIZE_T kstrlen(const char* str)
    {
        const char* s;
        for (s = str; *s; ++s);
        return (s - str);
    }

    INT kstrncmp(const char* s1, const char* s2, size_t n)
    {
        if (n == 0)
            return (0);
        do {
            if (*s1 != *s2++)
                return (*(unsigned char*)s1 - *(unsigned char*)--s2);
            if (*s1++ == 0)
                break;
        } while (--n != 0);
        return (0);
    }

    INT kstrcmp(const char* s1, const char* s2)
    {
        while (*s1 == *s2++)
            if (*s1++ == 0)
                return (0);
        return (*(unsigned char*)s1 - *(unsigned char*)--s2);
    }

    INT kmemcmp(const void* s1, const void* s2, size_t n)
    {
        const unsigned char* p1 = (const unsigned char*)s1;
        const unsigned char* end1 = p1 + n;
        const unsigned char* p2 = (const unsigned char*)s2;
        int                   d = 0;
        for (;;) {
            if (d || p1 >= end1) break;
            d = (int)*p1++ - (int)*p2++;
            if (d || p1 >= end1) break;
            d = (int)*p1++ - (int)*p2++;
            if (d || p1 >= end1) break;
            d = (int)*p1++ - (int)*p2++;
            if (d || p1 >= end1) break;
            d = (int)*p1++ - (int)*p2++;
        }
        return d;
    }

    /*
    CHAR* kstrstr(const char* s, const char* find)
    {
        char c, sc;
        size_t len;
        if ((c = *find++) != 0)
        {
            len = kstrlen(find);
            do
            {
                do
                {
                    if ((sc = *s++) == 0)
                    {
                        return (NULL);
                    }
                } while (sc != c);
            } while (kstrncmp(s, find, len) != 0);
            s--;
        }
        return ((char*)s);
    }

    INT kMemcmp(const void* str1, const void* str2, size_t count)
    {
        register const unsigned char* s1 = (const unsigned char*)str1;
        register const unsigned char* s2 = (const unsigned char*)str2;
        while (count-- > 0)
        {
            if (*s1++ != *s2++)
                return s1[-1] < s2[-1] ? -1 : 1;
        }
        return 0;
    }

    void* memcpy(void* dest, const void* src, size_t len)
    {
        char* d = (char*)dest;
        const char* s = (const char*)src;
        while (len--)
            *d++ = *s++;
        return dest;
    }

    VOID* kmemset(void* dest, UINT8 c, size_t count)
    {
        size_t blockIdx;
        size_t blocks = count >> 3;
        size_t bytesLeft = count - (blocks << 3);
        UINT64 cUll =
            c
            | (((UINT64)c) << oxorany(8))
            | (((UINT64)c) << oxorany(16))
            | (((UINT64)c) << oxorany(24))
            | (((UINT64)c) << oxorany(32))
            | (((UINT64)c) << oxorany(40))
            | (((UINT64)c) << oxorany(48))
            | (((UINT64)c) << oxorany(56));

        UINT64* destPtr8 = (UINT64*)dest;
        for (blockIdx = oxorany(0); blockIdx < blocks; blockIdx++) destPtr8[blockIdx] = cUll;

        if (!bytesLeft) return dest;

        blocks = bytesLeft >> oxorany(2);
        bytesLeft = bytesLeft - (blocks << oxorany(2));

        UINT32* destPtr4 = (UINT32*)&destPtr8[blockIdx];
        for (blockIdx = 0; blockIdx < blocks; blockIdx++) destPtr4[blockIdx] = (UINT32)cUll;

        if (!bytesLeft) return dest;

        blocks = bytesLeft >> 1;
        bytesLeft = bytesLeft - (blocks << oxorany(1));

        UINT16* destPtr2 = (UINT16*)&destPtr4[blockIdx];
        for (blockIdx = 0; blockIdx < blocks; blockIdx++) destPtr2[blockIdx] = (UINT16)cUll;

        if (!bytesLeft) return dest;

        UINT8* destPtr1 = (UINT8*)&destPtr2[blockIdx];
        for (blockIdx = 0; blockIdx < bytesLeft; blockIdx++) destPtr1[blockIdx] = (UINT8)cUll;

        return dest;
    }
    */

    char* stristr(const char* str1, const char* str2) {
        const char* p1 = str1;
        const char* p2 = str2;
        const char* r = *p2 == 0 ? str1 : 0;

        while (*p1 != 0 && *p2 != 0)
        {
            if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
            {
                if (r == 0)
                {
                    r = p1;
                }

                p2++;
            }
            else
            {
                p2 = str2;
                if (r != 0)
                {
                    p1 = r + 1;
                }

                if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
                {
                    r = p1;
                    p2++;
                }
                else
                {
                    r = 0;
                }
            }

            p1++;
        }

        return *p2 == 0 ? (char*)r : 0;
    }
}

_declspec(noinline) auto resolve_address(
    uintptr_t Instruction,
    ULONG OffsetOffset,
    ULONG InstructionSize) -> uintptr_t
{
    SPOOF_FUNC;

    LONG RipOffset = *(PLONG)(Instruction + OffsetOffset);
    auto ResolvedAddr = (
        Instruction +
        InstructionSize +
        RipOffset);

    return ResolvedAddr;
}

PVOID resolve_relative_address(
    _In_ PVOID Instruction,
    _In_ ULONG OffsetOffset,
    _In_ ULONG InstructionSize
)
{
    ULONG_PTR Instr = (ULONG_PTR)Instruction;
    LONG RipOffset = *(PLONG)(Instr + OffsetOffset);
    PVOID ResolvedAddr = (PVOID)(Instr + InstructionSize + RipOffset);

    return ResolvedAddr;
}


namespace MODULES {
    UCHAR RandomNumber() {
        UNICODE_STRING RoutineName = RTL_CONSTANT_STRING(L"RtlRandom");
        auto cRtlRandom = reinterpret_cast<decltype(&RtlRandomEx)>(mm_get_system_routine_address(&RoutineName));

        ULONG Seed = oxorany(5216799);
        ULONG Rand = cRtlRandom(&Seed) % oxorany(100);

        UCHAR RandInt = oxorany(0);

        if (Rand >= oxorany(101) || Rand <= -1)
            RandInt = oxorany(72);

        return (UCHAR)(Rand);
    }

    auto get_kernel_export(uintptr_t Base, LPCSTR routine_name) -> UINT64
    {
        SPOOF_FUNC;

        if (!Base) return NULL;

        PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)(Base);
        if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
            return 0;

        PIMAGE_NT_HEADERS64 ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS64>((UINT64)(Base)+dosHeader->e_lfanew);

        UINT32 exportsRva = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        if (!exportsRva)
            return 0;

        PIMAGE_EXPORT_DIRECTORY exports = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>((UINT64)(Base)+exportsRva);
        UINT32* nameRva = reinterpret_cast<UINT32*>((UINT64)(Base)+exports->AddressOfNames);

        for (UINT32 i = oxorany(0); i < exports->NumberOfNames; ++i)
        {
            CHAR* func = reinterpret_cast<CHAR*>((UINT64)(Base)+nameRva[i]);
            if (crt::kstrcmp(func, routine_name) == oxorany(0))
            {
                UINT32* funcRva = (UINT32*)((UINT64)(Base)+exports->AddressOfFunctions);
                UINT16* ordinalRva = (UINT16*)((UINT64)(Base)+exports->AddressOfNameOrdinals);

                return (UINT64)(Base)+funcRva[ordinalRva[i]];
            }
        }
        return 0;
    }

    auto get_pattern(uintptr_t base, size_t range, const char* pattern, const char* mask) -> uintptr_t
    {
        SPOOF_FUNC;

        const auto check_mask = [](const char* base, const char* pattern, const char* mask) -> bool
            {
                for (; *mask; ++base, ++pattern, ++mask)
                {
                    if (*mask == 'x' && *base != *pattern)
                    {
                        return false;
                    }
                }

                return true;
            };

        range = range - crt::kstrlen(mask);

        for (size_t i = oxorany(0); i < range; ++i)
        {
            if (check_mask((const char*)base + i, pattern, mask))
            {
                return base + i;
            }
        }

        return NULL;
    }

    auto find_pattern(uintptr_t Base, CHAR* Pattern, CHAR* Mask, char* Scan_Section) -> uintptr_t
    {
        SPOOF_FUNC;

        IMAGE_NT_HEADERS* Headers{ (PIMAGE_NT_HEADERS)(Base + ((PIMAGE_DOS_HEADER)Base)->e_lfanew) };
        IMAGE_SECTION_HEADER* Sections{ IMAGE_FIRST_SECTION(Headers) };

        for (auto i = 0; i < Headers->FileHeader.NumberOfSections; ++i)
        {
            IMAGE_SECTION_HEADER* Section{ &Sections[i] };

            if (!crt::kmemcmp(Section->Name, Scan_Section, crt::kstrlen(Scan_Section)) || !crt::kmemcmp(Section->Name, E("PAGE"), oxorany(4)))
            {
                const auto match = get_pattern(Base + Section->VirtualAddress, Section->Misc.VirtualSize, Pattern, Mask);

                if (match) {
                    return (match);
                }
            }
        }

        return 0;
    }

    PERESOURCE GetPsLoaded() {
        ERESOURCE PsLoadedModuleResource;

        /* I know this is really retarded, I couldnt find any other way to use static encrypted strings with UNICODE_STRING/RTL */
        UNICODE_STRING routineName;
        routineName.Buffer = (PWSTR)E(L"PsLoadedModuleResource");
        routineName.Length = (USHORT)(wcslen(E(L"PsLoadedModuleResource")) * sizeof(WCHAR));
        routineName.MaximumLength = (USHORT)((wcslen(E(L"PsLoadedModuleResource")) + 1) * sizeof(WCHAR));

        auto cPsLoadedModuleResource = reinterpret_cast<decltype(&PsLoadedModuleResource)>(mm_get_system_routine_address(&routineName));
        return cPsLoadedModuleResource;
    }

}

namespace NTOS {

    _declspec(noinline) auto get_ntos_base_address() -> uintptr_t{
        SPOOF_FUNC;

        typedef unsigned char uint8_t;
        auto Idt_base = reinterpret_cast<uintptr_t>(KeGetPcr()->IdtBase);
        auto align_page = *reinterpret_cast<uintptr_t*>(Idt_base + oxorany(4)) >> oxorany(0xc) << oxorany(0xc);

        for (; align_page; align_page -= PAGE_SIZE)
        {
            for (int index = oxorany(0); index < PAGE_SIZE - oxorany(0x7); index++)
            {
                auto current_address = static_cast<intptr_t>(align_page) + index;

                if (*reinterpret_cast<uint8_t*>(current_address) == oxorany(0x48)
                    && *reinterpret_cast<uint8_t*>(current_address + oxorany(1)) == oxorany(0x8D)
                    && *reinterpret_cast<uint8_t*>(current_address + oxorany(2)) == oxorany(0x1D)
                    && *reinterpret_cast<uint8_t*>(current_address + oxorany(6)) == oxorany(0xFF)) //48 8d 1D ?? ?? ?? FF
                {
                    // rva our virtual address lol
                    auto Ntosbase = resolve_address(current_address, oxorany(3), oxorany(7));
                    if (!((UINT64)Ntosbase & oxorany(0xfff)))
                    {
                        return Ntosbase;
                    }
                }
            }
        }
        return 0;
    }

    template<class type_t>
    type_t find_export(const char* export_name) {
        SPOOF_FUNC;

        auto NTOS = ntos_image_base;
        if (NTOS == NULL) {
            NTOS = NTOS::get_ntos_base_address();
            ntos_image_base = NTOS;
            kernel_base = NTOS;
        }
        auto dos_header = reinterpret_cast<dos_header_t*>(NTOS);
        if (!dos_header->is_valid()) {
            return nullptr;  // Return nullptr on failure instead of `false`.
        }

        auto m_nt_header = reinterpret_cast<nt_headers_t*>(reinterpret_cast<uint64_t>(dos_header) + dos_header->m_lfanew);
        if (!m_nt_header->is_valid()) {
            return nullptr;  // Return nullptr on failure instead of `false`.
        }

        auto library{ reinterpret_cast<int8_t*>(dos_header) };
        auto export_directory =
            reinterpret_cast<export_directory_t*>(NTOS + m_nt_header->m_export_table.m_virtual_address);
        if (!export_directory->m_address_of_functions
            || !export_directory->m_address_of_names
            || !export_directory->m_address_of_names_ordinals) {
            return nullptr;  // Return nullptr on failure instead of an empty object.
        }

        auto names{ reinterpret_cast<int32_t*>(library + export_directory->m_address_of_names) };
        auto functions{ reinterpret_cast<int32_t*>(library + export_directory->m_address_of_functions) };
        auto ordinals{ reinterpret_cast<int16_t*>(library + export_directory->m_address_of_names_ordinals) };

        for (int32_t i = 0; i < export_directory->m_number_of_names; i++) {
            auto current_name{ library + names[i] };
            auto current_function{ library + functions[ordinals[i]] };


            if (!strcmp(export_name, reinterpret_cast<char*>(current_name)))
                return reinterpret_cast<type_t>(current_function);
        }
        return nullptr;  // Return nullptr on failure instead of 0.
    }
}

namespace PROCESS {
    uintptr_t attach(uintptr_t e_process)
    {
        SPOOF_FUNC;

        auto current_thread = __readgsqword(oxorany(0x188));
        if (!current_thread)
            return 0;

        auto apc_state = *(uintptr_t*)(current_thread + oxorany(0x98));
        auto old_process = *(uintptr_t*)(apc_state + oxorany(0x20));
        *(uintptr_t*)(apc_state + oxorany(0x20)) = e_process;

        auto dir_table_base = *(uintptr_t*)(e_process + oxorany(0x28));
        __writecr3(dir_table_base);

        return old_process;
    }

    uintptr_t get_eprocess(uint32_t process_id) {
        SPOOF_FUNC;

        static auto KeCapturePersistentThreadState_t = NTOS::find_export<addr_t>(E("KeCapturePersistentThreadState"));
        if (KeCapturePersistentThreadState_t == NULL) {
            return 0;
        }

        while (KeCapturePersistentThreadState_t[oxorany(0x0)] != oxorany(0x20)
            || KeCapturePersistentThreadState_t[oxorany(0x1)] != oxorany(0x48)
            || KeCapturePersistentThreadState_t[oxorany(0x2)] != oxorany(0x8d))
            KeCapturePersistentThreadState_t++;
        auto PsActiveProcessHead = *reinterpret_cast<list_entry_t**>
            (&KeCapturePersistentThreadState_t[oxorany(0x8)] + *reinterpret_cast<int32_t*>(&KeCapturePersistentThreadState_t[oxorany(0x4)]));

        auto process_list_head = PsActiveProcessHead;
        if (!process_list_head) {
            return 0;
        }
        auto PsInitialSystemProcess_t = NTOS::find_export<addr_t>(E("PsInitialSystemProcess"));
        if (PsInitialSystemProcess_t == NULL) {
            return 0;
        }

        auto PsInitialSystemProcess = *reinterpret_cast<uintptr_t*>(PsInitialSystemProcess_t);
        const auto link_va =
            reinterpret_cast<addr_t>(process_list_head) -
            PsInitialSystemProcess;
        if (!link_va) {
            return 0;
        }

        for (auto flink = process_list_head->m_flink; flink; flink = flink->m_flink)
        {
            const auto next_eprocess = reinterpret_cast<addr_t>(flink) - link_va;
            if (!next_eprocess) {
                continue;
            }

            auto PsGetProcessId_t = NTOS::find_export<addr_t>(E("PsGetProcessId"));
            if (!PsGetProcessId_t) {
                return 0;
            }

            const auto next_process_id = reinterpret_cast<uint32_t>(reinterpret_cast<function_t*>(PsGetProcessId_t)(reinterpret_cast<PEPROCESS>(next_eprocess)));
            if (next_process_id == process_id) {
                return next_eprocess;
            }
        }

        return 0;
    }

    uintptr_t get_eprocess(const wchar_t* process_name)
    {
        static auto KeCapturePersistentThreadState_t = NTOS::find_export<addr_t>(E("KeCapturePersistentThreadState"));
        if (KeCapturePersistentThreadState_t == NULL) {
            return 0;
        }

        while (KeCapturePersistentThreadState_t[oxorany(0x0)] != oxorany(0x20)
            || KeCapturePersistentThreadState_t[oxorany(0x1)] != oxorany(0x48)
            || KeCapturePersistentThreadState_t[oxorany(0x2)] != oxorany(0x8d))
            KeCapturePersistentThreadState_t++;
        auto PsActiveProcessHead = *reinterpret_cast<list_entry_t**>
            (&KeCapturePersistentThreadState_t[oxorany(0x8)] + *reinterpret_cast<int32_t*>(&KeCapturePersistentThreadState_t[oxorany(0x4)]));

        auto process_list_head = PsActiveProcessHead;
        if (!process_list_head) {
            return 0;
        }

        const auto linkage_va =
            reinterpret_cast<addr_t>(process_list_head) -
            exports::ps_initial_system_process();
        if (!linkage_va) {
            return 0;
        }

        for (auto flink = process_list_head->m_flink; flink; flink = flink->m_flink)
        {
            const auto next_eprocess = reinterpret_cast<addr_t>(flink) - linkage_va;
            if (!next_eprocess || !exports::ps_get_process_exit_status(next_eprocess)) {
                continue;
            }

            auto unicode_name{ exports::ps_query_full_process_image_name(next_eprocess) };
            if (!unicode_name->m_buffer
                || !unicode_name->m_length
                || !unicode_name->m_maximum_length)
                continue;

            if (wcscmp(unicode_name->m_buffer, process_name))
            {
                return next_eprocess;
            }
        }

        return 0;
    }

    uintptr_t get_process_cr3(uintptr_t e_process) {
        SPOOF_FUNC;

        static auto function_address =
            NTOS::find_export< addr_t >(E("KeCapturePersistentThreadState"));
        if (!function_address) {
            return 0;
        }

        while (function_address[oxorany(0x0)] != oxorany(0x48)
            || function_address[oxorany(0x1)] != oxorany(0x8b)
            || function_address[oxorany(0x2)] != oxorany(0x48))
            function_address++;

        return *reinterpret_cast<uintptr_t*>
            (e_process + *reinterpret_cast<int8_t*>(&function_address[oxorany(0x3)]));
    }
};
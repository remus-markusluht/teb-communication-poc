#pragma once
#include <stdint.h>
#include <ntddmou.h>
#include <ntddk.h>
#include <ntifs.h>
#include <minwindef.h>

typedef struct _MI_ACTIVE_PFN
{
    union
    {
        struct
        {
            struct /* bitfield */
            {
                /* 0x0000 */ unsigned __int64 Tradable : 1; /* bit position: 0 */
                /* 0x0000 */ unsigned __int64 NonPagedBuddy : 43; /* bit position: 1 */
            }; /* bitfield */
        } /* size: 0x0008 */ Leaf;
        struct
        {
            struct /* bitfield */
            {
                /* 0x0000 */ unsigned __int64 Tradable : 1; /* bit position: 0 */
                /* 0x0000 */ unsigned __int64 WsleAge : 3; /* bit position: 1 */
                /* 0x0000 */ unsigned __int64 OldestWsleLeafEntries : 10; /* bit position: 4 */
                /* 0x0000 */ unsigned __int64 OldestWsleLeafAge : 3; /* bit position: 14 */
                /* 0x0000 */ unsigned __int64 NonPagedBuddy : 43; /* bit position: 17 */
            }; /* bitfield */
        } /* size: 0x0008 */ PageTable;
        /* 0x0000 */ unsigned __int64 EntireActiveField;
    }; /* size: 0x0008 */
} MI_ACTIVE_PFN, * PMI_ACTIVE_PFN; /* size: 0x0008 */

typedef struct _MMPTE_HARDWARE
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
        /* 0x0000 */ unsigned __int64 Dirty1 : 1; /* bit position: 1 */
        /* 0x0000 */ unsigned __int64 Owner : 1; /* bit position: 2 */
        /* 0x0000 */ unsigned __int64 WriteThrough : 1; /* bit position: 3 */
        /* 0x0000 */ unsigned __int64 CacheDisable : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned __int64 Accessed : 1; /* bit position: 5 */
        /* 0x0000 */ unsigned __int64 Dirty : 1; /* bit position: 6 */
        /* 0x0000 */ unsigned __int64 LargePage : 1; /* bit position: 7 */
        /* 0x0000 */ unsigned __int64 Global : 1; /* bit position: 8 */
        /* 0x0000 */ unsigned __int64 CopyOnWrite : 1; /* bit position: 9 */
        /* 0x0000 */ unsigned __int64 Unused : 1; /* bit position: 10 */
        /* 0x0000 */ unsigned __int64 Write : 1; /* bit position: 11 */
        /* 0x0000 */ unsigned __int64 PageFrameNumber : 40; /* bit position: 12 */
        /* 0x0000 */ unsigned __int64 ReservedForSoftware : 4; /* bit position: 52 */
        /* 0x0000 */ unsigned __int64 WsleAge : 4; /* bit position: 56 */
        /* 0x0000 */ unsigned __int64 WsleProtection : 3; /* bit position: 60 */
        /* 0x0000 */ unsigned __int64 NoExecute : 1; /* bit position: 63 */
    }; /* bitfield */
} MMPTE_HARDWARE, * PMMPTE_HARDWARE; /* size: 0x0008 */

typedef struct _MMPTE_PROTOTYPE
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
        /* 0x0000 */ unsigned __int64 DemandFillProto : 1; /* bit position: 1 */
        /* 0x0000 */ unsigned __int64 HiberVerifyConverted : 1; /* bit position: 2 */
        /* 0x0000 */ unsigned __int64 ReadOnly : 1; /* bit position: 3 */
        /* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
        /* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
        /* 0x0000 */ unsigned __int64 Combined : 1; /* bit position: 11 */
        /* 0x0000 */ unsigned __int64 Unused1 : 4; /* bit position: 12 */
        /* 0x0000 */ __int64 ProtoAddress : 48; /* bit position: 16 */
    }; /* bitfield */
} MMPTE_PROTOTYPE, * PMMPTE_PROTOTYPE; /* size: 0x0008 */

typedef struct _MMPTE_SOFTWARE
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
        /* 0x0000 */ unsigned __int64 PageFileReserved : 1; /* bit position: 1 */
        /* 0x0000 */ unsigned __int64 PageFileAllocated : 1; /* bit position: 2 */
        /* 0x0000 */ unsigned __int64 ColdPage : 1; /* bit position: 3 */
        /* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
        /* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
        /* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
        /* 0x0000 */ unsigned __int64 PageFileLow : 4; /* bit position: 12 */
        /* 0x0000 */ unsigned __int64 UsedPageTableEntries : 10; /* bit position: 16 */
        /* 0x0000 */ unsigned __int64 ShadowStack : 1; /* bit position: 26 */
        /* 0x0000 */ unsigned __int64 Unused : 5; /* bit position: 27 */
        /* 0x0000 */ unsigned __int64 PageFileHigh : 32; /* bit position: 32 */
    }; /* bitfield */
} MMPTE_SOFTWARE, * PMMPTE_SOFTWARE; /* size: 0x0008 */

typedef struct _MMPTE_TIMESTAMP
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned __int64 MustBeZero : 1; /* bit position: 0 */
        /* 0x0000 */ unsigned __int64 Unused : 3; /* bit position: 1 */
        /* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
        /* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
        /* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
        /* 0x0000 */ unsigned __int64 PageFileLow : 4; /* bit position: 12 */
        /* 0x0000 */ unsigned __int64 Reserved : 16; /* bit position: 16 */
        /* 0x0000 */ unsigned __int64 GlobalTimeStamp : 32; /* bit position: 32 */
    }; /* bitfield */
} MMPTE_TIMESTAMP, * PMMPTE_TIMESTAMP; /* size: 0x0008 */

typedef struct _MMPTE_TRANSITION
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
        /* 0x0000 */ unsigned __int64 Write : 1; /* bit position: 1 */
        /* 0x0000 */ unsigned __int64 Spare : 1; /* bit position: 2 */
        /* 0x0000 */ unsigned __int64 IoTracker : 1; /* bit position: 3 */
        /* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
        /* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
        /* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
        /* 0x0000 */ unsigned __int64 PageFrameNumber : 40; /* bit position: 12 */
        /* 0x0000 */ unsigned __int64 Unused : 12; /* bit position: 52 */
    }; /* bitfield */
} MMPTE_TRANSITION, * PMMPTE_TRANSITION; /* size: 0x0008 */

typedef struct _MMPTE_SUBSECTION
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
        /* 0x0000 */ unsigned __int64 Unused0 : 3; /* bit position: 1 */
        /* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
        /* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
        /* 0x0000 */ unsigned __int64 ColdPage : 1; /* bit position: 11 */
        /* 0x0000 */ unsigned __int64 Unused1 : 3; /* bit position: 12 */
        /* 0x0000 */ unsigned __int64 ExecutePrivilege : 1; /* bit position: 15 */
        /* 0x0000 */ __int64 SubsectionAddress : 48; /* bit position: 16 */
    }; /* bitfield */
} MMPTE_SUBSECTION, * PMMPTE_SUBSECTION; /* size: 0x0008 */

typedef struct _MMPTE_LIST
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
        /* 0x0000 */ unsigned __int64 OneEntry : 1; /* bit position: 1 */
        /* 0x0000 */ unsigned __int64 filler0 : 2; /* bit position: 2 */
        /* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
        /* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
        /* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
        /* 0x0000 */ unsigned __int64 filler1 : 16; /* bit position: 12 */
        /* 0x0000 */ unsigned __int64 NextEntry : 36; /* bit position: 28 */
    }; /* bitfield */
} MMPTE_LIST, * PMMPTE_LIST; /* size: 0x0008 */

typedef struct _MMPTE
{
    union
    {
        union
        {
            /* 0x0000 */ unsigned __int64 Long;
            /* 0x0000 */ volatile unsigned __int64 VolatileLong;
            /* 0x0000 */ struct _MMPTE_HARDWARE Hard;
            /* 0x0000 */ struct _MMPTE_PROTOTYPE Proto;
            /* 0x0000 */ struct _MMPTE_SOFTWARE Soft;
            /* 0x0000 */ struct _MMPTE_TIMESTAMP TimeStamp;
            /* 0x0000 */ struct _MMPTE_TRANSITION Trans;
            /* 0x0000 */ struct _MMPTE_SUBSECTION Subsect;
            /* 0x0000 */ struct _MMPTE_LIST List;
        }; /* size: 0x0008 */
    } /* size: 0x0008 */ u;
} MMPTE, * PMMPTE; /* size: 0x0008 */

typedef struct _MIPFNBLINK
{
    union
    {
        struct /* bitfield */
        {
            /* 0x0000 */ unsigned __int64 Blink : 40; /* bit position: 0 */
            /* 0x0000 */ unsigned __int64 NodeBlinkLow : 19; /* bit position: 40 */
            /* 0x0000 */ unsigned __int64 TbFlushStamp : 3; /* bit position: 59 */
            /* 0x0000 */ unsigned __int64 PageBlinkDeleteBit : 1; /* bit position: 62 */
            /* 0x0000 */ unsigned __int64 PageBlinkLockBit : 1; /* bit position: 63 */
        }; /* bitfield */
        struct /* bitfield */
        {
            /* 0x0000 */ unsigned __int64 ShareCount : 62; /* bit position: 0 */
            /* 0x0000 */ unsigned __int64 PageShareCountDeleteBit : 1; /* bit position: 62 */
            /* 0x0000 */ unsigned __int64 PageShareCountLockBit : 1; /* bit position: 63 */
        }; /* bitfield */
        /* 0x0000 */ unsigned __int64 EntireField;
        /* 0x0000 */ volatile __int64 Lock;
        struct /* bitfield */
        {
            /* 0x0000 */ unsigned __int64 LockNotUsed : 62; /* bit position: 0 */
            /* 0x0000 */ unsigned __int64 DeleteBit : 1; /* bit position: 62 */
            /* 0x0000 */ unsigned __int64 LockBit : 1; /* bit position: 63 */
        }; /* bitfield */
    }; /* size: 0x0008 */
} MIPFNBLINK, * PMIPFNBLINK; /* size: 0x0008 */

typedef struct _MMPFNENTRY1
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned char PageLocation : 3; /* bit position: 0 */
        /* 0x0000 */ unsigned char WriteInProgress : 1; /* bit position: 3 */
        /* 0x0000 */ unsigned char Modified : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned char ReadInProgress : 1; /* bit position: 5 */
        /* 0x0000 */ unsigned char CacheAttribute : 2; /* bit position: 6 */
    }; /* bitfield */
} MMPFNENTRY1, * PMMPFNENTRY1; /* size: 0x0001 */

typedef struct _MMPFNENTRY3
{
    struct /* bitfield */
    {
        /* 0x0000 */ unsigned char Priority : 3; /* bit position: 0 */
        /* 0x0000 */ unsigned char OnProtectedStandby : 1; /* bit position: 3 */
        /* 0x0000 */ unsigned char InPageError : 1; /* bit position: 4 */
        /* 0x0000 */ unsigned char SystemChargedPage : 1; /* bit position: 5 */
        /* 0x0000 */ unsigned char RemovalRequested : 1; /* bit position: 6 */
        /* 0x0000 */ unsigned char ParityError : 1; /* bit position: 7 */
    }; /* bitfield */
} MMPFNENTRY3, * PMMPFNENTRY3; /* size: 0x0001 */

typedef struct _MI_PFN_ULONG5
{
    union
    {
        /* 0x0000 */ unsigned long EntireField;
        struct
        {
            struct /* bitfield */
            {
                /* 0x0000 */ unsigned long NodeBlinkHigh : 21; /* bit position: 0 */
                /* 0x0000 */ unsigned long NodeFlinkMiddle : 11; /* bit position: 21 */
            }; /* bitfield */
        } /* size: 0x0004 */ StandbyList;
        struct
        {
            /* 0x0000 */ unsigned char ModifiedListBucketIndex : 4; /* bit position: 0 */
        } /* size: 0x0001 */ MappedPageList;
        struct
        {
            struct /* bitfield */
            {
                /* 0x0000 */ unsigned char AnchorLargePageSize : 2; /* bit position: 0 */
                /* 0x0000 */ unsigned char Spare1 : 6; /* bit position: 2 */
            }; /* bitfield */
            /* 0x0001 */ unsigned char ViewCount;
            /* 0x0002 */ unsigned short Spare2;
        } /* size: 0x0004 */ Active;
    }; /* size: 0x0004 */
} MI_PFN_ULONG5, * PMI_PFN_ULONG5; /* size: 0x0004 */

static void* g_mmonp_MmPfnDatabase;

typedef union _virt_addr_t
{
    void* value;
    struct
    {
        uintptr_t offset : 12;
        uintptr_t pt_index : 9;
        uintptr_t pd_index : 9;
        uintptr_t pdpt_index : 9;
        uintptr_t pml4_index : 9;
        uintptr_t reserved : 16;
    };
} virt_addr_t, * pvirt_addr_t;

typedef struct _MMPFN
{
    union
    {
        /* 0x0000 */ struct _LIST_ENTRY ListEntry;
        /* 0x0000 */ struct _RTL_BALANCED_NODE TreeNode;
        struct
        {
            union
            {
                union
                {
                    /* 0x0000 */ struct _SINGLE_LIST_ENTRY NextSlistPfn;
                    /* 0x0000 */ void* Next;
                    struct /* bitfield */
                    {
                        /* 0x0000 */ unsigned __int64 Flink : 40; /* bit position: 0 */
                        /* 0x0000 */ unsigned __int64 NodeFlinkLow : 24; /* bit position: 40 */
                    }; /* bitfield */
                    /* 0x0000 */ struct _MI_ACTIVE_PFN Active;
                }; /* size: 0x0008 */
            } /* size: 0x0008 */ u1;
            union
            {
                /* 0x0008 */ struct _MMPTE* PteAddress;
                /* 0x0008 */ unsigned __int64 PteLong;
            }; /* size: 0x0008 */
            /* 0x0010 */ struct _MMPTE OriginalPte;
        }; /* size: 0x0018 */
    }; /* size: 0x0018 */
    /* 0x0018 */ struct _MIPFNBLINK u2;
    union
    {
        union
        {
            struct
            {
                /* 0x0020 */ unsigned short ReferenceCount;
                /* 0x0022 */ struct _MMPFNENTRY1 e1;
                /* 0x0023 */ struct _MMPFNENTRY3 e3;
            }; /* size: 0x0004 */
            struct
            {
                /* 0x0020 */ unsigned short ReferenceCount;
            } /* size: 0x0002 */ e2;
            struct
            {
                /* 0x0020 */ unsigned long EntireField;
            } /* size: 0x0004 */ e4;
        }; /* size: 0x0004 */
    } /* size: 0x0004 */ u3;
    /* 0x0024 */ struct _MI_PFN_ULONG5 u5;
    union
    {
        union
        {
            struct /* bitfield */
            {
                /* 0x0028 */ unsigned __int64 PteFrame : 40; /* bit position: 0 */
                /* 0x0028 */ unsigned __int64 ResidentPage : 1; /* bit position: 40 */
                /* 0x0028 */ unsigned __int64 Unused1 : 1; /* bit position: 41 */
                /* 0x0028 */ unsigned __int64 Unused2 : 1; /* bit position: 42 */
                /* 0x0028 */ unsigned __int64 Partition : 10; /* bit position: 43 */
                /* 0x0028 */ unsigned __int64 FileOnly : 1; /* bit position: 53 */
                /* 0x0028 */ unsigned __int64 PfnExists : 1; /* bit position: 54 */
                /* 0x0028 */ unsigned __int64 NodeFlinkHigh : 5; /* bit position: 55 */
                /* 0x0028 */ unsigned __int64 PageIdentity : 3; /* bit position: 60 */
                /* 0x0028 */ unsigned __int64 PrototypePte : 1; /* bit position: 63 */
            }; /* bitfield */
            /* 0x0028 */ unsigned __int64 EntireField;
        }; /* size: 0x0008 */
    } /* size: 0x0008 */ u4;
} MMPFN, * PMMPFN; /* size: 0x0030 */














typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
    HANDLE Section;         // Not filled in
    PVOID MappedBase;
    PVOID ImageBase;
    ULONG ImageSize;
    ULONG Flags;
    USHORT LoadOrderIndex;
    USHORT InitOrderIndex;
    USHORT LoadCount;
    USHORT OffsetToFileName;
    UCHAR  FullPathName[MAXIMUM_FILENAME_LENGTH];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
    ULONG NumberOfModules;
    RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;

struct PiDDBCacheEntry
{
    LIST_ENTRY		List;
    UNICODE_STRING	DriverName;
    ULONG			TimeDateStamp;
    NTSTATUS		LoadStatus;
    char			_0x0028[16]; // data from the shim engine, or uninitialized memory for custom drivers
};

typedef struct _SYSTEM_MODULE {
    HANDLE Section;
    PVOID MappedBase;
    PVOID ImageBase;
    ULONG ImageSize;
    ULONG Flags;
    USHORT LoadOrderIndex;
    USHORT InitOrderIndex;
    USHORT LoadCount;
    USHORT OffsetToFileName;
    UCHAR  FullPathName[MAXIMUM_FILENAME_LENGTH];
} SYSTEM_MODULE, * PSYSTEM_MODULE;

typedef struct _SYSTEM_MODULE_INFORMATION {
    ULONG NumberOfModules;
    SYSTEM_MODULE Modules[1];
} SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

typedef struct _SYSTEM_BASIC_INFORMATION {
    ULONG Reserved;                        // Offset 0x00 (x86 & x64)
    ULONG TimerResolution;                 // Offset 0x04 (x86 & x64)
    ULONG PageSize;                        // Offset 0x08 (x86 & x64)
    ULONG NumberOfPhysicalPages;           // Offset 0x0C (x86 & x64)
    ULONG LowestPhysicalPageNumber;        // Offset 0x10 (x86 & x64)
    ULONG HighestPhysicalPageNumber;       // Offset 0x14 (x86 & x64)
    ULONG AllocationGranularity;           // Offset 0x18 (x86 & x64)
    ULONG_PTR MinimumUserModeAddress;      // Offset 0x1C (x86) / 0x20 (x64)
    ULONG_PTR MaximumUserModeAddress;      // Offset 0x20 (x86) / 0x28 (x64)
    KAFFINITY ActiveProcessorsAffinityMask; // Offset 0x24 (x86) / 0x30 (x64)
    CHAR NumberOfProcessors;               // Offset 0x28 (x86) / 0x38 (x64)
} SYSTEM_BASIC_INFORMATION;



typedef enum _SYSTEM_INFORMATION_CLASS
{
    SystemBasicInformation = 0x0,
    SystemProcessorInformation = 0x1,
    SystemPerformanceInformation = 0x2,
    SystemTimeOfDayInformation = 0x3,
    SystemPathInformation = 0x4,
    SystemProcessInformation = 0x5,
    SystemCallCountInformation = 0x6,
    SystemDeviceInformation = 0x7,
    SystemProcessorPerformanceInformation = 0x8,
    SystemFlagsInformation = 0x9,
    SystemCallTimeInformation = 0xa,
    SystemModuleInformation = 0xb,
    SystemLocksInformation = 0xc,
    SystemStackTraceInformation = 0xd,
    SystemPagedPoolInformation = 0xe,
    SystemNonPagedPoolInformation = 0xf,
    SystemHandleInformation = 0x10,
    SystemObjectInformation = 0x11,
    SystemPageFileInformation = 0x12,
    SystemVdmInstemulInformation = 0x13,
    SystemVdmBopInformation = 0x14,
    SystemFileCacheInformation = 0x15,
    SystemPoolTagInformation = 0x16,
    SystemInterruptInformation = 0x17,
    SystemDpcBehaviorInformation = 0x18,
    SystemFullMemoryInformation = 0x19,
    SystemLoadGdiDriverInformation = 0x1a,
    SystemUnloadGdiDriverInformation = 0x1b,
    SystemTimeAdjustmentInformation = 0x1c,
    SystemSummaryMemoryInformation = 0x1d,
    SystemMirrorMemoryInformation = 0x1e,
    SystemPerformanceTraceInformation = 0x1f,
    SystemObsolete0 = 0x20,
    SystemExceptionInformation = 0x21,
    SystemCrashDumpStateInformation = 0x22,
    SystemKernelDebuggerInformation = 0x23,
    SystemContextSwitchInformation = 0x24,
    SystemRegistryQuotaInformation = 0x25,
    SystemExtendServiceTableInformation = 0x26,
    SystemPrioritySeperation = 0x27,
    SystemVerifierAddDriverInformation = 0x28,
    SystemVerifierRemoveDriverInformation = 0x29,
    SystemProcessorIdleInformation = 0x2a,
    SystemLegacyDriverInformation = 0x2b,
    SystemCurrentTimeZoneInformation = 0x2c,
    SystemLookasideInformation = 0x2d,
    SystemTimeSlipNotification = 0x2e,
    SystemSessionCreate = 0x2f,
    SystemSessionDetach = 0x30,
    SystemSessionInformation = 0x31,
    SystemRangeStartInformation = 0x32,
    SystemVerifierInformation = 0x33,
    SystemVerifierThunkExtend = 0x34,
    SystemSessionProcessInformation = 0x35,
    SystemLoadGdiDriverInSystemSpace = 0x36,
    SystemNumaProcessorMap = 0x37,
    SystemPrefetcherInformation = 0x38,
    SystemExtendedProcessInformation = 0x39,
    SystemRecommendedSharedDataAlignment = 0x3a,
    SystemComPlusPackage = 0x3b,
    SystemNumaAvailableMemory = 0x3c,
    SystemProcessorPowerInformation = 0x3d,
    SystemEmulationBasicInformation = 0x3e,
    SystemEmulationProcessorInformation = 0x3f,
    SystemExtendedHandleInformation = 0x40,
    SystemLostDelayedWriteInformation = 0x41,
    SystemBigPoolInformation = 0x42,
    SystemSessionPoolTagInformation = 0x43,
    SystemSessionMappedViewInformation = 0x44,
    SystemHotpatchInformation = 0x45,
    SystemObjectSecurityMode = 0x46,
    SystemWatchdogTimerHandler = 0x47,
    SystemWatchdogTimerInformation = 0x48,
    SystemLogicalProcessorInformation = 0x49,
    SystemWow64SharedInformationObsolete = 0x4a,
    SystemRegisterFirmwareTableInformationHandler = 0x4b,
    SystemFirmwareTableInformation = 0x4c,
    SystemModuleInformationEx = 0x4d,
    SystemVerifierTriageInformation = 0x4e,
    SystemSuperfetchInformation = 0x4f,
    SystemMemoryListInformation = 0x50,
    SystemFileCacheInformationEx = 0x51,
    SystemThreadPriorityClientIdInformation = 0x52,
    SystemProcessorIdleCycleTimeInformation = 0x53,
    SystemVerifierCancellationInformation = 0x54,
    SystemProcessorPowerInformationEx = 0x55,
    SystemRefTraceInformation = 0x56,
    SystemSpecialPoolInformation = 0x57,
    SystemProcessIdInformation = 0x58,
    SystemErrorPortInformation = 0x59,
    SystemBootEnvironmentInformation = 0x5a,
    SystemHypervisorInformation = 0x5b,
    SystemVerifierInformationEx = 0x5c,
    SystemTimeZoneInformation = 0x5d,
    SystemImageFileExecutionOptionsInformation = 0x5e,
    SystemCoverageInformation = 0x5f,
    SystemPrefetchPatchInformation = 0x60,
    SystemVerifierFaultsInformation = 0x61,
    SystemSystemPartitionInformation = 0x62,
    SystemSystemDiskInformation = 0x63,
    SystemProcessorPerformanceDistribution = 0x64,
    SystemNumaProximityNodeInformation = 0x65,
    SystemDynamicTimeZoneInformation = 0x66,
    SystemCodeIntegrityInformation = 0x67,
    SystemProcessorMicrocodeUpdateInformation = 0x68,
    SystemProcessorBrandString = 0x69,
    SystemVirtualAddressInformation = 0x6a,
    SystemLogicalProcessorAndGroupInformation = 0x6b,
    SystemProcessorCycleTimeInformation = 0x6c,
    SystemStoreInformation = 0x6d,
    SystemRegistryAppendString = 0x6e,
    SystemAitSamplingValue = 0x6f,
    SystemVhdBootInformation = 0x70,
    SystemCpuQuotaInformation = 0x71,
    SystemNativeBasicInformation = 0x72,
    SystemErrorPortTimeouts = 0x73,
    SystemLowPriorityIoInformation = 0x74,
    SystemBootEntropyInformation = 0x75,
    SystemVerifierCountersInformation = 0x76,
    SystemPagedPoolInformationEx = 0x77,
    SystemSystemPtesInformationEx = 0x78,
    SystemNodeDistanceInformation = 0x79,
    SystemAcpiAuditInformation = 0x7a,
    SystemBasicPerformanceInformation = 0x7b,
    SystemQueryPerformanceCounterInformation = 0x7c,
    SystemSessionBigPoolInformation = 0x7d,
    SystemBootGraphicsInformation = 0x7e,
    SystemScrubPhysicalMemoryInformation = 0x7f,
    SystemBadPageInformation = 0x80,
    SystemProcessorProfileControlArea = 0x81,
    SystemCombinePhysicalMemoryInformation = 0x82,
    SystemEntropyInterruptTimingInformation = 0x83,
    SystemConsoleInformation = 0x84,
    SystemPlatformBinaryInformation = 0x85,
    SystemThrottleNotificationInformation = 0x86,
    SystemHypervisorProcessorCountInformation = 0x87,
    SystemDeviceDataInformation = 0x88,
    SystemDeviceDataEnumerationInformation = 0x89,
    SystemMemoryTopologyInformation = 0x8a,
    SystemMemoryChannelInformation = 0x8b,
    SystemBootLogoInformation = 0x8c,
    SystemProcessorPerformanceInformationEx = 0x8d,
    SystemSpare0 = 0x8e,
    SystemSecureBootPolicyInformation = 0x8f,
    SystemPageFileInformationEx = 0x90,
    SystemSecureBootInformation = 0x91,
    SystemEntropyInterruptTimingRawInformation = 0x92,
    SystemPortableWorkspaceEfiLauncherInformation = 0x93,
    SystemFullProcessInformation = 0x94,
    SystemKernelDebuggerInformationEx = 0x95,
    SystemBootMetadataInformation = 0x96,
    SystemSoftRebootInformation = 0x97,
    SystemElamCertificateInformation = 0x98,
    SystemOfflineDumpConfigInformation = 0x99,
    SystemProcessorFeaturesInformation = 0x9a,
    SystemRegistryReconciliationInformation = 0x9b,
    MaxSystemInfoClass = 0x9c,
} SYSTEM_INFORMATION_CLASS;

#define MM_UNLOADED_DRIVERS_SIZE 50
typedef struct _MM_UNLOADED_DRIVER {
    UNICODE_STRING 	Name;
    PVOID 			ModuleStart;
    PVOID 			ModuleEnd;
    ULONG64 		UnloadTime;
} MM_UNLOADED_DRIVER, * PMM_UNLOADED_DRIVER;


typedef struct _KLDR_DATA_TABLE_ENTRY
{
    struct _LIST_ENTRY InLoadOrderLinks;                                    //0x0
    VOID* ExceptionTable;                                                   //0x8
    ULONG ExceptionTableSize;                                               //0xc
    VOID* GpValue;                                                          //0x10
    struct _NON_PAGED_DEBUG_INFO* NonPagedDebugInfo;                        //0x14
    VOID* DllBase;                                                          //0x18
    VOID* EntryPoint;                                                       //0x1c
    ULONG SizeOfImage;                                                      //0x20
    struct _UNICODE_STRING FullDllName;                                     //0x24
    struct _UNICODE_STRING BaseDllName;                                     //0x2c
    ULONG Flags;                                                            //0x34
    USHORT LoadCount;                                                       //0x38
    union
    {
        USHORT SignatureLevel : 4;                                            //0x3a
        USHORT SignatureType : 3;                                             //0x3a
        USHORT Unused : 9;                                                    //0x3a
        USHORT EntireField;                                                 //0x3a
    } u1;                                                                   //0x3a
    VOID* SectionPointer;                                                   //0x3c
    ULONG CheckSum;                                                         //0x40
    ULONG CoverageSectionSize;                                              //0x44
    VOID* CoverageSection;                                                  //0x48
    VOID* LoadedImports;                                                    //0x4c
    VOID* Spare;                                                            //0x50
    ULONG SizeOfImageNotRounded;                                            //0x54
    ULONG TimeDateStamp;                                                    //0x58
} KLDR_DATA_TABLE_ENTRY, * PKLDR_DATA_TABLE_ENTRY;




typedef union _cr3 {
    uint64_t flags;

    struct {
        uint64_t pcid : 12;
        uint64_t page_frame_number : 36;
        uint64_t reserved_1 : 12;
        uint64_t reserved_2 : 3;
        uint64_t pcid_invalidate : 1;
    };
} cr3, * pcr3;
static_assert(sizeof(cr3) == sizeof(void*), "size mismatch, only 64-bit supported.");

struct single_list_entry_t {
    single_list_entry_t* m_next;
};



typedef struct _memory_basic_information {
    void* BaseAddress;
    void* AllocationBase;
    uint32_t  AllocationProtect;
    uint32_t   PartitionId;
    uint64_t RegionSize;
    uint32_t  State;
    uint32_t  Protect;
    uint32_t  Type;
} memory_basic_information, * pmemory_basic_information;

struct section_header_t {
    char m_name[0x8];
    union {
        int32_t m_physical_address;
        int32_t m_virtual_size;
    };
    int32_t m_virtual_address;
    int32_t m_size_of_raw_data;
    int32_t m_pointer_to_raw_data;
    int32_t m_pointer_to_relocations;
    int32_t m_pointer_to_line_numbers;
    int16_t m_number_of_relocations;
    int16_t m_number_of_line_numbers;
    int32_t m_characteristics;
};

struct list_entry_t {
    list_entry_t* m_flink;
    list_entry_t* m_blink;
};

enum pe_magic_t {
    dos_header = 0x5a4d,
    nt_headers = 0x4550,
    opt_header = 0x020b
};

struct data_directory_t {
    int32_t m_virtual_address;
    int32_t m_size;

    template< class type_t >
    
    type_t as_rva(
        unsigned char* rva
    ) {
        return reinterpret_cast<type_t>(rva + m_virtual_address);
    }
};

struct dos_header_t {
    int16_t m_magic;
    int16_t m_cblp;
    int16_t m_cp;
    int16_t m_crlc;
    int16_t m_cparhdr;
    int16_t m_minalloc;
    int16_t m_maxalloc;
    int16_t m_ss;
    int16_t m_sp;
    int16_t m_csum;
    int16_t m_ip;
    int16_t m_cs;
    int16_t m_lfarlc;
    int16_t m_ovno;
    int16_t m_res0[0x4];
    int16_t m_oemid;
    int16_t m_oeminfo;
    int16_t m_res1[0xa];
    int32_t m_lfanew;

    
    constexpr bool is_valid() {
        return m_magic == pe_magic_t::dos_header;
    }
};

struct export_directory_t {
    int32_t m_characteristics;
    int32_t m_time_date_stamp;
    int16_t m_major_version;
    int16_t m_minor_version;
    int32_t m_name;
    int32_t m_base;
    int32_t m_number_of_functions;
    int32_t m_number_of_names;
    int32_t m_address_of_functions;
    int32_t m_address_of_names;
    int32_t m_address_of_names_ordinals;
};

struct nt_headers_t {
    int32_t m_signature;
    int16_t m_machine;
    int16_t m_number_of_sections;
    int32_t m_time_date_stamp;
    int32_t m_pointer_to_symbol_table;
    int32_t m_number_of_symbols;
    int16_t m_size_of_optional_header;
    int16_t m_characteristics;

    int16_t m_magic;
    int8_t m_major_linker_version;
    int8_t m_minor_linker_version;
    int32_t m_size_of_code;
    int32_t m_size_of_initialized_data;
    int32_t m_size_of_uninitialized_data;
    int32_t m_address_of_entry_point;
    int32_t m_base_of_code;
    uint64_t m_image_base;
    int32_t m_section_alignment;
    int32_t m_file_alignment;
    int16_t m_major_operating_system_version;
    int16_t m_minor_operating_system_version;
    int16_t m_major_image_version;
    int16_t m_minor_image_version;
    int16_t m_major_subsystem_version;
    int16_t m_minor_subsystem_version;
    int32_t m_win32_version_value;
    int32_t m_size_of_image;
    int32_t m_size_of_headers;
    int32_t m_check_sum;
    int16_t m_subsystem;
    int16_t m_dll_characteristics;
    uint64_t m_size_of_stack_reserve;
    uint64_t m_size_of_stack_commit;
    uint64_t m_size_of_heap_reserve;
    uint64_t m_size_of_heap_commit;
    int32_t m_loader_flags;
    int32_t m_number_of_rva_and_sizes;

    data_directory_t m_export_table;
    data_directory_t m_import_table;
    data_directory_t m_resource_table;
    data_directory_t m_exception_table;
    data_directory_t m_certificate_table;
    data_directory_t m_base_relocation_table;
    data_directory_t m_debug;
    data_directory_t m_architecture;
    data_directory_t m_global_ptr;
    data_directory_t m_tls_table;
    data_directory_t m_load_config_table;
    data_directory_t m_bound_import;
    data_directory_t m_iat;
    data_directory_t m_delay_import_descriptor;
    data_directory_t m_clr_runtime_header;
    data_directory_t m_reserved;

    
    constexpr bool is_valid() {
        return m_signature == pe_magic_t::nt_headers
            && m_magic == pe_magic_t::opt_header;
    }
};

struct unicode_string_t {
    uint16_t m_length;
    uint16_t m_maximum_length;
    wchar_t* m_buffer;
};
















namespace IA32 {
typedef struct _TEB {
    PVOID Reserved1[12];
    PPEB  ProcessEnvironmentBlock;
    PVOID Reserved2[399];
    BYTE  Reserved3[1952];
    PVOID TlsSlots[64];
    BYTE  Reserved4[8];
    PVOID Reserved5[26];
    PVOID ReservedForOle;
    PVOID Reserved6[4];
    PVOID TlsExpansionSlots;
} TEB, * PTEB;

typedef enum {
    pdpt_table_valid, // Means that the pml4 at the correct index already points to a remapped pdpt table
    pde_table_valid,  // Means that the pdpt at the correct index already points to a remapped pde table
    pte_table_valid,  // Means that the pde at the correct index already points to a remapped pte table
    non_valid,        // Means that the pml4 indexes didn't match
} usable_entry_t;

typedef union _virt_addr_t
{
    struct
    {
        uint64_t offset_1gb : 21;
        uint64_t pdpte_index : 9;
        uint64_t pml4e_index : 9;
        uint64_t reserved : 16;
    };

    struct
    {
        uint64_t offset_2mb : 21;
        uint64_t pde_index : 9;
        uint64_t pdpte_index : 9;
        uint64_t pml4e_index : 9;
        uint64_t reserved : 16;
    };

    struct
    {
        uint64_t offset_4kb : 12;
        uint64_t pte_index : 9;
        uint64_t pde_index : 9;
        uint64_t pdpte_index : 9;
        uint64_t pml4e_index : 9;
        uint64_t reserved : 16;
    };

    uintptr_t value;
} virt_addr_t, * pvirt_addr_t;
static_assert(sizeof(virt_addr_t) == sizeof(void*), "size mismatch, only 64-bit supported.");

typedef union _pml4e
{
    struct
    {
        uint64_t present : 1;					// Must be 1 if the region is valid.
        uint64_t read_write : 1;				// Write access control (0 = read-only, 1 = read/write)
        uint64_t user_supervisor : 1;			// User/supervisor access control (0 = supervisor, 1 = user)
        uint64_t page_write_through : 1;		// Write-through caching
        uint64_t cached_disable : 1;			// Cache disable (1 = disable caching)
        uint64_t accessed : 1;					// Set when accessed
        uint64_t dirty : 1;					// Set when written to (only valid for large pages)
        uint64_t large_page : 1;				// Page size (1 = entry maps a 1-GByte page)
        uint64_t ignored1 : 4;					// Ignored by hardware
        uint64_t pfn : 36;						// Physical frame number of the 4KB page
        uint64_t reserved_for_software : 4;	// Reserved for software use only
        uint64_t reserved_for_hardware : 11;	// Reserved for hardware use only
        uint64_t no_execute : 1;				// No-execute (NX) bit, set to disable execution
    } hard;

    uint64_t value;
} pml4e, * ppml4e;

typedef union _pte
{
    struct
    {
        uint64_t present : 1;					// Must be 1 if the page is valid
        uint64_t read_write : 1;				// Write access control (0 = read-only, 1 = read/write)
        uint64_t user_supervisor : 1;			// User/supervisor access control (0 = supervisor, 1 = user)
        uint64_t page_write_through : 1;		// Write-through caching
        uint64_t cached_disable : 1;			// Cache disable (1 = disable caching)
        uint64_t accessed : 1;					// Set when accessed
        uint64_t dirty : 1;					// Set when written to
        uint64_t page_attribute_table : 1;		// Page Attribute Table bit (affects memory type selection)
        uint64_t global_page : 1;				// Set if the page is global (won't be flushed on CR3 switch)
        uint64_t ignored1 : 3;					// Ignored by hardware
        uint64_t pfn : 36;						// Physical frame number of the 4KB page
        uint64_t reserved : 4;					// Reserved for future use
        uint64_t ignored2 : 7;					// Ignored by software
        uint64_t protection_key : 4;			// Protection Key (if PKE bit in CR4 is set)
        uint64_t no_execute : 1;				// No-execute (NX) bit, set to disable execution
    } hard;

    uint64_t value;
} pte, * ppte;

typedef union _pfn {
    struct {
        uint64_t pte_frame : 25;                  // Frame number in PFN
        uint64_t image_verified : 1;              // Image verification status
        uint64_t awe_allocation : 1;              // Allocation type (AWE)
        uint64_t prototype_pte : 1;               // Prototype PTE
        uint64_t page_color : 4;                  // Page color (for balancing)
        uint64_t page_location : 3;               // State (free, standby, etc.)
        uint64_t modified : 1;                    // Modified bit
        uint64_t read_in_progress : 1;            // Ongoing read
        uint64_t write_in_progress : 1;           // Ongoing write
        uint64_t in_transition : 1;               // Paging transition
        uint64_t reserved_flags : 3;              // Reserved flags
    } flags;

    struct {
        uint16_t reference_count;           // Reference count (2 bytes)
        uint16_t padding;                   // Padding for 8-byte alignment
        uint64_t flink;                     // Forward link (8 bytes)
        uint64_t blink;                     // Backward link (8 bytes)
        uint32_t ws_index;                  // Working set index (4 bytes)
        uint32_t ws_padding;                // Padding for 8-byte alignment
        uint64_t pte_address;               // Pointer to PTE in memory (8 bytes)
    } meta_data;

} pfn, * ppfn;

typedef union _cr3 {
    uint64_t flags;

    struct {
        uint64_t pcid : 12;
        uint64_t page_frame_number : 36;
        uint64_t reserved_1 : 12;
        uint64_t reserved_2 : 3;
        uint64_t pcid_invalidate : 1;
    };
} cr3, * pcr3;
static_assert(sizeof(cr3) == sizeof(void*), "size mismatch, only 64-bit supported.");

typedef union _ktss64
{
    struct
    {
        uint32_t reserved0;                    // Reserved (must be 0)
        uint64_t rsp0;                         // Stack pointer for ring 0
        uint64_t rsp1;                         // Stack pointer for ring 1
        uint64_t rsp2;                         // Stack pointer for ring 2
        uint64_t ist[7];                     // Interrupt stack table pointers (IST1 - IST7)
        uint64_t reserved1;                    // Reserved (must be 0)
        uint16_t reserved2;                    // Reserved (must be 0)
        uint16_t iomap_base;                   // I/O map base address
    };
} ktss64, * pktss64;

typedef struct _KAFFINITY_EX
{
    uint8_t Count;
    uint16_t Size;
    unsigned long Reserved;
    uint64_t Bitmap[20];

} KAFFINITY_EX, * PKAFFINITY_EX;

typedef struct _RTL_MODULE_EXTENDED_INFO
{
    void* ImageBase;
    unsigned long ImageSize;
    uint16_t FileNameOffset;
    char FullPathName[0x100];
} RTL_MODULE_EXTENDED_INFO, * PRTL_MODULE_EXTENDED_INFO;

typedef struct _SYSTEM_MODULES
{
    void* address;
    int module_count;
}SYSTEM_MODULES, * PSYSTEM_MODULES;

typedef struct _INVALID_DRIVER
{
    struct _INVALID_DRIVER* next;
    void* driver;
}INVALID_DRIVER, * PINVALID_DRIVER;

typedef struct _INVALID_DRIVERS_HEAD
{
    PINVALID_DRIVER first_entry;
    int count;		//keeps track of the number of drivers in the list
}INVALID_DRIVERS_HEAD, * PINVALID_DRIVERS_HEAD;

typedef struct _MACHINE_FRAME
{
    uint64_t rip;
    uint64_t cs;
    uint64_t eflags;
    uint64_t rsp;
    uint64_t ss;
} MACHINE_FRAME, * PMACHINE_FRAME;

typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
    unsigned long Version;
    unsigned long Reserved;
    void* Callback;
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, * PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

//0x18 bytes (sizeof)
struct dispatcher_header_t
{
    union
    {
        volatile int32_t Lock;                                                 //0x0
        int32_t LockNV;                                                        //0x0
        struct
        {
            uint8_t Type;                                                     //0x0
            uint8_t Signalling;                                               //0x1
            uint8_t Size;                                                     //0x2
            uint8_t Reserved1;                                                //0x3
        };
        struct
        {
            uint8_t TimerType;                                                //0x0
            union
            {
                uint8_t TimerControlFlags;                                    //0x1
                struct
                {
                    uint8_t Absolute : 1;                                       //0x1
                    uint8_t Wake : 1;                                           //0x1
                    uint8_t EncodedTolerableDelay : 6;                          //0x1
                };
            };
            uint8_t Hand;                                                     //0x2
            union
            {
                uint8_t TimerMiscFlags;                                       //0x3
                struct
                {
                    uint8_t Index : 6;                                          //0x3
                    uint8_t Inserted : 1;                                       //0x3
                    volatile uint8_t Expired : 1;                               //0x3
                };
            };
        };
        struct
        {
            uint8_t Timer2Type;                                               //0x0
            union
            {
                uint8_t Timer2Flags;                                          //0x1
                struct
                {
                    uint8_t Timer2Inserted : 1;                                 //0x1
                    uint8_t Timer2Expiring : 1;                                 //0x1
                    uint8_t Timer2CancelPending : 1;                            //0x1
                    uint8_t Timer2SetPending : 1;                               //0x1
                    uint8_t Timer2Running : 1;                                  //0x1
                    uint8_t Timer2Disabled : 1;                                 //0x1
                    uint8_t Timer2ReservedFlags : 2;                            //0x1
                };
            };
            uint8_t Timer2ComponentId;                                        //0x2
            uint8_t Timer2RelativeId;                                         //0x3
        };
        struct
        {
            uint8_t QueueType;                                                //0x0
            union
            {
                uint8_t QueueControlFlags;                                    //0x1
                struct
                {
                    uint8_t Abandoned : 1;                                      //0x1
                    uint8_t DisableIncrement : 1;                               //0x1
                    uint8_t QueueReservedControlFlags : 6;                      //0x1
                };
            };
            uint8_t QueueSize;                                                //0x2
            uint8_t QueueReserved;                                            //0x3
        };
        struct
        {
            uint8_t ThreadType;                                               //0x0
            uint8_t ThreadReserved;                                           //0x1
            union
            {
                uint8_t ThreadControlFlags;                                   //0x2
                struct
                {
                    uint8_t CycleProfiling : 1;                                 //0x2
                    uint8_t CounterProfiling : 1;                               //0x2
                    uint8_t GroupScheduling : 1;                                //0x2
                    uint8_t AffinitySet : 1;                                    //0x2
                    uint8_t Tagged : 1;                                         //0x2
                    uint8_t EnergyProfiling : 1;                                //0x2
                    uint8_t SchedulerAssist : 1;                                //0x2
                    uint8_t ThreadReservedControlFlags : 1;                     //0x2
                };
            };
            union
            {
                uint8_t DebugActive;                                          //0x3
                struct
                {
                    uint8_t ActiveDR7 : 1;                                      //0x3
                    uint8_t Instrumented : 1;                                   //0x3
                    uint8_t Minimal : 1;                                        //0x3
                    uint8_t Reserved4 : 2;                                      //0x3
                    uint8_t AltSyscall : 1;                                     //0x3
                    uint8_t UmsScheduled : 1;                                   //0x3
                    uint8_t UmsPrimary : 1;                                     //0x3
                };
            };
        };
        struct
        {
            uint8_t MutantType;                                               //0x0
            uint8_t MutantSize;                                               //0x1
            uint8_t DpcActive;                                                //0x2
            uint8_t MutantReserved;                                           //0x3
        };
    };
    int32_t SignalState;                                                       //0x4
    list_entry_t WaitListHead;                                        //0x8
};

union ularge_integer_t
{
    struct
    {
        uint32_t  LowPart;                                                      //0x0
        uint32_t  HighPart;                                                     //0x4
    };
    struct
    {
        uint32_t  LowPart;                                                      //0x0
        uint32_t  HighPart;                                                     //0x4
    } u;                                                                    //0x0
    uint64_t QuadPart;                                                     //0x0
};

//0x40 bytes (sizeof)
struct ktimer_t
{
    struct dispatcher_header_t Header;                                       //0x0
    union ularge_integer_t DueTime;                                          //0x18
    struct list_entry_t TimerListEntry;                                      //0x20
    struct _KDPC* Dpc;                                                      //0x30
    uint16_t Processor;                                                       //0x38
    uint16_t TimerType;                                                       //0x3a
    uint32_t Period;                                                           //0x3c
};

//0x30 bytes (sizeof)
struct kapc_state_t
{
    list_entry_t ApcListHead[2];                                      //0x0
    struct _KPROCESS* Process;                                              //0x20
    union
    {
        uint8_t InProgressFlags;                                              //0x28
        struct
        {
            uint8_t KernelApcInProgress : 1;                                    //0x28
            uint8_t SpecialApcInProgress : 1;                                   //0x28
        };
    };
    uint8_t KernelApcPending;                                                 //0x29
    union
    {
        uint8_t UserApcPendingAll;                                            //0x2a
        struct
        {
            uint8_t SpecialUserApcPending : 1;                                  //0x2a
            uint8_t UserApcPending : 1;                                         //0x2a
        };
    };
};

//0x1 bytes (sizeof)
union kwait_status_register_t
{
    uint8_t Flags;                                                            //0x0
    uint8_t State : 3;                                                          //0x0
    uint8_t Affinity : 1;                                                       //0x0
    uint8_t Priority : 1;                                                       //0x0
    uint8_t Apc : 1;                                                            //0x0
    uint8_t UserApc : 1;                                                        //0x0
    uint8_t Alert : 1;                                                          //0x0
};

//0x30 bytes (sizeof)
struct kwait_block_t
{
    struct list_entry_t WaitListEntry;                                       //0x0
    uint8_t WaitType;                                                         //0x10
    volatile uint8_t BlockState;                                              //0x11
    uint16_t WaitKey;                                                         //0x12
    int32_t SpareLong;                                                         //0x14
    union
    {
        struct kthread* Thread;                                            //0x18
        struct _KQUEUE* NotificationQueue;                                  //0x18
    };
    void* Object;                                                           //0x20
    void* SparePtr;                                                         //0x28
};

//0x10 bytes (sizeof)
struct group_affinity_t
{
    uint64_t Mask;                                                         //0x0
    uint16_t Group;                                                           //0x8
    uint16_t Reserved[3];                                                     //0xa
};

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
    void* Section;
    void* MappedBase;
    void* image_base;
    unsigned long image_size;
    unsigned long Flags;
    uint16_t LoadOrderIndex;
    uint16_t InitOrderIndex;
    uint16_t LoadCount;
    uint16_t OffsetToFileName;
    char FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _rtl_process_modules
{
    unsigned long number_of_modules;
    RTL_PROCESS_MODULE_INFORMATION modules[1];
} rtl_process_modules, * prtl_process_modules;

//0x58 bytes (sizeof)
struct kapc_t
{
    uint8_t Type;                                                             //0x0
    uint8_t SpareByte0;                                                       //0x1
    uint8_t Size;                                                             //0x2
    uint8_t SpareByte1;                                                       //0x3
    uint32_t SpareLong0;                                                       //0x4
    struct kthread* Thread;                                                //0x8
    struct list_entry_t ApcListEntry;                                        //0x10
    union
    {
        struct
        {
            void(*KernelRoutine)(struct kapc_t* arg1, void(**arg2)(void* arg1, void* arg2, void* arg3), void** arg3, void** arg4, void** arg5); //0x20
            void(*RundownRoutine)(struct kapc_t* arg1);                     //0x28
            void(*NormalRoutine)(void* arg1, void* arg2, void* arg3);      //0x30
        };
        void* Reserved[3];                                                  //0x20
    };
    void* NormalContext;                                                    //0x38
    void* SystemArgument1;                                                  //0x40
    void* SystemArgument2;                                                  //0x48
    uint8_t ApcStateIndex;                                                     //0x50
    uint8_t ApcMode;                                                           //0x51
    uint8_t Inserted;                                                         //0x52
};

//0x18 bytes (sizeof)
struct kevent_t
{
    struct dispatcher_header_t Header;                                       //0x0
};

struct kthread
{
    struct dispatcher_header_t Header;                                       //0x0
    void* SListFaultAddress;                                                //0x18
    uint64_t QuantumTarget;                                                //0x20
    void* InitialStack;                                                     //0x28
    void* volatile StackLimit;                                              //0x30
    void* StackBase;                                                        //0x38
    uint64_t ThreadLock;                                                   //0x40
    volatile uint64_t CycleTime;                                           //0x48
    uint64_t CurrentRunTime;                                                   //0x50
    uint64_t ExpectedRunTime;                                                  //0x54
    void* KernelStack;                                                      //0x58
    struct _XSAVE_FORMAT* StateSaveArea;                                    //0x60
    struct _KSCHEDULING_GROUP* volatile SchedulingGroup;                    //0x68
    union kwait_status_register_t WaitRegister;                              //0x70
    volatile uint8_t Running;                                                 //0x71
    uint8_t Alerted[2];                                                       //0x72
    union
    {
        struct
        {
            uint64_t AutoBoostActive : 1;                                        //0x74
            uint64_t ReadyTransition : 1;                                        //0x74
            uint64_t WaitNext : 1;                                               //0x74
            uint64_t SystemAffinityActive : 1;                                   //0x74
            uint64_t Alertable : 1;                                              //0x74
            uint64_t UserStackWalkActive : 1;                                    //0x74
            uint64_t ApcInterruptRequest : 1;                                    //0x74
            uint64_t QuantumEndMigrate : 1;                                      //0x74
            uint64_t UmsDirectedSwitchEnable : 1;                                //0x74
            uint64_t TimerActive : 1;                                            //0x74
            uint64_t SystemThread : 1;                                           //0x74
            uint64_t ProcessDetachActive : 1;                                    //0x74
            uint64_t CalloutActive : 1;                                          //0x74
            uint64_t ScbReadyQueue : 1;                                          //0x74
            uint64_t ApcQueueable : 1;                                           //0x74
            uint64_t ReservedStackInUse : 1;                                     //0x74
            uint64_t UmsPerformingSyscall : 1;                                   //0x74
            uint64_t TimerSuspended : 1;                                         //0x74
            uint64_t SuspendedWaitMode : 1;                                      //0x74
            uint64_t SuspendSchedulerApcWait : 1;                                //0x74
            uint64_t CetUserShadowStack : 1;                                     //0x74
            uint64_t BypassProcessFreeze : 1;                                    //0x74
            uint64_t Reserved : 10;                                              //0x74
        };
        int32_t MiscFlags;                                                     //0x74
    };
    union
    {
        struct
        {
            uint64_t ThreadFlagsSpare : 2;                                       //0x78
            uint64_t AutoAlignment : 1;                                          //0x78
            uint64_t DisableBoost : 1;                                           //0x78
            uint64_t AlertedByThreadId : 1;                                      //0x78
            uint64_t QuantumDonation : 1;                                        //0x78
            uint64_t EnableStackSwap : 1;                                        //0x78
            uint64_t GuiThread : 1;                                              //0x78
            uint64_t DisableQuantum : 1;                                         //0x78
            uint64_t ChargeOnlySchedulingGroup : 1;                              //0x78
            uint64_t DeferPreemption : 1;                                        //0x78
            uint64_t QueueDeferPreemption : 1;                                   //0x78
            uint64_t ForceDeferSchedule : 1;                                     //0x78
            uint64_t clientReadyQueueAffinity : 1;                               //0x78
            uint64_t FreezeCount : 1;                                            //0x78
            uint64_t TerminationApcRequest : 1;                                  //0x78
            uint64_t AutoBoostEntriesExhausted : 1;                              //0x78
            uint64_t KernelStackResident : 1;                                    //0x78
            uint64_t TerminateRequestReason : 2;                                 //0x78
            uint64_t ProcessStackCountDecremented : 1;                           //0x78
            uint64_t RestrictedGuiThread : 1;                                    //0x78
            uint64_t VpBackingThread : 1;                                        //0x78
            uint64_t ThreadFlagsSpare2 : 1;                                      //0x78
            uint64_t EtwStackTraceApcInserted : 8;                               //0x78
        };
        volatile int32_t ThreadFlags;                                          //0x78
    };
    volatile uint8_t Tag;                                                     //0x7c
    uint8_t SystemHeteroCpuPolicy;                                            //0x7d
    uint8_t UserHeteroCpuPolicy : 7;                                            //0x7e
    uint8_t ExplicitSystemHeteroCpuPolicy : 1;                                  //0x7e
    union
    {
        struct
        {
            uint8_t RunningNonRetpolineCode : 1;                                //0x7f
            uint8_t SpecCtrlSpare : 7;                                          //0x7f
        };
        uint8_t SpecCtrl;                                                     //0x7f
    };
    uint64_t SystemCallNumber;                                                 //0x80
    uint64_t ReadyTime;                                                        //0x84
    void* FirstArgument;                                                    //0x88
    struct _KTRAP_FRAME* TrapFrame;                                         //0x90
    union
    {
        struct kapc_state_t ApcState;                                        //0x98
        struct
        {
            uint8_t ApcStateFill[43];                                         //0x98
            uint8_t Priority;                                                  //0xc3
            uint64_t UserIdealProcessor;                                       //0xc4
        };
    };
    volatile uint64_t WaitStatus;                                           //0xc8
    struct kwait_block_t* WaitBlockList;                                     //0xd0
    union
    {
        struct list_entry_t WaitListEntry;                                   //0xd8
        struct single_list_entry_t SwapListEntry;                            //0xd8
    };
    struct dispatcher_header_t* volatile Queue;                              //0xe8
    IA32::PTEB Teb;                                                              //0xf0
    uint64_t RelativeTimerBias;                                            //0xf8
    struct ktimer_t Timer;                                                   //0x100
    union
    {
        struct kwait_block_t WaitBlock[4];                                   //0x140
        struct
        {
            uint8_t WaitBlockFill4[20];                                       //0x140
            uint64_t ContextSwitches;                                          //0x154
        };
        struct
        {
            uint8_t WaitBlockFill5[68];                                       //0x140
            volatile uint8_t State;                                           //0x184
            uint8_t Spare13;                                                   //0x185
            uint8_t WaitIrql;                                                 //0x186
            uint8_t WaitMode;                                                  //0x187
        };
        struct
        {
            uint8_t WaitBlockFill6[116];                                      //0x140
            uint64_t WaitTime;                                                 //0x1b4
        };
        struct
        {
            uint8_t WaitBlockFill7[164];                                      //0x140
            union
            {
                struct
                {
                    int16_t KernelApcDisable;                                 //0x1e4
                    int16_t SpecialApcDisable;                                //0x1e6
                };
                uint64_t CombinedApcDisable;                                   //0x1e4
            };
        };
        struct
        {
            uint8_t WaitBlockFill8[40];                                       //0x140
            struct _KTHREAD_COUNTERS* ThreadCounters;                       //0x168
        };
        struct
        {
            uint8_t WaitBlockFill9[88];                                       //0x140
            struct _XSTATE_SAVE* XStateSave;                                //0x198
        };
        struct
        {
            uint8_t WaitBlockFill10[136];                                     //0x140
            void* volatile Win32Thread;                                     //0x1c8
        };
        struct
        {
            uint8_t WaitBlockFill11[176];                                     //0x140
            struct _UMS_CONTROL_BLOCK* Ucb;                                 //0x1f0
            struct _KUMS_CONTEXT_HEADER* volatile Uch;                      //0x1f8
        };
    };
    union
    {
        volatile int32_t ThreadFlags2;                                         //0x200
        struct
        {
            uint64_t BamQosLevel : 8;                                            //0x200
            uint64_t ThreadFlags2Reserved : 24;                                  //0x200
        };
    };
    uint64_t Spare21;                                                          //0x204
    struct list_entry_t QueueListEntry;                                      //0x208
    union
    {
        volatile uint64_t NextProcessor;                                       //0x218
        struct
        {
            uint64_t NextProcessorNumber : 31;                                   //0x218
            uint64_t clientReadyQueue : 1;                                       //0x218
        };
    };
    int32_t QueuePriority;                                                     //0x21c
    struct _KPROCESS* Process;                                              //0x220
    union
    {
        struct group_affinity_t UserAffinity;                                //0x228
        struct
        {
            uint8_t UserAffinityFill[10];                                     //0x228
            uint8_t PreviousMode;                                              //0x232
            uint8_t BasePriority;                                              //0x233
            union
            {
                uint8_t PriorityDecrement;                                     //0x234
                struct
                {
                    uint8_t ForegroundBoost : 4;                                //0x234
                    uint8_t UnusualBoost : 4;                                   //0x234
                };
            };
            uint8_t Preempted;                                                //0x235
            uint8_t AdjustReason;                                             //0x236
            uint8_t AdjustIncrement;                                           //0x237
        };
    };
    uint64_t AffinityVersion;                                              //0x238
    union
    {
        struct group_affinity_t Affinity;                                    //0x240
        struct
        {
            uint8_t AffinityFill[10];                                         //0x240
            uint8_t ApcStateIndex;                                            //0x24a
            uint8_t WaitBlockCount;                                           //0x24b
            uint64_t IdealProcessor;                                           //0x24c
        };
    };
    uint64_t NpxState;                                                     //0x250
    union
    {
        struct kapc_state_t SavedApcState;                                   //0x258
        struct
        {
            uint8_t SavedApcStateFill[43];                                    //0x258
            uint8_t WaitReason;                                               //0x283
            uint8_t SuspendCount;                                              //0x284
            uint8_t Saturation;                                                //0x285
            uint16_t SListFaultCount;                                         //0x286
        };
    };
    union
    {
        struct kapc_t SchedulerApc;                                          //0x288
        struct
        {
            uint8_t SchedulerApcFill0[1];                                     //0x288
            uint8_t ResourceIndex;                                            //0x289
        };
        struct
        {
            uint8_t SchedulerApcFill1[3];                                     //0x288
            uint8_t QuantumReset;                                             //0x28b
        };
        struct
        {
            uint8_t SchedulerApcFill2[4];                                     //0x288
            uint64_t KernelTime;                                               //0x28c
        };
        struct
        {
            uint8_t SchedulerApcFill3[64];                                    //0x288
            struct _KPRCB* volatile WaitPrcb;                               //0x2c8
        };
        struct
        {
            uint8_t SchedulerApcFill4[72];                                    //0x288
            void* LegoData;                                                 //0x2d0
        };
        struct
        {
            uint8_t SchedulerApcFill5[83];                                    //0x288
            uint8_t CallbackNestingLevel;                                     //0x2db
            uint64_t UserTime;                                                 //0x2dc
        };
    };
    struct kevent_t SuspendEvent;                                            //0x2e0
    struct list_entry_t ThreadListEntry;                                     //0x2f8
    struct list_entry_t MutantListHead;                                      //0x308
    uint8_t AbEntrySummary;                                                   //0x318
    uint8_t AbWaitEntryCount;                                                 //0x319
    uint8_t AbAllocationRegionCount;                                          //0x31a
    uint8_t SystemPriority;                                                    //0x31b
    uint64_t SecureThreadCookie;                                               //0x31c
    struct _KLOCK_ENTRY* LockEntries;                                       //0x320
    struct single_list_entry_t PropagateBoostsEntry;                         //0x328
    struct single_list_entry_t IoSelfBoostsEntry;                            //0x330
    uint8_t PriorityFloorCounts[16];                                          //0x338
    uint8_t PriorityFloorCountsReserved[16];                                  //0x348
    uint64_t PriorityFloorSummary;                                             //0x358
    volatile int32_t AbCompletedIoBoostCount;                                  //0x35c
    volatile int32_t AbCompletedIoQoSBoostCount;                               //0x360
    volatile int16_t KeReferenceCount;                                        //0x364
    uint8_t AbOrphanedEntrySummary;                                           //0x366
    uint8_t AbOwnedEntryCount;                                                //0x367
    uint64_t ForegroundLossTime;                                               //0x368
    union
    {
        struct list_entry_t GlobalForegroundListEntry;                       //0x370
        struct
        {
            struct single_list_entry_t ForegroundDpcStackListEntry;          //0x370
            uint64_t InGlobalForegroundList;                               //0x378
        };
    };
    uint64_t ReadOperationCount;                                            //0x380
    uint64_t WriteOperationCount;                                           //0x388
    uint64_t OtherOperationCount;                                           //0x390
    uint64_t ReadTransferCount;                                             //0x398
    uint64_t WriteTransferCount;                                            //0x3a0
    uint64_t OtherTransferCount;                                            //0x3a8
    struct _KSCB* QueuedScb;                                                //0x3b0
    volatile uint64_t ThreadTimerDelay;                                        //0x3b8
    union
    {
        volatile int32_t ThreadFlags3;                                         //0x3bc
        struct
        {
            uint64_t ThreadFlags3Reserved : 8;                                   //0x3bc
            uint64_t PpmPolicy : 2;                                              //0x3bc
            uint64_t ThreadFlags3Reserved2 : 22;                                 //0x3bc
        };
    };
    uint64_t TracingPrivate[1];                                            //0x3c0
    void* SchedulerAssist;                                                  //0x3c8
    void* volatile AbWaitObject;                                            //0x3d0
    uint64_t ReservedPreviousReadyTimeValue;                                   //0x3d8
    uint64_t KernelWaitTime;                                               //0x3e0
    uint64_t UserWaitTime;                                                 //0x3e8
    union
    {
        struct list_entry_t GlobalUpdateVpThreadPriorityListEntry;           //0x3f0
        struct
        {
            struct single_list_entry_t UpdateVpThreadPriorityDpcStackListEntry; //0x3f0
            uint64_t InGlobalUpdateVpThreadPriorityList;                   //0x3f8
        };
    };
    int32_t SchedulerAssistPriorityFloor;                                      //0x400
    uint64_t Spare28;                                                          //0x404
    uint64_t EndPadding[5];                                                //0x408
};

//0x10 bytes (sizeof)
struct _DISPATCHER_HEADER
{
    union
    {
        struct
        {
            uint8_t Type;                                                     //0x0
            union
            {
                uint8_t TimerControlFlags;                                    //0x1
                struct
                {
                    uint8_t Absolute : 1;                                       //0x1
                    uint8_t Coalescable : 1;                                    //0x1
                    uint8_t KeepShifting : 1;                                   //0x1
                    uint8_t EncodedTolerableDelay : 5;                          //0x1
                };
                uint8_t Abandoned;                                            //0x1
                uint8_t Signalling;                                           //0x1
            };
            union
            {
                uint8_t ThreadControlFlags;                                   //0x2
                struct
                {
                    uint8_t CpuThrottled : 1;                                   //0x2
                    uint8_t CycleProfiling : 1;                                 //0x2
                    uint8_t CounterProfiling : 1;                               //0x2
                    uint8_t Reserved : 5;                                       //0x2
                };
                uint8_t Hand;                                                 //0x2
                uint8_t Size;                                                 //0x2
            };
            union
            {
                uint8_t TimerMiscFlags;                                       //0x3
                struct
                {
                    uint8_t Index : 1;                                          //0x3
                    uint8_t Processor : 5;                                      //0x3
                    uint8_t Inserted : 1;                                       //0x3
                    volatile uint8_t Expired : 1;                               //0x3
                };
                uint8_t DebugActive;                                          //0x3
                struct
                {
                    uint8_t ActiveDR7 : 1;                                      //0x3
                    uint8_t Instrumented : 1;                                   //0x3
                    uint8_t Reserved2 : 4;                                      //0x3
                    uint8_t UmsScheduled : 1;                                   //0x3
                    uint8_t UmsPrimary : 1;                                     //0x3
                };
                uint8_t DpcActive;                                            //0x3
            };
        };
        volatile long Lock;                                                 //0x0
    };
    long SignalState;                                                       //0x4
    struct list_entry_t WaitListHead;                                        //0x8
};

//0x20 bytes (sizeof)
struct _KSEMAPHORE
{
    struct _DISPATCHER_HEADER Header;                                       //0x0
    long Limit;                                                             //0x18
};

//0x10 bytes (sizeof)
struct _CLIENT_ID
{
    void* UniqueProcess;                                                    //0x0
    void* UniqueThread;                                                     //0x8
};

//0x18 bytes (sizeof)
struct _PS_PROPERTY_SET
{
    struct list_entry_t ListHead;                                            //0x0
    uint64_t Lock;                                                         //0x10
};

//0x8 bytes (sizeof)
struct _EX_RUNDOWN_REF
{
    union
    {
        uint64_t Count;                                                    //0x0
        void* Ptr;                                                          //0x0
    };
};

//0x8 bytes (sizeof)
union _PS_CLIENT_SECURITY_CONTEXT
{
    uint64_t ImpersonationData;                                            //0x0
    void* ImpersonationToken;                                               //0x0
    uint64_t ImpersonationLevel : 2;                                         //0x0
    uint64_t EffectiveOnly : 1;                                              //0x0
};

//0x4 bytes (sizeof)
struct _EX_PUSH_LOCK
{
    union
    {
        struct
        {
            unsigned long Locked : 1;                                                 //0x0
            unsigned long Waiting : 1;                                                //0x0
            unsigned long Waking : 1;                                                 //0x0
            unsigned long MultipleShared : 1;                                         //0x0
            unsigned long Shared : 28;                                                //0x0
        };
        unsigned long Value;                                                        //0x0
        void* Ptr;                                                          //0x0
    };
};

//0x10 bytes (sizeof)
struct _RTL_RB_TREE
{
    struct _RTL_BALANCED_NODE* Root;                                        //0x0
    union
    {
        uint8_t Encoded : 1;                                                    //0x8
        struct _RTL_BALANCED_NODE* Min;                                     //0x8
    };
};

//0x10 bytes (sizeof)
struct _KLOCK_ENTRY_LOCK_STATE
{
    union
    {
        struct
        {
            uint64_t CrossThreadReleasable : 1;                              //0x0
            uint64_t Busy : 1;                                               //0x0
            uint64_t Reserved : 61;                                          //0x0
            uint64_t InTree : 1;                                             //0x0
        };
        void* LockState;                                                    //0x0
    };
    union
    {
        void* SessionState;                                                 //0x8
        struct
        {
            unsigned long SessionId;                                                //0x8
            unsigned long SessionPad;                                               //0xc
        };
    };
};

//0xc bytes (sizeof)
struct _RTL_BALANCED_NODE
{
    union
    {
        struct _RTL_BALANCED_NODE* Children[2];                             //0x0
        struct
        {
            struct _RTL_BALANCED_NODE* Left;                                //0x0
            struct _RTL_BALANCED_NODE* Right;                               //0x4
        };
    };
    union
    {
        struct
        {
            uint8_t Red : 1;                                                    //0x8
            uint8_t Balance : 2;                                                //0x8
        };
        unsigned long ParentValue;                                                  //0x8
    };
};

//0x60 bytes (sizeof)
struct _KLOCK_ENTRY
{
    union
    {
        struct _RTL_BALANCED_NODE TreeNode;                                 //0x0
        struct single_list_entry_t FreeListEntry;                            //0x0
    };
    union
    {
        unsigned long EntryFlags;                                                   //0x18
        struct
        {
            unsigned char EntryOffset;                                              //0x18
            union
            {
                unsigned char ThreadLocalFlags;                                     //0x19
                struct
                {
                    unsigned char WaitingBit : 1;                                     //0x19
                    unsigned char Spare0 : 7;                                         //0x19
                };
            };
            union
            {
                unsigned char AcquiredByte;                                         //0x1a
                unsigned char AcquiredBit : 1;                                        //0x1a
            };
            union
            {
                unsigned char CrossThreadFlags;                                     //0x1b
                struct
                {
                    unsigned char HeadNodeBit : 1;                                    //0x1b
                    unsigned char IoPriorityBit : 1;                                  //0x1b
                    unsigned char Spare1 : 6;                                         //0x1b
                };
            };
        };
        struct
        {
            unsigned long StaticState : 8;                                            //0x18
            unsigned long AllFlags : 24;                                              //0x18
        };
    };
    unsigned long SpareFlags;                                                       //0x1c
    union
    {
        struct _KLOCK_ENTRY_LOCK_STATE LockState;                           //0x20
        void* volatile LockUnsafe;                                          //0x20
        struct
        {
            volatile unsigned char CrossThreadReleasableAndBusyByte;                //0x20
            unsigned char Reserved[6];                                              //0x21
            volatile unsigned char InTreeByte;                                      //0x27
            union
            {
                void* SessionState;                                         //0x28
                struct
                {
                    unsigned long SessionId;                                        //0x28
                    unsigned long SessionPad;                                       //0x2c
                };
            };
        };
    };
    union
    {
        struct
        {
            struct _RTL_RB_TREE OwnerTree;                                  //0x30
            struct _RTL_RB_TREE WaiterTree;                                 //0x40
        };
        char CpuPriorityKey;                                                //0x30
    };
    uint64_t EntryLock;                                                    //0x50
    union
    {
        unsigned short AllBoosts;                                                   //0x58
        struct
        {
            unsigned short IoBoost : 1;                                               //0x58
            unsigned short CpuBoostsBitmap : 15;                                      //0x58
        };
    };
    unsigned short IoNormalPriorityWaiterCount;                                     //0x5a
    unsigned short SparePad;                                                        //0x5c
};

//0x898 bytes (sizeof)
typedef struct ethread
{
    struct kthread Tcb;                                                    //0x0
    union ularge_integer_t CreateTime;                                        //0x430
    union
    {
        union ularge_integer_t ExitTime;                                      //0x438
        struct list_entry_t KeyedWaitChain;                                  //0x438
    };
    union
    {
        struct list_entry_t PostBlockList;                                   //0x448
        struct
        {
            void* ForwardLinkShadow;                                        //0x448
            void* StartAddress;                                             //0x450
        };
    };
    union
    {
        struct _TERMINATION_PORT* TerminationPort;                          //0x458
        struct _ETHREAD* ReaperLink;                                        //0x458
        void* KeyedWaitValue;                                               //0x458
    };
    uint64_t ActiveTimerListLock;                                          //0x460
    struct list_entry_t ActiveTimerListHead;                                 //0x468
    struct _CLIENT_ID Cid;                                                  //0x478
    union
    {
        struct _KSEMAPHORE KeyedWaitSemaphore;                              //0x488
        struct _KSEMAPHORE AlpcWaitSemaphore;                               //0x488
    };
    union _PS_CLIENT_SECURITY_CONTEXT ClientSecurity;                       //0x4a8
    struct list_entry_t IrpList;                                             //0x4b0
    uint64_t TopLevelIrp;                                                  //0x4c0
    struct _DEVICE_OBJECT* DeviceToVerify;                                  //0x4c8
    void* Win32StartAddress;                                                //0x4d0
    void* ChargeOnlySession;                                                //0x4d8
    void* LegacyPowerObject;                                                //0x4e0
    struct list_entry_t ThreadListEntry;                                     //0x4e8
    struct _EX_RUNDOWN_REF RundownProtect;                                  //0x4f8
    struct _EX_PUSH_LOCK ThreadLock;                                        //0x500
    uint32_t ReadClusterSize;                                                  //0x508
    volatile long MmLockOrdering;                                           //0x50c
    union
    {
        uint32_t CrossThreadFlags;                                             //0x510
        struct
        {
            uint32_t Terminated : 1;                                             //0x510
            uint32_t ThreadInserted : 1;                                         //0x510
            uint32_t HideFromDebugger : 1;                                       //0x510
            uint32_t ActiveImpersonationInfo : 1;                                //0x510
            uint32_t HardErrorsAreDisabled : 1;                                  //0x510
            uint32_t BreakOnTermination : 1;                                     //0x510
            uint32_t SkipCreationMsg : 1;                                        //0x510
            uint32_t SkipTerminationMsg : 1;                                     //0x510
            uint32_t CopyTokenOnOpen : 1;                                        //0x510
            uint32_t ThreadIoPriority : 3;                                       //0x510
            uint32_t ThreadPagePriority : 3;                                     //0x510
            uint32_t RundownFail : 1;                                            //0x510
            uint32_t UmsForceQueueTermination : 1;                               //0x510
            uint32_t IndirectCpuSets : 1;                                        //0x510
            uint32_t DisableDynamicCodeOptOut : 1;                               //0x510
            uint32_t ExplicitCaseSensitivity : 1;                                //0x510
            uint32_t PicoNotifyExit : 1;                                         //0x510
            uint32_t DbgWerUserReportActive : 1;                                 //0x510
            uint32_t ForcedSelfTrimActive : 1;                                   //0x510
            uint32_t SamplingCoverage : 1;                                       //0x510
            uint32_t ReservedCrossThreadFlags : 8;                               //0x510
        };
    };
    union
    {
        uint32_t SameThreadPassiveFlags;                                       //0x514
        struct
        {
            uint32_t ActiveExWorker : 1;                                         //0x514
            uint32_t MemoryMaker : 1;                                            //0x514
            uint32_t StoreLockThread : 2;                                        //0x514
            uint32_t ClonedThread : 1;                                           //0x514
            uint32_t KeyedEventInUse : 1;                                        //0x514
            uint32_t SelfTerminate : 1;                                          //0x514
            uint32_t RespectIoPriority : 1;                                      //0x514
            uint32_t ActivePageLists : 1;                                        //0x514
            uint32_t SecureContext : 1;                                          //0x514
            uint32_t ZeroPageThread : 1;                                         //0x514
            uint32_t WorkloadClass : 1;                                          //0x514
            uint32_t ReservedSameThreadPassiveFlags : 20;                        //0x514
        };
    };
    union
    {
        uint32_t SameThreadApcFlags;                                           //0x518
        struct
        {
            uint8_t OwnsProcessAddressSpaceExclusive : 1;                       //0x518
            uint8_t OwnsProcessAddressSpaceShared : 1;                          //0x518
            uint8_t HardFaultBehavior : 1;                                      //0x518
            volatile uint8_t StartAddressInvalid : 1;                           //0x518
            uint8_t EtwCalloutActive : 1;                                       //0x518
            uint8_t SuppressSymbolLoad : 1;                                     //0x518
            uint8_t Prefetching : 1;                                            //0x518
            uint8_t OwnsVadExclusive : 1;                                       //0x518
            uint8_t SystemPagePriorityActive : 1;                               //0x519
            uint8_t SystemPagePriority : 3;                                     //0x519
            uint8_t AllowUserWritesToExecutableMemory : 1;                      //0x519
            uint8_t AllowKernelWritesToExecutableMemory : 1;                    //0x519
            uint8_t OwnsVadShared : 1;                                          //0x519
        };
    };
    uint8_t CacheManagerActive;                                               //0x51c
    uint8_t DisablePageFaultClustering;                                       //0x51d
    uint8_t ActiveFaultCount;                                                 //0x51e
    uint8_t LockOrderState;                                                   //0x51f
    uint32_t PerformanceCountLowReserved;                                      //0x520
    long PerformanceCountHighReserved;                                      //0x524
    uint64_t AlpcMessageId;                                                //0x528
    union
    {
        void* AlpcMessage;                                                  //0x530
        uint32_t AlpcReceiveAttributeSet;                                      //0x530
    };
    struct list_entry_t AlpcWaitListEntry;                                   //0x538
    long ExitStatus;                                                        //0x548
    uint32_t CacheManagerCount;                                                //0x54c
    uint32_t IoBoostCount;                                                     //0x550
    uint32_t IoQoSBoostCount;                                                  //0x554
    uint32_t IoQoSThrottleCount;                                               //0x558
    uint32_t KernelStackReference;                                             //0x55c
    struct list_entry_t BoostList;                                           //0x560
    struct list_entry_t DeboostList;                                         //0x570
    uint64_t BoostListLock;                                                //0x580
    uint64_t IrpListLock;                                                  //0x588
    void* ReservedForSynchTracking;                                         //0x590
    struct single_list_entry_t CmCallbackListHead;                           //0x598
    struct _GUID* ActivityId;                                               //0x5a0
    struct single_list_entry_t SeLearningModeListHead;                       //0x5a8
    void* VerifierContext;                                                  //0x5b0
    void* AdjustedClientToken;                                              //0x5b8
    void* WorkOnBehalfThread;                                               //0x5c0
    struct _PS_PROPERTY_SET PropertySet;                                    //0x5c8
    void* PicoContext;                                                      //0x5e0
    uint64_t UserFsBase;                                                   //0x5e8
    uint64_t UserGsBase;                                                   //0x5f0
    struct _THREAD_ENERGY_VALUES* EnergyValues;                             //0x5f8
    union
    {
        uint64_t SelectedCpuSets;                                          //0x600
        uint64_t* SelectedCpuSetsIndirect;                                 //0x600
    };
    struct _EJOB* Silo;                                                     //0x608
    struct unicode_string_t* ThreadName;                                     //0x610
    struct _CONTEXT* SetContextState;                                       //0x618
    uint32_t LastExpectedRunTime;                                              //0x620
    uint32_t HeapData;                                                         //0x624
    struct list_entry_t OwnerEntryListHead;                                  //0x628
    uint64_t DisownedOwnerEntryListLock;                                   //0x638
    struct list_entry_t DisownedOwnerEntryListHead;                          //0x640
    struct _KLOCK_ENTRY LockEntries[6];                                     //0x650
    void* CmDbgInfo;                                                        //0x890
};

typedef struct _NMI_CONTEXT
{
    uint64_t  interrupted_rip;
    uint64_t  interrupted_rsp;
    kthread* kthread;
    uint32_t  callback_count;
    bool user_thread;
} NMI_CONTEXT, * PNMI_CONTEXT;

typedef struct
{
    /**
     * Reserved bits. Set to 0.
     */
    uint32_t Reserved0;

    /**
     * Stack pointer for privilege level 0.
     */
    uint64_t Rsp0;

    /**
     * Stack pointer for privilege level 1.
     */
    uint64_t Rsp1;

    /**
     * Stack pointer for privilege level 2.
     */
    uint64_t Rsp2;

    /**
     * Reserved bits. Set to 0.
     */
    uint64_t Reserved1;

    /**
     * Interrupt stack table pointer (1).
     */
    uint64_t Ist1;

    /**
     * Interrupt stack table pointer (2).
     */
    uint64_t Ist2;

    /**
     * Interrupt stack table pointer (3).
     */
    uint64_t Ist3;

    /**
     * Interrupt stack table pointer (4).
     */
    uint64_t Ist4;

    /**
     * Interrupt stack table pointer (5).
     */
    uint64_t Ist5;

    /**
     * Interrupt stack table pointer (6).
     */
    uint64_t Ist6;

    /**
     * Interrupt stack table pointer (7).
     */
    uint64_t Ist7;

    /**
     * Reserved bits. Set to 0.
     */
    uint64_t Reserved2;

    /**
     * Reserved bits. Set to 0.
     */
    uint16_t Reserved3;

    /**
     * The 16-bit offset to the I/O permission bit map from the 64-bit TSS base.
     */
    uint16_t IoMapBase;
} TASK_STATE_SEGMENT_64;

typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;
}
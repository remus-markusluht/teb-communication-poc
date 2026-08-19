#include "page2.h"

#define PAGE_OFFSET_SIZE 12
static const UINT64 PMASK = (~0xfull << 8) & 0xfffffffffull;

NTSTATUS ReadPhysical(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_read) {
	// Check for null pointers
	if (!target_address || !buffer || !bytes_read) {
		return STATUS_INVALID_PARAMETER;
	}

	// Check for a valid size
	if (size == oxorany(0)) {
		*bytes_read = oxorany(0);  // No bytes to read
		return STATUS_SUCCESS;
	}

	MM_COPY_ADDRESS to_read = { 0 };
	to_read.PhysicalAddress.QuadPart = (LONGLONG)target_address;

	// Call the memory copy function and check its return value
	NTSTATUS status = mm_copy_memory(buffer, to_read, size, oxorany(MM_COPY_MEMORY_PHYSICAL), bytes_read);
	if (!NT_SUCCESS(status)) {
		// Log error for debugging
		return status;
	}

	// Ensure bytes_read reflects the actual number of bytes read
	if (*bytes_read > size) {
		*bytes_read = size;  // Cap at requested size to prevent overflow
	}

	return STATUS_SUCCESS;
}

UINT64 Helper::TranslateLinear(UINT64 directoryTableBase, UINT64 virtualAddress) {
	// Check for valid directory table base
	if (directoryTableBase & oxorany(0xf)) {
		return 0; // Invalid base address
	}

	// Extract offsets for paging
	UINT64 pageOffset = virtualAddress & ((1ULL << PAGE_OFFSET_SIZE) - oxorany(1));
	UINT64 pte = (virtualAddress >> oxorany(12)) & oxorany(0x1FF);
	UINT64 pt = (virtualAddress >> oxorany(21)) & oxorany(0x1FF);
	UINT64 pd = (virtualAddress >> oxorany(30)) & oxorany(0x1FF);
	UINT64 pdp = (virtualAddress >> oxorany(39)) & oxorany(0x1FF);

	SIZE_T readsize = oxorany(0);
	UINT64 pdpe = oxorany(0);

	// Read PDP entry
	NTSTATUS status = ReadPhysical(PVOID(directoryTableBase + oxorany(8) * pdp), &pdpe, sizeof(pdpe), &readsize);
	if (!NT_SUCCESS(status) || readsize != sizeof(pdpe) || !(pdpe & oxorany(1))) {
		return oxorany(0); // Invalid PDP entry
	}

	UINT64 pde = oxorany(0);
	status = ReadPhysical(PVOID((pdpe & PMASK) + oxorany(8) * pd), &pde, sizeof(pde), &readsize);
	if (!NT_SUCCESS(status) || readsize != sizeof(pde) || !(pde & oxorany(1))) {
		return oxorany(0); // Invalid PDE entry
	}

	// Handle 1GB large page
	if (pde & oxorany(0x80)) {
		return (pde & (~0ULL << oxorany(42) >> oxorany(12))) + (virtualAddress & ~(~0ULL << oxorany(30)));
	}

	UINT64 pteAddr = oxorany(0);
	status = ReadPhysical(PVOID((pde & PMASK) + oxorany(8) * pt), &pteAddr, sizeof(pteAddr), &readsize);
	if (!NT_SUCCESS(status) || readsize != sizeof(pteAddr) || !(pteAddr & oxorany(1))) {
		return oxorany(0); // Invalid PTE entry
	}

	// Handle 2MB large page
	if (pteAddr & oxorany(0x80)) {
		return (pteAddr & PMASK) + (virtualAddress & ~(~0ULL << oxorany(21)));
	}

	virtualAddress = oxorany(0);
	status = ReadPhysical(PVOID((pteAddr & PMASK) + oxorany(8) * pte), &virtualAddress, sizeof(virtualAddress), &readsize);
	if (!NT_SUCCESS(status) || readsize != sizeof(virtualAddress)) {
		return oxorany(0); // Invalid virtual address
	}

	virtualAddress &= PMASK;

	if (!virtualAddress) {
		return oxorany(0); // No valid address found
	}

	return virtualAddress + pageOffset;
}


ULONG64 Helper::FindMin(INT32 g, SIZE_T f) {
	INT32 h = (INT32)f;
	ULONG64 result = oxorany(0);

	result = (((g) < (h)) ? (g) : (h));

	return result;
}

void Helper::CustomMemCopy(const void* dstp, const void* srcp, SIZE_T len) {
	ULONG* dst = (ULONG*)dstp;
	ULONG* src = (ULONG*)srcp;
	SIZE_T i, tail;

	for (i = oxorany(0); i < (len / sizeof(ULONG)); i++)
		*dst++ = *src++;

	tail = len & (sizeof(ULONG) - oxorany(1));
	if (tail) {

		UCHAR* dstb = (UCHAR*)dstp;
		UCHAR* srcb = (UCHAR*)srcp;

		for (i = len - tail; i < len; i++)
			dstb[i] = srcb[i];
	}
}
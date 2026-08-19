#include "read.h"

NTSTATUS Read2(PVOID target, PVOID buffer, SIZE_T size, SIZE_T* bytesRead) {
	// Check for null pointers
	if (!target || !buffer || !bytesRead) {
		return oxorany(STATUS_INVALID_PARAMETER);
	}

	PHYSICAL_ADDRESS AddrToWrite = { oxorany(0) };
	AddrToWrite.QuadPart = LONGLONG(target);

	// Map the memory
	PVOID pmapped_mem = mm_map_io_space_ex(AddrToWrite, size, oxorany(PAGE_READWRITE));
	if (!pmapped_mem) {
		return oxorany(STATUS_UNSUCCESSFUL);
	}

	// Ensure size does not exceed buffer limits
	SIZE_T bytes_to_copy = min(size, oxorany(PAGE_SIZE));  // Adjust based on the maximum you can read
	if (bytes_to_copy > size) {
		bytes_to_copy = size;
	}

	// Use custom memcpy with size check
	Helper::CustomMemCopy(buffer, pmapped_mem, bytes_to_copy);

	*bytesRead = size;
	mm_unmap_io_space(pmapped_mem, size);  // Unmap the memory

	return STATUS_SUCCESS;
}

NTSTATUS Read::ReadMemory(PVOID target, PVOID buffer, SIZE_T size, UINT64 savedCR3) {
	if (!target || !buffer || !size || !savedCR3) {
		return STATUS_INVALID_PARAMETER;
	}

	SIZE_T currentOffset = oxorany(0);
	SIZE_T totalSize = size;

	while (totalSize > oxorany(0)) {
		INT64 currentPhysicalAddress = Helper::TranslateLinear(savedCR3, (UINT64)target + currentOffset);
		if (!currentPhysicalAddress) {
			return oxorany(STATUS_UNSUCCESSFUL);
		}

		ULONG64 readSize = Helper::FindMin(oxorany(PAGE_SIZE) - (currentPhysicalAddress & oxorany(0xFFF)), totalSize);
		SIZE_T bytesRead = oxorany(0);

		NTSTATUS status = Read2((PVOID)currentPhysicalAddress, (PVOID)((UINT64)buffer + currentOffset), readSize, &bytesRead);

		if (!NT_SUCCESS(status)) {
			return status;
		}

		if (!bytesRead) {
			break;
		}

		totalSize -= bytesRead;
		currentOffset += bytesRead;
	}

	if (!totalSize)
		return oxorany(STATUS_SUCCESS);
	else
		return oxorany(STATUS_UNSUCCESSFUL);
}
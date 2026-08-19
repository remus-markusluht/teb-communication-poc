#include "write.h"

NTSTATUS write(PVOID target, PVOID buffer, SIZE_T size, SIZE_T* bytes_read) {
	if (!target)
		return STATUS_UNSUCCESSFUL;

	PHYSICAL_ADDRESS AddrToWrite = { oxorany(0) };
	AddrToWrite.QuadPart = LONGLONG(target);

	PVOID pmapped_mem = mm_map_io_space_ex(AddrToWrite, size, oxorany(PAGE_READWRITE));

	if (!pmapped_mem)
		return oxorany(STATUS_UNSUCCESSFUL);

	Helper::CustomMemCopy(pmapped_mem, buffer, size);

	*bytes_read = size;
	mm_unmap_io_space(pmapped_mem, size);
	return oxorany(STATUS_SUCCESS);
}

NTSTATUS Write::WriteMemory(PVOID target, PVOID buffer, SIZE_T size, UINT64 savedCR3) {
	if (!target || !buffer || !size || !savedCR3) {
		return oxorany(STATUS_INVALID_PARAMETER);
	}

	SIZE_T currentOffset = oxorany(0);
	SIZE_T totalSize = size;

	while (totalSize > oxorany(0)) {
		INT64 currentPhysicalAddress = Helper::TranslateLinear(savedCR3, (UINT64)target + currentOffset);
		if (!currentPhysicalAddress) {
			return STATUS_UNSUCCESSFUL;
		}

		ULONG64 write_size = Helper::FindMin(PAGE_SIZE - (currentPhysicalAddress & oxorany(0xFFF)), totalSize);
		SIZE_T bytes_written = oxorany(0);

		NTSTATUS status = write((PVOID)currentPhysicalAddress, (PVOID)((UINT64)buffer + currentOffset), write_size, &bytes_written);

		if (!NT_SUCCESS(status)) {
			return status;
		}

		if (bytes_written == oxorany(0)) {
			break;
		}

		totalSize -= bytes_written;
		currentOffset += bytes_written;
	}

	if (!totalSize)
		return oxorany(STATUS_SUCCESS);
	else
		return oxorany(STATUS_UNSUCCESSFUL);
}
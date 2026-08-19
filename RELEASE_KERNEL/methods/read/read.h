#pragma once
#include "../../Includes.h"

namespace Read {
	NTSTATUS ReadMemory(PVOID target, PVOID buffer, SIZE_T size, UINT64 savedCR3);
}
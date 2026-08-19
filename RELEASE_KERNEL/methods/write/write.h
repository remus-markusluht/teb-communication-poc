#pragma once
#include "../../Includes.h"

namespace Write
{
	NTSTATUS WriteMemory(PVOID target, PVOID buffer, SIZE_T size, UINT64 savedCR3);
}
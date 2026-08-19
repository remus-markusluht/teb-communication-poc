#pragma once
#include "../../Includes.h"
#include "../../module/module.h"
namespace CR3 {
	UINT64 GetCR3(void* BaseAddress);
	NTSTATUS InitMmpfnDatabase();
}
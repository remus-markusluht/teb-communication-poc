#pragma once
#include "../../Includes.h"

namespace moduleaddress {
	uintptr_t GetModuleAddress(PEPROCESS client, char* module_name);
}
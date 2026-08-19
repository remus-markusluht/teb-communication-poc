#pragma once
#include "../../Includes.h"

namespace rwx
{
	bool discover_next_executable_section(uint64_t image_base, uint64_t* executable_section_base, uint64_t* executable_section_size);
}
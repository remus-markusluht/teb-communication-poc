#include "rwx.h"

namespace rwx
{
	bool discover_next_executable_section(uint64_t image_base, uint64_t* executable_section_base, uint64_t* executable_section_size)
	{
		SPOOF_FUNC;

		bool has_found_start_section_base = false;
		if (*executable_section_base == 0)
		{
			has_found_start_section_base = true;
		}

		auto driver_dos_header = reinterpret_cast<dos_header_t*>(image_base);
		if (!driver_dos_header->is_valid())
		{
			silence(E("[sonos::DiscoverNextExecutableSection] Failed DriverDosHeader\n"));
			return false;
		}

		auto driver_nt_header = reinterpret_cast<nt_headers_t*>(reinterpret_cast<ULONG_PTR>(driver_dos_header) + driver_dos_header->m_lfanew);
		if (!driver_nt_header->is_valid())
		{
			silence(E("[sonos::DiscoverNextExecutableSection] Failed DriverNtHeader\n"));
			return false;
		}

		auto driver_section_header = reinterpret_cast<section_header_t*>(
			reinterpret_cast<uintptr_t>(driver_nt_header) +
			driver_nt_header->m_size_of_optional_header + oxorany(0x18));

		for (int i = 0; i < driver_nt_header->m_number_of_sections; i++)
		{
			auto current_section_base = reinterpret_cast<uint64_t>(driver_dos_header) + driver_section_header[i].m_virtual_address;
			if (has_found_start_section_base == FALSE && current_section_base == *executable_section_base)
			{
				has_found_start_section_base = TRUE;
				continue;
			}
			else if (has_found_start_section_base && driver_section_header[i].m_characteristics & 0x20000000 /*IMAGE_SCN_MEM_EXECUTE*/)
			{
				*executable_section_base = current_section_base;
				*executable_section_size = driver_section_header[i].m_size_of_raw_data;
				break;
			}
		}
	}
}
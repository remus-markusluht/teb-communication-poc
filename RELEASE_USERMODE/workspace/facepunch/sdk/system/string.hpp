#pragma once

namespace system_collections {

	class string : public sdk::c_base_class {
	public:
		declare_member( int, _string_length, 0x10 );
		declare_member( char, _first_char, 0x14 );
	};
}
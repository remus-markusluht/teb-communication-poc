#pragma once

namespace system_collections {

	template<typename T>
	class nullable : public sdk::c_base_class {
		declare_member( bool, has_value, 0x0 );
		declare_member( T, value, 0x1 );
	};
}
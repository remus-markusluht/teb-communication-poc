#pragma once

namespace system_collections {

	template <typename T>
	class buffer_list : public sdk::c_base_class {
	public:
		declare_member( array<T>*, buffer, 0x10 );
		declare_member( int, count, 0x18 );
	};
}
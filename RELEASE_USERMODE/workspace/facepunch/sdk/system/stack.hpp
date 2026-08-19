#pragma once

namespace system_collections {

	template <typename T>
	class stack : public sdk::c_base_class {
	public:
		declare_member( array<T>*, _array, 0x10 );
		declare_member( int, _size, 0x18 );
	};
}
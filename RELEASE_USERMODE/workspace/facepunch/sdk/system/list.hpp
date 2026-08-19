#pragma once

namespace system_collections {

	template <typename T>
	class list : public sdk::c_base_class {
	public:
		declare_member( array<T>*, _items, 0x10 );
		declare_member( int, _size, 0x18 );
	};
}
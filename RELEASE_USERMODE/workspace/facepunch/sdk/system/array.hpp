#pragma once

namespace system_collections {

	template <typename T>
	class array : public sdk::c_base_class {
	public:
		declare_member( int, size, 0x18 );

	public:
		T get( int index ) const {
			return g_vm->read<T>( current_address + 0x20 + ( index * 0x8 ) );
		}
	};
}
#pragma once

namespace unity {

	template<typename T>
	class c_dynamic_list {
	public:
		T data;
		u64 label;
		int size;

	public:
		T get( int index ) const {
			return g_vm->read<T>( reinterpret_cast< u64 >( data ) + ( 0x8 * index ) );
		}
	};
}
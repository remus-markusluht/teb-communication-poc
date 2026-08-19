#pragma once

namespace unity {

	template <typename T>
	class c_dynamic_array {
	public:
		T data;
		u64 label;
		size_t size;
		size_t capacity;

	public:
		T get( int index ) const {
			return g_vm->read<T>( reinterpret_cast< u64 >( data ) + ( 0x10 * index + 0x8 ) );
		}
	};
}
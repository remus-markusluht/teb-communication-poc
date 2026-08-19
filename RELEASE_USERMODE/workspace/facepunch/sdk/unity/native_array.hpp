#pragma once

namespace unity {

	template <typename T>
	struct native_array {
	public:
		T data;
		u32 size;
		u32 capacity;

	public:
		T get( u32 index ) const {
			return g_vm->read<T>( reinterpret_cast< u64 >( data ) + 0x8 * index );
		}
	};
}
#pragma once

namespace system_collections {

	template<typename TKey, typename TValue>
	class dictionary : public sdk::c_base_class {
	public:
		declare_member( dictionary*, _entries, 0x18 );
		declare_member( int, _count, 0x18 );

	public:
		TKey key( int index ) const {
			return g_vm->read<TKey>( current_address + 0x18 * index + 0x28 );
		}

		TValue value( int index ) const {
			return g_vm->read<TValue>( current_address + 0x18 * index + 0x30 );
		}

		void value( int index, TValue value ) const {
			g_vm->write<TValue>( current_address + 0x18 * index + 0x30, value );
		}
	};
}
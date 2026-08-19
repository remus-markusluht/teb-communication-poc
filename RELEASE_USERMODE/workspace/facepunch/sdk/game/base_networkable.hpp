#pragma once

namespace sdk {

	class c_base_networkable;

	inline system_collections::buffer_list<c_base_networkable*>* entities = nullptr;

	class c_base_networkable_entity_realm : public c_base_mono_behaviour {
	public:
		using entity_list_t = system_collections::list_dictionary<u32, c_base_networkable*>*;
		declare_member( entity_list_t, entity_list, 0x0 );
	};

	class c_base_networkable : public c_base_mono_behaviour {
	public:
		inline static c_base_networkable* klass( )
		{
			static c_base_networkable* ins = nullptr;
			if ( !ins )
				ins = g_vm->read_chain<c_base_networkable*>( g_vm->game_assembly, { 0x0, 0xB8 } );

			return ins;
		}

		declare_member( c_base_networkable_entity_realm*, client_entities, 0x0 );
		declare_member( u32, prefab_id, 0x0 );
	};
}
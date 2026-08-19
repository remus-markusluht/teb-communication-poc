#pragma once

namespace unity {

	class c_game_object : public c_object {
	public:
		// 48 8B 41 ? 49 C1 E0 ? 4C 03 41 (QueryComponent)
		declare_member( c_dynamic_array<c_component*>, components, 0x30 );

		// E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 85 C0 74 ? 48 8B CF (GameObject::SetName)
		declare_member( u64, name_pointer, 0x60 );

		// 0F B7 48 ? 48 8B 05 (GameObject_Get_Custom_PropTag)
		declare_member( WORD, tag, 0x54 );

		// C6 47 ? ? 48 8B CF E8 ? ? ? ? 48 81 C4 (GameObject::Activate)
		declare_member( bool, is_active, 0x56 );

	public:

	};
}
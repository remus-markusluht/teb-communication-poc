#pragma once

namespace unity {

	class c_game_object;

	class c_component : public c_object {
	public:
		declare_member( c_game_object*, game_object, 0x30 );
		declare_member( c_component*, scripting_object, 0x28 );
		declare_member( c_dynamic_list<c_component*>, child_components, 0x70 );
	};
}
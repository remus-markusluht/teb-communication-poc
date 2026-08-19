#pragma once

namespace sdk {

	enum class c_lifestate : u32 {
		alive = 0,
		dead = 1
	};

	class c_base_combat_entity : public c_base_class {
	public:
		declare_member( float, _max_health, 0x0 );
		declare_member( float, _health, 0x0 );
		declare_member( float, start_health, 0x0 );

		declare_member( c_lifestate, lifestate, 0x0 );

		declare_member( int, last_notify_frame, 0x0 );
	};
}
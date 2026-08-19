#pragma once

namespace sdk {

    enum player_flags : u32 {
        unused1 = 1,
        unused2 = 2,
        is_admin = 4,
        receiving_snapshot = 8,
        sleeping = 16,
        spectating = 32,
        wounded = 64,
        is_developer = 128,
        connected = 256,
        third_person_viewmode = 1024,
        eyes_viewmode = 2048,
        chat_mute = 4096,
        no_sprint = 8192,
        aiming = 16384,
        display_sash = 32768,
        relaxed = 65536,
        safe_zone = 131072,
        server_fall = 262144,
        incapacitated = 524288,
        workbench1 = 1048576,
        workbench2 = 2097152,
        workbench3 = 4194304,
        voice_range_boost = 8388608,
        modify_clan = 16777216,
        loading_after_transfer = 33554432,
        no_respawn_zone = 67108864,
        is_in_tutorial = 134217728,
        is_restrained = 268435456,
        creative_mode = 536870912,
        waiting_for_gesture_interaction = 1073741824,
        ragdolling = 2147483648
    };

    enum base_player_components : u32 {
        transform = 0,
        base_player = 1,
        player_inventory = 3,
        player_eyes = 4,
    };

    class c_base_player : public c_base_combat_entity {
    public:
        declare_member( ulong, cl_active_item, 0x0 );
        declare_member( ulong, current_team, 0x0 );
        declare_member( ulong, user_id, 0x0 );

        declare_member( unity::c_game_object*, _looking_at, 0x0 );

        declare_member( system_collections::string*, username, 0x0 );
        declare_member( system_collections::string*, steam_id, 0x0 );

        declare_member( float, clothing_move_speed_reduction, 0x0 );
        declare_member( float, last_headshot_sound_time, 0x0 );

        declare_member( bool, clothing_blocks_aiming, 0x0 );

        declare_member( int, flags, 0x0 );
        declare_member( u64, last_sent_tick_time, 0x0 );
    };
}
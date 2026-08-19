#ifndef SDK_HPP
#define SDK_HPP

#define current_address reinterpret_cast<u64>( this )

#include <workspace/facepunch/sdk/game/base_class.hpp>

#define declare_member(type, name, offset) \
    auto name ( ) const -> type { \
        if ( !sdk::c_base_class::is_valid_address( current_address ) ) return { }; \
        return g_vm->read<type>( current_address + offset ); \
    } \
    auto set_##name ( type val ) const -> void { \
        if ( !sdk::c_base_class::is_valid_address( current_address ) ) return; \
        g_vm->write<type>( current_address + offset, val ); \
    }

#define declare_static_member(type, name, offset) \
    static auto name ( ) -> type { \
        auto* instance = klass( ); \
        if ( !instance || !sdk::c_base_class::is_valid_address( instance->get_current_class( ) ) ) return { }; \
        return g_vm->read<type>( instance->get_current_class( ) + offset ); \
    } \
    static auto set_##name ( type val ) -> void { \
        auto* instance = klass( ); \
        if ( !instance || !sdk::c_base_class::is_valid_address( instance->get_current_class( ) ) ) return; \
        g_vm->write<type>( instance->get_current_class( ) + offset, val ); \
    }

/* System SDK */

#include <workspace/facepunch/sdk/system/dictionary.hpp>
#include <workspace/facepunch/sdk/system/array.hpp>
#include <workspace/facepunch/sdk/system/stack.hpp>
#include <workspace/facepunch/sdk/system/buffer_list.hpp>
#include <workspace/facepunch/sdk/system/list_dictionary.hpp>
#include <workspace/facepunch/sdk/system/list_hash_set.hpp>
#include <workspace/facepunch/sdk/system/list_component.hpp>
#include <workspace/facepunch/sdk/system/hash_set.hpp>
#include <workspace/facepunch/sdk/system/list.hpp>
#include <workspace/facepunch/sdk/system/string.hpp>
#include <workspace/facepunch/sdk/system/nullable.hpp>
#include <workspace/facepunch/sdk/system/t_object.hpp>
#include <workspace/facepunch/sdk/system/singleton_component.hpp>

/* Il2CPP SDK */

#include <workspace/facepunch/sdk/il2cpp/klass.hpp>
#include <workspace/facepunch/sdk/il2cpp/object.hpp>

/* Unity SDK */

#include <workspace/facepunch/sdk/unity/dynamic_array.hpp>
#include <workspace/facepunch/sdk/unity/native_array.hpp>
#include <workspace/facepunch/sdk/unity/dynamic_list.hpp>

#include <workspace/facepunch/sdk/unity/object.hpp>
#include <workspace/facepunch/sdk/unity/component.hpp>
#include <workspace/facepunch/sdk/unity/game_object.hpp>

#include <workspace/facepunch/sdk/unity/behaviour.hpp>
#include <workspace/facepunch/sdk/unity/mono_behaviour.hpp>
#include <workspace/facepunch/sdk/unity/ui_behaviour.hpp>

#include <workspace/facepunch/sdk/unity/bounds.hpp>
#include <workspace/facepunch/sdk/unity/text.hpp>

/* Game SDK */

#include <workspace/facepunch/sdk/game/rust_camera.hpp>
#include <workspace/facepunch/sdk/game/camera.hpp>
#include <workspace/facepunch/sdk/game/main_camera.hpp>

#include <workspace/facepunch/sdk/game/facepunch_behaviour.hpp>
#include <workspace/facepunch/sdk/game/base_mono_behaviour.hpp>


#include <workspace/facepunch/sdk/game/base_networkable.hpp>

#include <workspace/facepunch/sdk/game/base_combat_entity.hpp>

#include <workspace/facepunch/sdk/game/base_player.hpp>

#endif // !SDK_HPP

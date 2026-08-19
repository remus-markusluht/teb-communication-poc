#ifndef PLAYERS_CPP
#define PLAYERS_CPP

#include <impl/includes.hpp>

entity_interface::c_entity::c_entity( )
{
	player_actors.store( std::make_shared<std::unordered_map<sdk::c_base_player*, sdk::object::c_base_player>>( ) );
	world_actors.store( std::make_shared<std::unordered_map<sdk::c_base_combat_entity*, sdk::object::c_base_combat_entity>>( ) );
	local_actor.store( std::make_shared<sdk::object::c_local_player>( ) );
}

auto entity_interface::c_entity::cache_thread( ) -> void
{
	static constexpr ch::milliseconds warmup_interval = ch::milliseconds( 15000 );
	static constexpr ch::milliseconds local_interval = ch::milliseconds( 5000 );
	static constexpr ch::milliseconds networkable_interval = ch::milliseconds( 250 );

	ch::high_resolution_clock::time_point now = ch::high_resolution_clock::now( );

	ch::high_resolution_clock::time_point networkable_tick = now - networkable_interval;
	ch::high_resolution_clock::time_point warmup_tick = now - warmup_interval;

	std::vector<ch::milliseconds> intervals =
	{
		warmup_interval, local_interval, networkable_interval
	};

	static ch::milliseconds lowest_interval = *std::min_element( intervals.begin( ), intervals.end( ) );

	while ( true ) {

		utility::update_function( warmup_interval, warmup_tick,
			[ & ] { warmup_pointers( ); }
		);

		utility::update_function( networkable_interval, networkable_tick,
			[ & ] {
				base_networkable( );
				update_local_player( );
				update_data( );
			}
		);

		utility::sleep_for( lowest_interval.count( ) );
	}
}

void entity_interface::c_entity::warmup_pointers( )
{

}

auto entity_interface::c_entity::update_local_player( ) -> void
{
	auto current_actor = local_actor.load( );
	if ( !current_actor )
		return;

	auto commit = [ & ] ( std::shared_ptr<sdk::object::c_local_player>& updated ) { local_actor.compare_exchange_weak( current_actor, updated, std::memory_order_release ); };

	auto new_actor = std::make_shared<sdk::object::c_local_player>( sdk::object::c_local_player( ) );

	/*
		const auto* entities = sdk::entities;
		if ( !entities->is_valid( ) )
			return commit( new_actor );

		new_actor->transform = game_object->get_native_component<unity::c_transform*>( sdk::base_player_components::transform );
	*/

	return commit( new_actor );
}

auto entity_interface::c_entity::base_networkable( ) -> void
{
	current_actors_set.clear( );

	const auto* entities = sdk::entities;
	if ( !entities->is_valid( ) )
		return;

	const auto* buffer = entities->buffer( );
	if ( !buffer->is_valid( ) )
		return;

	const auto count = entities->count( );
	if ( count < 0 )
		return;

	for ( int index = PLAYER_START_INDEX; index < count; index++ )
	{
		const auto* base_networkable = buffer->get( index );
		if ( !base_networkable->is_valid( ) )
			continue;

		const auto* native_component = base_networkable->native_component( ).m_value;
		if ( !native_component->is_valid( ) )
			continue;

		auto* game_object = native_component->game_object( );
		if ( !game_object->is_valid( ) )
			continue;

		switch ( game_object->tag( ) ) {
		case 6: {
			auto* base_player = base_networkable->cast<sdk::c_base_player*>( );

			current_actors_set.insert( base_player->get_current_class( ) );

			const auto actors = player_actors.load( std::memory_order_acquire );
			if ( !actors )
				continue;

			bool is_cached = actors->find( base_player ) != actors->end( );
			if ( is_cached )
				continue;

			if ( handle_player( game_object, base_player ) )
				global_actors.emplace( base_player->get_current_class( ), actor_tag::player );

			break;
		}
		default: {
			auto* base_combat_entity = base_networkable->cast<sdk::c_base_combat_entity*>( );

			current_actors_set.insert( base_combat_entity->get_current_class( ) );

			const auto actors = world_actors.load( std::memory_order_acquire );
			if ( !actors )
				continue;

			bool is_cached = actors->find( base_combat_entity ) != actors->end( );
			if ( is_cached )
				continue;

			if ( handle_entity( game_object, base_combat_entity ) )
				global_actors.emplace( base_combat_entity->get_current_class( ), actor_tag::world );

			break;
		}
		}
	}
}

void entity_interface::c_entity::update_data( )
{
	for ( auto it = global_actors.begin( ); it != global_actors.end( ); )
	{
		bool should_erase = current_actors_set.find( it->first ) == current_actors_set.end( );

		switch ( it->second )
		{
		case actor_tag::player: {
			auto* base_player = reinterpret_cast< sdk::c_base_player* >( it->first );

			auto actors = player_actors.load( std::memory_order_acquire );
			if ( !actors )
				continue;

			auto new_map = std::make_shared<std::unordered_map<sdk::c_base_player*, sdk::object::c_base_player>>( *actors );

			auto it_actor = new_map->find( base_player );
			if ( it_actor != new_map->end( ) )
			{
				if ( should_erase || !verify_player( it_actor->second ) )
					new_map->erase( it_actor );
			}

			player_actors.compare_exchange_weak( actors, new_map, std::memory_order_release );
			break;
		}
		case actor_tag::world: {
			auto* base_combat_entity = reinterpret_cast< sdk::c_base_combat_entity* >( it->first );

			auto actors = world_actors.load( std::memory_order_acquire );
			if ( !actors )
				continue;

			auto new_map = std::make_shared<std::unordered_map<sdk::c_base_combat_entity*, sdk::object::c_base_combat_entity>>( *actors );

			auto it_actor = new_map->find( base_combat_entity );
			if ( it_actor != new_map->end( ) )
			{
				if ( should_erase || !verify_entity( it_actor->second ) )
					new_map->erase( it_actor );
			}

			world_actors.compare_exchange_weak( actors, new_map, std::memory_order_release );
			break;
		}
		}

		if ( should_erase )
			it = global_actors.erase( it );
		else
			++it;
	}
}

auto entity_interface::c_entity::handle_player( unity::c_game_object* game_object, sdk::c_base_player* base_player ) -> bool
{
	sdk::object::c_base_player player = { };

	if ( !verify_player( player ) ) return false;

	auto actors = player_actors.load( std::memory_order_acquire );
	if ( !actors )
		return false;

	auto new_map = std::make_shared<std::unordered_map<sdk::c_base_player*, sdk::object::c_base_player>>( *actors );
	new_map->emplace( base_player, player );

	if ( !player_actors.compare_exchange_weak( actors, new_map, std::memory_order_release ) )
		return false;

	return true;
}

auto entity_interface::c_entity::handle_entity( unity::c_game_object* game_object, sdk::c_base_combat_entity* base_combat_entity ) -> bool
{
	sdk::object::c_base_combat_entity entity = { };

	if ( !verify_entity( entity ) ) return false;

	auto actors = world_actors.load( std::memory_order_acquire );
	if ( !actors )
		return false;

	auto new_map = std::make_shared<std::unordered_map<sdk::c_base_combat_entity*, sdk::object::c_base_combat_entity>>( *actors );
	new_map->emplace( base_combat_entity, entity );

	if ( !world_actors.compare_exchange_weak( actors, new_map, std::memory_order_release ) )
		return false;

	return true;
}

auto entity_interface::c_entity::update_thread( ) -> void
{
	static constexpr ch::milliseconds players_interval = ch::milliseconds( 1 );
	static constexpr ch::milliseconds entites_interval = ch::milliseconds( 1 );

	ch::high_resolution_clock::time_point now = ch::high_resolution_clock::now( );

	ch::high_resolution_clock::time_point players_tick = now - players_interval;
	ch::high_resolution_clock::time_point entites_tick = now - entites_interval;

	std::vector<ch::milliseconds> intervals =
	{
		players_interval, entites_interval
	};

	static ch::milliseconds lowest_interval = *std::min_element( intervals.begin( ), intervals.end( ) );

	while ( true ) {

		utility::update_function( players_interval, players_tick,
			[ & ] { update_players( ); }
		);

		utility::update_function( entites_interval, entites_tick,
			[ & ] { update_entities( ); }
		);

		utility::sleep_for( lowest_interval.count( ) );
	}
}

auto entity_interface::c_entity::verify_player( sdk::object::c_base_player& player ) const -> bool
{
	/*const auto* transform = player.transform;
	if ( !transform->is_valid( ) )
		return false;

	if ( player.lifestate == sdk::c_lifestate::dead )
		return false;

	const auto* base_player = player.base_player;

	if ( const auto current_actor = local_actor.load( std::memory_order_acquire ); current_actor )
		player.flags.is_teammate = base_player->is_teammate( current_actor->base_player );

	if ( !player.flags.is_npc && player.steam_id.length( ) == 17 && !player.profile )
		player.profile = steam_api->get_profile( player.steam_id );

	bool is_teammate = player.flags.is_teammate;
	const auto teammate_config = vars->teammates;

	if ( is_teammate && !teammate_config.enabled )
		return false;

	if ( is_teammate && player.distance > teammate_config.render_distance ) return false;

	bool is_crawling = player.flags.is_crawling;
	const auto wounded_config = vars->wounded;

	if ( is_crawling && !wounded_config.enabled && !is_teammate )
		return false;

	if ( is_crawling && player.distance > wounded_config.render_distance ) return false;

	bool is_in_safezone = player.flags.is_in_safezone;
	const auto safezone_config = vars->safezone;

	if ( is_in_safezone && !safezone_config.enabled && !is_teammate )
		return false;

	if ( is_in_safezone && player.distance > wounded_config.render_distance ) return false;

	bool is_scientist = player.flags.is_npc;
	const auto scientist_config = vars->scientists;

	if ( is_scientist && !scientist_config.enabled )
		return false;

	if ( is_scientist && player.distance > scientist_config.render_distance ) return false;

	bool is_sleeping = player.flags.is_sleeping;
	const auto sleeper_config = vars->sleepers;

	if ( is_sleeping && !sleeper_config.enabled )
		return false;

	if ( is_sleeping && player.distance > sleeper_config.render_distance ) return false;

	player.flags.is_player = !is_scientist && !is_crawling && !is_in_safezone && !is_sleeping && !is_teammate;

	bool is_player = player.flags.is_player;
	const auto player_config = vars->players;

	if ( is_player && !player_config.enabled )
		return false;

	if ( is_player && player.distance > player_config.render_distance ) return false;

	player.team_index = base_player->current_team( );
	*/

	return true;
}

auto entity_interface::c_entity::update_players( ) -> void
{
	auto actors = player_actors.load( std::memory_order_acquire );
	if ( !actors )
		return;

	auto new_map = std::make_shared<std::unordered_map<sdk::c_base_player*, sdk::object::c_base_player>>( *actors );

	for ( auto& [key, player] : *new_map ) {

		/*
			const auto* game_object = player.game_object;
			const auto* base_player = player.base_player;

			player.lifestate = base_player->lifestate( );

			player.transform = game_object->get_native_component<unity::c_transform*>( sdk::base_player_components::transform );
			if ( !player.transform->is_valid( ) )
				continue;

			player.origin_position = unity::c_transform::get_position( player.transform->get_current_class( ) );
			player.distance = camera_position.distance( player.origin_position );
		*/
	}

	player_actors.compare_exchange_weak( actors, new_map, std::memory_order_release );
}

auto entity_interface::c_entity::verify_entity( sdk::object::c_base_combat_entity& entity ) -> bool
{
	/*
		const auto* transform = entity.transform;
		if ( !transform->is_valid( ) )
			return false;

		const auto* prefab = entity.prefab;

		if ( !*prefab->enabled ) return false;
		if ( !prefab->config->enabled ) return false;

		if ( entity.distance > prefab->config->render_distance )
			return false;
	*/

	return true;
}

auto entity_interface::c_entity::update_entities( ) -> void
{
	auto actors = world_actors.load( std::memory_order_acquire );
	if ( !actors )
		return;

	auto new_map = std::make_shared<std::unordered_map<sdk::c_base_combat_entity*, sdk::object::c_base_combat_entity>>( *actors );

	for ( auto& [key, entity] : *new_map ) {

	}

	world_actors.compare_exchange_weak( actors, new_map, std::memory_order_release );
}

#endif // !PLAYERS_CPP
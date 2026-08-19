#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <chrono>
#include <mutex>

namespace entity_interface {

	enum class actor_tag : u32 {
		player,
		world,
	};

	class c_entity {
	private:
		static constexpr ch::seconds health_occlusion_time = ch::seconds( 60 );

	private:
		std::unordered_set<u64> current_actors_set;
		std::unordered_map<u64, actor_tag> global_actors;

	public:
		c_entity( );
		~c_entity( ) = default;

		std::atomic<std::shared_ptr<std::unordered_map<sdk::c_base_player*, sdk::object::c_base_player>>> player_actors;
		std::atomic<std::shared_ptr<std::unordered_map<sdk::c_base_combat_entity*, sdk::object::c_base_combat_entity>>> world_actors;

	public:
		void cache_thread( );

	public:
		std::atomic<std::shared_ptr<sdk::object::c_local_player>> local_actor;

	private:
		void update_local_player( );
		void warmup_pointers( );

		void base_networkable( );

		void update_data( );

		bool handle_player( unity::c_game_object* game_object, sdk::c_base_player* base_player );
		bool handle_entity( unity::c_game_object* game_object, sdk::c_base_combat_entity* base_combat_entity );

	public:
		void update_thread( );

	private:
		void update_entities( );
		bool verify_entity( sdk::object::c_base_combat_entity& entity );

		void update_players( );
		bool verify_player( sdk::object::c_base_player& player ) const;
	};

} inline auto entities = std::make_shared<entity_interface::c_entity>( );

#endif // PLAYERS_HPP
#pragma once

namespace vars_interface
{
	class c_vars {
	public:
		c_vars( ) = default;
		~c_vars( ) = default;

	public:
		void load( );

	public:

		struct c_aim {
			c_option silent_aim;

			int max_distance = 500;
			float fov = 360.00f;

			bool hit_chance { };
			int chance_of_hit = 100;

			int hitbox { };

		}; c_aim rifles, lmgs, smgs, shotguns, snipers, pistols, bows, blowpipes, launchers, specials, global;

		struct {
			bool categorization { };

			struct {
				bool npc { };
				bool wounded = true;
				bool sleeper { };
				bool friendly { };
				bool safezone { };
			} targets;

			c_option fov_circle;
			c_option highlight_target;

			c_option prediction;
			c_option targetline;
			c_option bullet_tracers;
		} aim;

		struct c_visuals {
			bool enabled { };
			int render_distance = 500;

			c_option boxes;
			c_option corners;

			float box_thickness = 1.00f;

			c_option skeletons;
			float skeletons_thickness = 1.00f;

			c_option username;
			c_option avatar;

			c_option distance;
			c_option held_item;

			c_option healthbars { };

			c_option team_id;
			c_option playtime;

			c_option view_direction;
			float view_direction_length = 1.00f;
			float view_direction_thickness = 1.00f;

			c_option arrows;
			float arrows_radius = 180.00f;
			float arrows_width = 1.40f;
			float arrows_height = 11.00f;

			bool hotbar { };

			bool belt = true;
			bool clothing { };

			bool visibility_check;
			c_color visible_color = c_color( 0, 255, 0 ), invisible_color = c_color( 255, 0, 0 );

		}; c_visuals players, teammates, wounded, scientists, sleepers, safezone;

		struct c_o_elements {
			bool boxes = true;
			bool skeletons = true;
			bool username { };
			bool distance { };
			bool held_item { };
			bool playtime { };
			bool team_id { };
			bool view_direction = true;

		}; c_o_elements team_elements, visibility_check_elements, target_elements;

		struct {
			c_option copy_steam_id;
			c_option colorize_teams;
		} visuals;

		struct {
			float scale = 0.70f;
			ImVec2 position;
		} hotbar;

		struct {
			c_option no_block_sprint_on_attack;

			c_option long_melee;
			float melee_radius = 1.20f;

			c_option no_recoil;
			int recoil_mode { };
			float basic_rcs { };
			ImVec2 advanced_rcs;

			c_option no_weapon_spread;
			float weapon_spread { };

			c_option force_automatic;
			c_option no_deploy_delay;
			c_option no_animation_delay;

			c_option no_sway;
			float sway_amount { };

			c_option instant_eoka;
			int eoka_mode { };

			c_option no_bolt_cycle;
			c_option instant_compound;
			c_option fast_bow;

			c_option rapid_fire;
			float firing_multiplier { };

			c_option no_view_model_animations;
			c_option no_view_model_bob;
			c_option no_view_model_punch;
			c_option no_view_model_lower;

			c_option instant_ads;

			c_option ads_zoom;
			float ads_fov = 2.00f;

			c_option bright_night;

			c_option bright_stars;
			float stars_brightness { };
			float stars_size { };

			c_option remove_sun;
			c_option remove_moon;

			c_option ambient_multiplier;
			float ambience { };

			c_option thick_bullet;
			float bullet_thickness = 0.05f;

			c_option big_bullets;
			float bullet_scale { };

			c_option hit_material;
			int bullet_material { };

			c_option no_projectile_spread;
			float projectile_spread { };

			c_option hitbox_override;

			int hitbox { };

			c_option smart_patrol_override;

			c_option fov_changer;
			int camera_fov = 90.00f;

			c_option zoom;
			int camera_zoom = 70.00f;

			c_option smooth_zoom;
			int zoom_speed = 30;

			c_option aspect_ratio_changer;
			float aspect_ratio { };

			c_option instant_revive;
			bool teammates_only { };

			c_option remove_screen_shake;
			c_option remove_wear_restrictions;

			c_option fast_loot;

			c_option powershot;
			ImVec2 indicator_position;

			float indicator_scale = 0.80f;
			float powershot_multiplier = 3.00f;

		} misc;

		struct c_world_item_config {
			bool enabled { };

			c_color color;
			bool name = true;

			bool distance = true;
			int render_distance = 500;

			bool box = true;
			bool health { };
		};

		struct c_collectables {
			bool enabled { };

			c_world_item_config hemp = { .color = c_color( 76, 175, 80 ) };
			c_world_item_config wood = { .color = c_color( 139, 69, 19 ) };
			c_world_item_config wood_pile = { .color = c_color( 101, 67, 33 ) };
			c_world_item_config stone = { .color = c_color( 128, 128, 128 ) };
			c_world_item_config metal = { .color = c_color( 192, 192, 192 ) };
			c_world_item_config sulfur = { .color = c_color( 255, 255, 0 ) };
			c_world_item_config mushroom = { .color = c_color( 165, 42, 42 ) };
			c_world_item_config berries = { .color = c_color( 138, 43, 226 ) };
			c_world_item_config potato = { .color = c_color( 210, 180, 140 ) };
			c_world_item_config diesel = { .color = c_color( 255, 140, 0 ) };
			c_world_item_config corn = { .color = c_color( 255, 215, 0 ) };
			c_world_item_config pumpkin = { .color = c_color( 255, 117, 24 ) };
		};

		struct c_crates {
			bool enabled { };

			c_world_item_config elite_crate = { .color = c_color( 255, 0, 0 ) };
			c_world_item_config heli_crate = { .color = c_color( 255, 20, 147 ) };
			c_world_item_config bradley_crate = { .color = c_color( 255, 69, 0 ) };
			c_world_item_config hack_crate = { .color = c_color( 0, 255, 255 ) };
			c_world_item_config military_crate = { .color = c_color( 34, 139, 34 ) };
			c_world_item_config normal_crate = { .color = c_color( 139, 69, 19 ) };
			c_world_item_config tool_crate = { .color = c_color( 105, 105, 105 ) };
			c_world_item_config underwater_crate = { .color = c_color( 0, 191, 255 ) };
			c_world_item_config advanced_underwater_crate = { .color = c_color( 30, 144, 255 ) };
			c_world_item_config food_crate = { .color = c_color( 255, 228, 181 ) };
			c_world_item_config medical = { .color = c_color( 220, 20, 60 ) };
			c_world_item_config tech_parts_crate = { .color = c_color( 0, 206, 209 ) };
			c_world_item_config vehicle_parts_crate = { .color = c_color( 70, 130, 180 ) };
			c_world_item_config fuel_crate = { .color = c_color( 255, 165, 0 ) };
			c_world_item_config ammunition_crate = { .color = c_color( 184, 134, 11 ) };
		};

		struct c_vehicles {
			bool enabled { };

			c_world_item_config boats = { .color = c_color( 0, 105, 148 ) };
			c_world_item_config rhibs = { .color = c_color( 25, 25, 112 ) };
			c_world_item_config tugboat = { .color = c_color( 47, 79, 79 ) };
			c_world_item_config cargoship = { .color = c_color( 85, 107, 47 ) };
			c_world_item_config kayak = { .color = c_color( 0, 139, 139 ) };
			c_world_item_config minicopters = { .color = c_color( 255, 99, 71 ) };
			c_world_item_config scrapheli = { .color = c_color( 188, 143, 143 ) };
			c_world_item_config hotairbaloon = { .color = c_color( 255, 20, 147 ) };
			c_world_item_config patrol_helipcoter = { .color = c_color( 178, 34, 34 ) };
			c_world_item_config modular_car = { .color = c_color( 65, 105, 225 ) };
			c_world_item_config submarine = { .color = c_color( 72, 61, 139 ) };
			c_world_item_config bradley = { .color = c_color( 107, 142, 35 ) };
			c_world_item_config trains = { .color = c_color( 205, 92, 92 ) };
		};

		struct c_ores {
			bool enabled { };

			c_world_item_config stone_ore = { .color = c_color( 169, 169, 169 ) };
			c_world_item_config metal_ore = { .color = c_color( 192, 192, 192 ) };
			c_world_item_config sulfur_ore = { .color = c_color( 255, 255, 0 ) };
		};

		struct c_animals {
			bool enabled { };

			c_world_item_config bear = { .color = c_color( 139, 69, 19 ) };
			c_world_item_config polar_bear = { .color = c_color( 240, 248, 255 ) };
			c_world_item_config boar = { .color = c_color( 105, 105, 105 ) };
			c_world_item_config deers = { .color = c_color( 160, 82, 45 ) };
			c_world_item_config wolf = { .color = c_color( 112, 128, 144 ) };
			c_world_item_config chicken = { .color = c_color( 255, 250, 250 ) };
			c_world_item_config horse = { .color = c_color( 139, 90, 43 ) };
			c_world_item_config crocodiles = { .color = c_color( 85, 107, 47 ) };
			c_world_item_config tigers = { .color = c_color( 255, 140, 0 ) };
			c_world_item_config panthers = { .color = c_color( 0, 0, 0 ) };
			c_world_item_config snakes = { .color = c_color( 154, 205, 50 ) };
		};

		struct c_deployables {
			bool enabled { };

			c_world_item_config shotguntraps = { .color = c_color( 178, 34, 34 ) };
			c_world_item_config flameturrets = { .color = c_color( 255, 69, 0 ) };
			c_world_item_config autoturret = { .color = c_color( 220, 20, 60 ) };
			c_world_item_config bear_trap = { .color = c_color( 139, 69, 19 ) };
			c_world_item_config samsiteturrets = { .color = c_color( 0, 100, 0 ) };
			c_world_item_config landmines = { .color = c_color( 255, 215, 0 ) };
			c_world_item_config cupboard = { .color = c_color( 210, 105, 30 ) };
			c_world_item_config furnances = { .color = c_color( 255, 99, 71 ) };
			c_world_item_config boxes = { .color = c_color( 160, 82, 45 ) };
			c_world_item_config vendings = { .color = c_color( 0, 191, 255 ) };
			c_world_item_config cctv_cameras = { .color = c_color( 70, 130, 180 ) };
			c_world_item_config seismic_sensor = { .color = c_color( 218, 165, 32 ) };
			c_world_item_config sleeping_bags = { .color = c_color( 100, 149, 237 ) };
			c_world_item_config workbench_1 = { .color = c_color( 105, 105, 105 ) };
			c_world_item_config workbench_2 = { .color = c_color( 128, 128, 128 ) };
			c_world_item_config workbench_3 = { .color = c_color( 169, 169, 169 ) };
		};

		struct c_world {
			bool enabled { };

			c_world_item_config recyclers = { .color = c_color( 34, 139, 34 ) };
			c_world_item_config supplydrop = { .color = c_color( 255, 0, 0 ) };
			c_world_item_config corpses = { .color = c_color( 128, 0, 0 ) };

			struct {
				bool weapon { };
				bool construction { };
				bool items { };
				bool resources { };
				bool attire { };
				bool tool { };
				bool medical { };
				bool food { };
				bool ammunition { };
				bool traps { };
				bool misc { };
				bool all { };
				bool common { };
				bool component { };
				bool search { };
				bool favourite { };
				bool electrical { };
				bool fun { };
			} categories;

			c_world_item_config dropped = { .color = c_color( 255, 215, 0 ) };
		};

		struct world_items_t {
			c_collectables collectables;
			c_crates crates;
			c_vehicles vehicles;
			c_ores ores;
			c_animals animals;
			c_deployables deployables;
			c_world world;

		} world_items;

		struct {
			c_option menu;
			float font_size = 15.00f;

			c_option framerate;
		} ui;
	};

} inline auto vars = std::make_shared<vars_interface::c_vars>( );
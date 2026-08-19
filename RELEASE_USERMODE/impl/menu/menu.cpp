#ifndef MENU_CPP
#define MENU_CPP

#include <impl/includes.hpp>

auto menu_interface::c_interface::initialize( ) -> void
{
	size = ImVec2 { 660, 675 };

	GImGui->IO.IniFilename = "";

	StyleManager::get( ).Styles( );
	StyleManager::get( ).Colors( );

	LangManager::get( ).initialize( );

	auto config = ImFontConfig( );

	config.FontLoaderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LoadColor;
	config.OversampleH = 1;
	config.OversampleV = 1;

	fonts->add( HASH_STR( "Karla-SemiBold.ttf" ), fonts_binary::karla_semibold, sizeof( fonts_binary::karla_semibold ), { vars->ui.font_size, 25.00f }, &config, ImGui::GetIO( ).Fonts->GetGlyphRangesCyrillic( ) );
	fonts->add( HASH_STR( "Geist-SemiBold.ttf" ), fonts_binary::geist_semi_bold, sizeof( fonts_binary::geist_semi_bold ), { 14.00f, 12.00f }, &config, ImGui::GetIO( ).Fonts->GetGlyphRangesCyrillic( ) );

	ImWchar icons_ranges[ ] = { 0x1 + 1000, 0x1 + 5881, 0 };
	fonts->add( HASH_STR( "Glyphter.tff" ), fonts_binary::glyphter, sizeof( fonts_binary::glyphter ), { 14.00f, 12.00f }, &config, icons_ranges );

	ChildManager& cm = ChildManager::get( );
	auto& widgets = WidgetsManager::get( );

	static int aim_category = 0;
	vars_interface::c_vars::c_aim* aim = nullptr;

	TabsManager::get( ).add_page( 0, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Local" ) );
			{
				TextDisabled( LangManager::get( ).translate( HASH_STR( "Category Config" ) ).c_str( ) );
				TooltipManager::get( ).draw( HASH_STR( "This applies to selected category" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Categorize Aim" ), &vars->aim.categorization );
				TooltipManager::get( ).draw( HASH_STR( "Enable categorization per weapon group" ) );

				if ( !vars->aim.categorization ) aim_category = 10;
				widgets.Combo( HASH_STR( "Selected" ), &aim_category, aim_categories );

				switch ( aim_category )
				{
				case 0: aim = &vars->rifles; break;
				case 1: aim = &vars->lmgs; break;
				case 2: aim = &vars->smgs; break;
				case 3: aim = &vars->shotguns; break;
				case 4: aim = &vars->snipers; break;
				case 5: aim = &vars->pistols; break;
				case 6: aim = &vars->bows; break;
				case 7: aim = &vars->blowpipes; break;
				case 8: aim = &vars->launchers; break;
				case 9: aim = &vars->specials; break;
				case 10: aim = &vars->global; break;
				}

				widgets.Checkbox( HASH_STR( "Silent Aim" ), &aim->silent_aim.state, &aim->silent_aim.keybind.key );

				widgets.SliderInt( HASH_STR( "Max Distance" ), &aim->max_distance, 0, 500 );
				widgets.SliderFloat( HASH_STR( "Field Of View" ), &aim->fov, 1.0f, 360.0f );

				widgets.Checkbox( HASH_STR( "Hitchance" ), &aim->hit_chance, nullptr, nullptr, [ & ] ( ) {
					widgets.SliderInt( HASH_STR( "Chance" ), &aim->chance_of_hit, 0, 100 );
					} );

				widgets.Combo( HASH_STR( "Hitbox" ), &aim->hitbox, aim_hitboxes );
			}
			cm.endchild( );
		}
		EndGroup( );

		SameLine( );

		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Global" ) );
			{
				TextDisabled( LangManager::get( ).translate( HASH_STR( "Global Config" ) ).c_str( ) );
				TooltipManager::get( ).draw( HASH_STR( "This applies to the whole visuals not per category" ) );

				widgets.Separator( );

				TextDisabled( LangManager::get( ).translate( HASH_STR( "Aim" ) ).c_str( ) );

				target_categories [ 0 ].selected = vars->aim.targets.npc;
				target_categories [ 1 ].selected = vars->aim.targets.wounded;
				target_categories [ 2 ].selected = vars->aim.targets.sleeper;
				target_categories [ 3 ].selected = vars->aim.targets.friendly;
				target_categories [ 4 ].selected = vars->aim.targets.safezone;

				widgets.MultiCombo( HASH_STR( "Target categories" ), &target_categories );

				vars->aim.targets.npc = target_categories [ 0 ].selected;
				vars->aim.targets.wounded = target_categories [ 1 ].selected;
				vars->aim.targets.sleeper = target_categories [ 2 ].selected;
				vars->aim.targets.friendly = target_categories [ 3 ].selected;
				vars->aim.targets.safezone = target_categories [ 4 ].selected;

				TextDisabled( LangManager::get( ).translate( HASH_STR( "Indicators" ) ).c_str( ) );

				widgets.Checkbox( HASH_STR( "Field Of View Circle" ), &vars->aim.fov_circle.state, nullptr, vars->aim.fov_circle.color.to_array( ) );
				widgets.Checkbox( HASH_STR( "Targetline" ), &vars->aim.targetline.state, nullptr, vars->aim.targetline.color.to_array( ) );
				widgets.Checkbox( HASH_STR( "Show Prediction" ), &vars->aim.prediction.state, nullptr, vars->aim.prediction.color.to_array( ) );
				widgets.Checkbox( HASH_STR( "Bullet Tracers" ), &vars->aim.bullet_tracers.state, nullptr, vars->aim.bullet_tracers.color.to_array( ) );

				widgets.Checkbox( HASH_STR( "Highlight Target" ), &vars->aim.highlight_target.state, nullptr, vars->aim.highlight_target.color.to_array( ), [ & ] ( ) {
					auto& e = vars->target_elements;

					elements [ 0 ].selected = e.boxes;
					elements [ 1 ].selected = e.skeletons;
					elements [ 2 ].selected = e.username;
					elements [ 3 ].selected = e.distance;
					elements [ 4 ].selected = e.held_item;
					elements [ 5 ].selected = e.playtime;
					elements [ 6 ].selected = e.team_id;
					elements [ 7 ].selected = e.view_direction;

					widgets.MultiCombo( HASH_STR( "Elements" ), &elements );

					e.boxes = elements [ 0 ].selected;
					e.skeletons = elements [ 1 ].selected;
					e.username = elements [ 2 ].selected;
					e.distance = elements [ 3 ].selected;
					e.held_item = elements [ 4 ].selected;
					e.playtime = elements [ 5 ].selected;
					e.team_id = elements [ 6 ].selected;
					e.view_direction = elements [ 7 ].selected;
				} );
			}
			cm.endchild( );
		}
		EndGroup( );
	} );

	TabsManager::get( ).add_page( 0, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Weapon" ) );
			{
				widgets.Checkbox( HASH_STR( "Recoil Modifier" ), &vars->misc.no_recoil.state, nullptr, nullptr, [ & ] ( ) {

					widgets.Combo( HASH_STR( "Mode" ), &vars->misc.recoil_mode, recoil_modes );
					TooltipManager::get( ).draw( HASH_STR( "Select a recoil mode prefered by style" ) );
				} );
				TooltipManager::get( ).draw( HASH_STR( "Reduces weapon recoil" ) );

				widgets.Checkbox( HASH_STR( "Weapon Spread" ), &vars->misc.no_weapon_spread.state, nullptr, nullptr, [ & ] ( ) {

					widgets.SliderFloat( HASH_STR( "Amount" ), &vars->misc.weapon_spread, 0.0f, 100.0f );
					TooltipManager::get( ).draw( HASH_STR( "Adjust weapon spread reduction" ) );
				} );
				TooltipManager::get( ).draw( HASH_STR( "Reduces weapon spread" ) );

				widgets.Checkbox( HASH_STR( "Projectile Spread" ), &vars->misc.no_projectile_spread.state, nullptr, nullptr, [ & ] ( ) {

					widgets.SliderFloat( HASH_STR( "Amount" ), &vars->misc.projectile_spread, 0.0f, 100.0f );
					TooltipManager::get( ).draw( HASH_STR( "Adjust projectile spread reduction" ) );
				} );
				TooltipManager::get( ).draw( HASH_STR( "Reduces projectile spread" ) );

				widgets.Checkbox( HASH_STR( "Weapon Sway" ), &vars->misc.no_sway.state, nullptr, nullptr, [ & ] ( ) {

					widgets.SliderFloat( HASH_STR( "Amount" ), &vars->misc.sway_amount, 0.0f, 100.0f );
					TooltipManager::get( ).draw( HASH_STR( "Adjust weapon sway reduction" ) );
				} );
				TooltipManager::get( ).draw( HASH_STR( "Reduces weapon sway" ) );

				widgets.Checkbox( HASH_STR( "Rapid Fire" ), &vars->misc.rapid_fire.state, nullptr, nullptr, [ & ] ( ) {

					widgets.SliderFloat( HASH_STR( "Multiplier" ), &vars->misc.firing_multiplier, 1.0f, 10.0f );
					TooltipManager::get( ).draw( HASH_STR( "Adjust fire rate multiplier" ) );
				} );
				TooltipManager::get( ).draw( HASH_STR( "Increases weapon fire rate" ) );

			}
			cm.endchild( );

			cm.beginchild( HASH_STR( "Bullet Settings" ) );
			{
				widgets.Checkbox( HASH_STR( "Thick Bullet" ), &vars->misc.thick_bullet.state, nullptr, nullptr, [ & ] ( ) {

					widgets.SliderFloat( HASH_STR( "Thickness" ), &vars->misc.bullet_thickness, 0.05f, 1.5f );
					TooltipManager::get( ).draw( HASH_STR( "Adjust bullet hitbox size" ) );
				} );
				TooltipManager::get( ).draw( HASH_STR( "Increases bullet hitbox size" ) );

				widgets.Checkbox( HASH_STR( "Big Bullets" ), &vars->misc.big_bullets.state, nullptr, nullptr, [ & ] ( ) {

					widgets.SliderFloat( HASH_STR( "Scale" ), &vars->misc.bullet_scale, 0.1f, 100.0f );
					TooltipManager::get( ).draw( HASH_STR( "Adjust bullet visual size" ) );
				} );
				TooltipManager::get( ).draw( HASH_STR( "Increases bullet visual size, only applies to static projectiles" ) );

				widgets.Checkbox( HASH_STR( "Hit Material" ), &vars->misc.hit_material.state, nullptr, nullptr, [ & ] ( ) {
		
				} );
				TooltipManager::get( ).draw( HASH_STR( "Changes hit material effects" ) );

				widgets.Checkbox( HASH_STR( "Hitbox Override" ), &vars->misc.hitbox_override.state, nullptr, nullptr, [ & ] ( ) {

					widgets.Combo( HASH_STR( "Hitbox" ), &vars->misc.hitbox, override_hitboxes );
					} );

				widgets.Checkbox( HASH_STR( "Smart Patrol Override" ), &vars->misc.smart_patrol_override.state );
			}
			cm.endchild( );
		}
		EndGroup( );

		SameLine( );

		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Animation" ) );
			{
				widgets.Checkbox( HASH_STR( "No Block Sprint On Attack" ), &vars->misc.no_block_sprint_on_attack.state );
				widgets.Checkbox( HASH_STR( "Force Automatic" ), &vars->misc.force_automatic.state );
				widgets.Checkbox( HASH_STR( "No Deploy Delay" ), &vars->misc.no_deploy_delay.state );
				widgets.Checkbox( HASH_STR( "No Animation Delay" ), &vars->misc.no_animation_delay.state );
				widgets.Checkbox( HASH_STR( "No Bolt Cycle" ), &vars->misc.no_bolt_cycle.state );

				widgets.Checkbox( HASH_STR( "Long Melee" ), &vars->misc.long_melee.state, nullptr, nullptr, [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Radius" ), &vars->misc.melee_radius, 0.0f, 3.0f );
				} );

				widgets.Checkbox( HASH_STR( "Instant Compound" ), &vars->misc.instant_compound.state );
				widgets.Checkbox( HASH_STR( "Fast Bow" ), &vars->misc.fast_bow.state );

				widgets.Checkbox( HASH_STR( "Instant Eoka" ), &vars->misc.instant_eoka.state, nullptr, nullptr, [ & ] ( ) {
					widgets.Combo( HASH_STR( "Mode" ), &vars->misc.eoka_mode, eoka_modes );
				} );
			}
			cm.endchild( );
		}
		EndGroup( );
	} );

	static int visual_category = 0;
	vars_interface::c_vars::c_visuals* visuals = nullptr;

	TabsManager::get( ).add_page( 1, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Visuals" ) );
			{
				TextDisabled( LangManager::get( ).translate( HASH_STR( "Category Config" ) ).c_str( ) );
				TooltipManager::get( ).draw( HASH_STR( "This applies to selected category" ) );

				widgets.Separator( );

				widgets.Combo( HASH_STR( "Selected" ), &visual_category, visuals_cateogries );

				switch ( visual_category ) 
				{
					case 0: visuals = &vars->players; break;
					case 1: visuals = &vars->teammates; break;
					case 2: visuals = &vars->wounded; break;
					case 3: visuals = &vars->scientists; break;
					case 4: visuals = &vars->sleepers; break;
					case 5: visuals = &vars->safezone; break;
					default: visuals = &vars->players; break;
				}

				widgets.Checkbox( HASH_STR( "Enabled" ), &visuals->enabled );
				TooltipManager::get( ).draw( HASH_STR( "Toggle the category" ) );

				widgets.SliderInt( HASH_STR( "Render Distance" ), &visuals->render_distance, 50, 500 );
				TooltipManager::get( ).draw( HASH_STR( "Maximum render distance of entities for category" ) );

				widgets.Separator( );

				TextDisabled( LangManager::get( ).translate( HASH_STR( "Global Config" ) ).c_str( ) );
				TooltipManager::get( ).draw( HASH_STR( "This applies to the whole visuals not per category" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Copy Steam ID" ), &vars->visuals.copy_steam_id.state, &vars->visuals.copy_steam_id.keybind.key );
				TooltipManager::get( ).draw( HASH_STR( "Coppies closest player Steam ID to clipboard" ) );

				widgets.Checkbox( HASH_STR( "Colorize Teams" ), &vars->visuals.colorize_teams.state, nullptr, nullptr, [ & ] ( ) {
					auto& e = vars->team_elements;

					elements [ 0 ].selected = e.boxes;
					elements [ 1 ].selected = e.skeletons;
					elements [ 2 ].selected = e.username;
					elements [ 3 ].selected = e.distance;
					elements [ 4 ].selected = e.held_item;
					elements [ 5 ].selected = e.playtime;
					elements [ 6 ].selected = e.team_id;
					elements [ 7 ].selected = e.view_direction;

					widgets.MultiCombo( HASH_STR( "Elements" ), &elements );

					e.boxes = elements [ 0 ].selected;
					e.skeletons = elements [ 1 ].selected;
					e.username = elements [ 2 ].selected;
					e.distance = elements [ 3 ].selected;
					e.held_item = elements [ 4 ].selected;
					e.playtime = elements [ 5 ].selected;
					e.team_id = elements [ 6 ].selected;
					e.view_direction = elements [ 7 ].selected;

					widgets.Separator( );

					TextDisabled( LangManager::get( ).translate( HASH_STR( "Teams Colors" ) ).c_str( ) );
					TooltipManager::get( ).draw( HASH_STR( "You may edit the colors of the existing teams" ) );

					widgets.Separator( );
				} );
			}
			cm.endchild( );
		}
		EndGroup( );

		SameLine( );

		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Visual Options" ) );
			{
				bool box_changed = widgets.Checkbox( HASH_STR( "Box" ), &visuals->boxes.state, nullptr, visuals->boxes.color.to_array( ), [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Thickness" ), &visuals->box_thickness, 1.0f, 2.50f );
					} );

				bool corner_changed = widgets.Checkbox( HASH_STR( "Corner" ), &visuals->corners.state, nullptr, visuals->corners.color.to_array( ), [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Thickness" ), &visuals->box_thickness, 1.0f, 2.50f );
					} );

				if ( box_changed && visuals->boxes.state ) visuals->corners.state = false;
				if ( corner_changed && visuals->corners.state ) visuals->boxes.state = false;

				widgets.Checkbox( HASH_STR( "Skeletons" ), &visuals->skeletons.state, nullptr, visuals->skeletons.color.to_array( ), [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Thickness" ), &visuals->skeletons_thickness, 1.00f, 2.50f );
				} );

				widgets.Checkbox( HASH_STR( "View Direction" ), &visuals->view_direction.state, nullptr, visuals->view_direction.color.to_array( ), [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Length" ), &visuals->view_direction_length, 0.1f, 2.50f );
					widgets.SliderFloat( HASH_STR( "Thickness" ), &visuals->view_direction_thickness, 1.00f, 2.50f );
					} );

				widgets.Checkbox( HASH_STR( "Arrows" ), &visuals->arrows.state, nullptr, visuals->arrows.color.to_array( ), [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Radius" ), &visuals->arrows_radius, 1.00f, 360.00f );
					widgets.SliderFloat( HASH_STR( "Width" ), &visuals->arrows_width, 0.1f, 3.f );
					widgets.SliderFloat( HASH_STR( "Height" ), &visuals->arrows_height, 0.1f, 15.f );
				} );

				widgets.Checkbox( HASH_STR( "Username" ), &visuals->username.state, nullptr, visuals->username.color.to_array( ) );

				widgets.Checkbox( HASH_STR( "Avatar" ), &visuals->avatar.state );
				TooltipManager::get( ).draw( HASH_STR( "Displays an image of persons Steam avatar" ) );

				widgets.Checkbox( HASH_STR( "Playtime" ), &visuals->playtime.state, nullptr, visuals->playtime.color.to_array( ) );
				TooltipManager::get( ).draw( HASH_STR( "Displays total playtime in hours if public" ) );

				widgets.Checkbox( HASH_STR( "Healthabrs" ), &visuals->healthbars.state );

				widgets.Checkbox( HASH_STR( "Distance" ), &visuals->distance.state, nullptr, visuals->distance.color.to_array( ) );

				widgets.Checkbox( HASH_STR( "Held Item" ), &visuals->held_item.state, nullptr, visuals->held_item.color.to_array( ) );
				widgets.Checkbox( HASH_STR( "Team ID" ), &visuals->team_id.state, nullptr, visuals->team_id.color.to_array( ) );

				widgets.Checkbox( HASH_STR( "Hotbar" ), &visuals->hotbar, nullptr, nullptr, [ & ] ( ) {

					hotbar_categories [ 0 ].selected = visuals->belt;
					hotbar_categories [ 1 ].selected = visuals->clothing;

					widgets.MultiCombo( HASH_STR( "Elements" ), &hotbar_categories );

					visuals->belt = hotbar_categories [ 0 ].selected;
					visuals->clothing = hotbar_categories [ 1 ].selected;

					widgets.SliderFloat( HASH_STR( "Scale" ), &vars->hotbar.scale, 0.10f, 1.00f );

					if ( widgets.Button( HASH_STR("Reset position" ) ) )
						vars->hotbar.position = ImVec2( render->game_width / 2.00, 200 );
					} );

				widgets.Checkbox( HASH_STR( "Visibility check" ), &visuals->visibility_check, nullptr, nullptr, [ & ] ( ) {
					auto& e = vars->visibility_check_elements;

					elements [ 0 ].selected = e.boxes;
					elements [ 1 ].selected = e.skeletons;
					elements [ 2 ].selected = e.username;
					elements [ 3 ].selected = e.distance;
					elements [ 4 ].selected = e.held_item;
					elements [ 5 ].selected = e.playtime;
					elements [ 6 ].selected = e.team_id;
					elements [ 7 ].selected = e.view_direction;

					widgets.MultiCombo( HASH_STR( "Elements" ), &elements );

					e.boxes = elements [ 0 ].selected;
					e.skeletons = elements [ 1 ].selected;
					e.username = elements [ 2 ].selected;
					e.distance = elements [ 3 ].selected;
					e.held_item = elements [ 4 ].selected;
					e.playtime = elements [ 5 ].selected;
					e.team_id = elements [ 6 ].selected;
					e.view_direction = elements [ 7 ].selected;

					widgets.Separator( );

					TextDisabled( LangManager::get( ).translate( HASH_STR( "Visible Colors" ) ).c_str( ) );
					TooltipManager::get( ).draw( HASH_STR( "You may edit the colors of visible/invisible players" ) );

					widgets.Separator( );

					widgets.ColorEdit( HASH_STR("Visible Color" ), visuals->visible_color.to_array( ) );
					widgets.ColorEdit( HASH_STR("Invisible Color" ), visuals->invisible_color.to_array( ) );
				} );
			}
			cm.endchild( );
		}
		EndGroup( );
	} );

	TabsManager::get( ).add_page( 3, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "General" ) );
			{
				widgets.Checkbox( HASH_STR( "FOV Changer" ), &vars->misc.fov_changer.state, nullptr, nullptr, [ & ] ( ) {
					widgets.SliderInt( HASH_STR( "FOV" ), &vars->misc.camera_fov, 70, 160 );
					} );

				widgets.Checkbox( HASH_STR( "Zoom" ), &vars->misc.zoom.state, &vars->misc.zoom.keybind.key, nullptr, [ & ] ( ) {
					widgets.SliderInt( HASH_STR( "FOV" ), &vars->misc.camera_zoom, 10, 70 );

					widgets.Checkbox( HASH_STR( "Smooth Zoom" ), &vars->misc.smooth_zoom.state, nullptr, nullptr, [ & ] ( ) {
						widgets.SliderInt( HASH_STR( "Speed" ), &vars->misc.zoom_speed, 0, 100 );
						} );

					} );

				widgets.Checkbox( HASH_STR( "Aspect Ratio Changer" ), &vars->misc.aspect_ratio_changer.state, nullptr, nullptr, [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Ratio" ), &vars->misc.aspect_ratio, 0.3f, 2.00f );
					} );

				widgets.Checkbox( HASH_STR( "Instant Revive" ), &vars->misc.instant_revive.state, nullptr, nullptr, [ & ] ( ) {
					widgets.Checkbox( HASH_STR( "Teammates Only" ), &vars->misc.teammates_only );
					} );

				widgets.Checkbox( HASH_STR( "Bright Night" ), &vars->misc.bright_night.state );
				widgets.Checkbox( HASH_STR( "Ambient Multiplier" ), &vars->misc.ambient_multiplier.state, nullptr, nullptr, [ & ] ( ) {
					widgets.SliderFloat( HASH_STR( "Amount" ), &vars->misc.ambience, 0.0f, 2.0f );
					} );

				widgets.Checkbox( HASH_STR( "Remove Screen Shake" ), &vars->misc.remove_screen_shake.state );
				widgets.Checkbox( HASH_STR( "Remove Wear Restrictions" ), &vars->misc.remove_wear_restrictions.state );
				widgets.Checkbox( HASH_STR( "Fast Loot" ), &vars->misc.fast_loot.state );
			}
			cm.endchild( );
		}
		EndGroup( );
	} );

	auto render_item_options = [ & ] ( vars_interface::c_vars::c_world_item_config& config, bool health = false ) {

		TextDisabled( LangManager::get( ).translate( HASH_STR( "Item Config" ) ).c_str( ) );
		TooltipManager::get( ).draw( HASH_STR( "This applies to this item only" ) );

		widgets.Separator( );

		widgets.SliderInt( HASH_STR( "Render Distance" ), &config.render_distance, 50, 5000 );

		widgets.Checkbox( HASH_STR( "Display Name" ), &config.name );
		widgets.Checkbox( HASH_STR( "Display Distance" ), &config.distance );
		widgets.Checkbox( HASH_STR( "3D Box" ), &config.box );

		if ( health )
			widgets.Checkbox( HASH_STR( "Display Health" ), &config.health );

		widgets.Separator( );
	};

	TabsManager::get( ).add_page( 2, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Collectables" ) );
			{
				widgets.Checkbox( HASH_STR( "Show Collectables" ), &vars->world_items.collectables.enabled );
				TooltipManager::get( ).draw( HASH_STR( "This enables the collectables category to work" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Hemp" ), &vars->world_items.collectables.hemp.enabled, 0, vars->world_items.collectables.hemp.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.hemp );
					} );

				widgets.Checkbox( HASH_STR( "Wood" ), &vars->world_items.collectables.wood.enabled, 0, vars->world_items.collectables.wood.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.wood );
					} );

				widgets.Checkbox( HASH_STR( "Wood Pile" ), &vars->world_items.collectables.wood_pile.enabled, 0, vars->world_items.collectables.wood_pile.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.wood_pile );
					} );

				widgets.Checkbox( HASH_STR( "Metal" ), &vars->world_items.collectables.metal.enabled, 0, vars->world_items.collectables.metal.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.metal );
					} );

				widgets.Checkbox( HASH_STR( "Sulfur" ), &vars->world_items.collectables.sulfur.enabled, 0, vars->world_items.collectables.sulfur.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.sulfur );
					} );

				widgets.Checkbox( HASH_STR( "Stone" ), &vars->world_items.collectables.stone.enabled, 0, vars->world_items.collectables.stone.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.stone );
					} );

				widgets.Checkbox( HASH_STR( "Mushrooms" ), &vars->world_items.collectables.mushroom.enabled, 0, vars->world_items.collectables.mushroom.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.mushroom );
					} );

				widgets.Checkbox( HASH_STR( "Berries" ), &vars->world_items.collectables.berries.enabled, 0, vars->world_items.collectables.berries.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.berries );
					} );

				widgets.Checkbox( HASH_STR( "Potato" ), &vars->world_items.collectables.potato.enabled, 0, vars->world_items.collectables.potato.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.potato );
					} );

				widgets.Checkbox( HASH_STR( "Diesel" ), &vars->world_items.collectables.diesel.enabled, 0, vars->world_items.collectables.diesel.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.diesel );
					} );

				widgets.Checkbox( HASH_STR( "Corn" ), &vars->world_items.collectables.corn.enabled, 0, vars->world_items.collectables.corn.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.corn );
					} );

				widgets.Checkbox( HASH_STR( "Pumpkin" ), &vars->world_items.collectables.pumpkin.enabled, 0, vars->world_items.collectables.pumpkin.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.collectables.pumpkin );
					} );
			}
			cm.endchild( );
		}
		EndGroup( );
	} );

	TabsManager::get( ).add_page( 2, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Crates" ) );
			{
				widgets.Checkbox( HASH_STR( "Show Crates" ), &vars->world_items.crates.enabled );
				TooltipManager::get( ).draw( HASH_STR( "This enables the crates category to work" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Elite Crate" ), &vars->world_items.crates.elite_crate.enabled, 0, vars->world_items.crates.elite_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.elite_crate );
					} );

				widgets.Checkbox( HASH_STR( "Heli Crate" ), &vars->world_items.crates.heli_crate.enabled, 0, vars->world_items.crates.heli_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.heli_crate );
					} );

				widgets.Checkbox( HASH_STR( "Bradley Crate" ), &vars->world_items.crates.bradley_crate.enabled, 0, vars->world_items.crates.bradley_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.bradley_crate );
					} );

				widgets.Checkbox( HASH_STR( "Locked Crate" ), &vars->world_items.crates.hack_crate.enabled, 0, vars->world_items.crates.hack_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.hack_crate );
					} );

				widgets.Checkbox( HASH_STR( "Military Crate" ), &vars->world_items.crates.military_crate.enabled, 0, vars->world_items.crates.military_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.military_crate );
					} );

				widgets.Checkbox( HASH_STR( "Wooden Crate" ), &vars->world_items.crates.normal_crate.enabled, 0, vars->world_items.crates.normal_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.normal_crate );
					} );

				widgets.Checkbox( HASH_STR( "Tool Crate" ), &vars->world_items.crates.tool_crate.enabled, 0, vars->world_items.crates.tool_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.tool_crate );
					} );

				widgets.Checkbox( HASH_STR( "Underwater Basic" ), &vars->world_items.crates.underwater_crate.enabled, 0, vars->world_items.crates.underwater_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.underwater_crate );
					} );

				widgets.Checkbox( HASH_STR( "Underwater Advanced" ), &vars->world_items.crates.advanced_underwater_crate.enabled, 0, vars->world_items.crates.advanced_underwater_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.advanced_underwater_crate );
					} );

				widgets.Checkbox( HASH_STR( "Food Crate" ), &vars->world_items.crates.food_crate.enabled, 0, vars->world_items.crates.food_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.food_crate );
					} );

				widgets.Checkbox( HASH_STR( "Medical Crate" ), &vars->world_items.crates.medical.enabled, 0, vars->world_items.crates.medical.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.medical );
					} );

				widgets.Checkbox( HASH_STR( "Tech Crate" ), &vars->world_items.crates.tech_parts_crate.enabled, 0, vars->world_items.crates.tech_parts_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.tech_parts_crate );
					} );

				widgets.Checkbox( HASH_STR( "Vehicle Parts Crate" ), &vars->world_items.crates.vehicle_parts_crate.enabled, 0, vars->world_items.crates.vehicle_parts_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.vehicle_parts_crate );
					} );

				widgets.Checkbox( HASH_STR( "Fuel Crate" ), &vars->world_items.crates.fuel_crate.enabled, 0, vars->world_items.crates.fuel_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.fuel_crate );
					} );

				widgets.Checkbox( HASH_STR( "Ammunition Crate" ), &vars->world_items.crates.ammunition_crate.enabled, 0, vars->world_items.crates.ammunition_crate.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.crates.ammunition_crate );
					} );
			}
			cm.endchild( );
		}
		EndGroup( );
		} );

	TabsManager::get( ).add_page( 2, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Vehicles" ) );
			{
				widgets.Checkbox( HASH_STR( "Show Vehicles" ), &vars->world_items.vehicles.enabled );
				TooltipManager::get( ).draw( HASH_STR( "This enables the vehicles category to work" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Rowboat" ), &vars->world_items.vehicles.boats.enabled, 0, vars->world_items.vehicles.boats.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.boats, true );
					} );

				widgets.Checkbox( HASH_STR( "Rhib" ), &vars->world_items.vehicles.rhibs.enabled, 0, vars->world_items.vehicles.rhibs.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.rhibs, true );
					} );

				widgets.Checkbox( HASH_STR( "Tugboat" ), &vars->world_items.vehicles.tugboat.enabled, 0, vars->world_items.vehicles.tugboat.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.tugboat, true );
					} );

				widgets.Checkbox( HASH_STR( "Cargo" ), &vars->world_items.vehicles.cargoship.enabled, 0, vars->world_items.vehicles.cargoship.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.cargoship, true );
					} );

				widgets.Checkbox( HASH_STR( "Kayak" ), &vars->world_items.vehicles.kayak.enabled, 0, vars->world_items.vehicles.kayak.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.kayak, true );
					} );

				widgets.Checkbox( HASH_STR( "Minicopter" ), &vars->world_items.vehicles.minicopters.enabled, 0, vars->world_items.vehicles.minicopters.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.minicopters, true );
					} );

				widgets.Checkbox( HASH_STR( "Scrap Helicopter" ), &vars->world_items.vehicles.scrapheli.enabled, 0, vars->world_items.vehicles.scrapheli.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.scrapheli, true );
					} );

				widgets.Checkbox( HASH_STR( "Hot Air Balloon" ), &vars->world_items.vehicles.hotairbaloon.enabled, 0, vars->world_items.vehicles.hotairbaloon.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.hotairbaloon, true );
					} );

				widgets.Checkbox( HASH_STR( "Patrol Helicopter" ), &vars->world_items.vehicles.patrol_helipcoter.enabled, 0, vars->world_items.vehicles.patrol_helipcoter.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.patrol_helipcoter, true );
					} );

				widgets.Checkbox( HASH_STR( "Modular Car" ), &vars->world_items.vehicles.modular_car.enabled, 0, vars->world_items.vehicles.modular_car.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.modular_car, true );
					} );

				widgets.Checkbox( HASH_STR( "Submarine" ), &vars->world_items.vehicles.submarine.enabled, 0, vars->world_items.vehicles.submarine.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.submarine, true );
					} );

				widgets.Checkbox( HASH_STR( "Bradley" ), &vars->world_items.vehicles.bradley.enabled, 0, vars->world_items.vehicles.bradley.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.bradley, true );
					} );

				widgets.Checkbox( HASH_STR( "Trains" ), &vars->world_items.vehicles.trains.enabled, 0, vars->world_items.vehicles.trains.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.vehicles.trains, true );
					} );
			}
			cm.endchild( );
		}
		EndGroup( );
		} );

	TabsManager::get( ).add_page( 2, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Deployables" ) );
			{
				widgets.Checkbox( HASH_STR( "Show Deployables" ), &vars->world_items.deployables.enabled );
				TooltipManager::get( ).draw( HASH_STR( "This enables the deployables category to work" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Shotgun Trap" ), &vars->world_items.deployables.shotguntraps.enabled, 0, vars->world_items.deployables.shotguntraps.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.shotguntraps, true );
					} );

				widgets.Checkbox( HASH_STR( "Flame Turret" ), &vars->world_items.deployables.flameturrets.enabled, 0, vars->world_items.deployables.flameturrets.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.flameturrets, true );
					} );

				widgets.Checkbox( HASH_STR( "Auto Turret" ), &vars->world_items.deployables.autoturret.enabled, 0, vars->world_items.deployables.autoturret.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.autoturret, true );
					} );

				widgets.Checkbox( HASH_STR( "Bear Trap" ), &vars->world_items.deployables.bear_trap.enabled, 0, vars->world_items.deployables.bear_trap.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.bear_trap );
					} );

				widgets.Checkbox( HASH_STR( "Sam Site" ), &vars->world_items.deployables.samsiteturrets.enabled, 0, vars->world_items.deployables.samsiteturrets.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.samsiteturrets, true );
					} );

				widgets.Checkbox( HASH_STR( "Landmine" ), &vars->world_items.deployables.landmines.enabled, 0, vars->world_items.deployables.landmines.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.landmines );
					} );

				widgets.Checkbox( HASH_STR( "Tool Cupboard" ), &vars->world_items.deployables.cupboard.enabled, 0, vars->world_items.deployables.cupboard.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.cupboard, true );
					} );

				widgets.Checkbox( HASH_STR( "Furnace" ), &vars->world_items.deployables.furnances.enabled, 0, vars->world_items.deployables.furnances.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.furnances );
					} );

				widgets.Checkbox( HASH_STR( "Boxes" ), &vars->world_items.deployables.boxes.enabled, 0, vars->world_items.deployables.boxes.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.boxes );
					} );

				widgets.Checkbox( HASH_STR( "Vending Machine" ), &vars->world_items.deployables.vendings.enabled, 0, vars->world_items.deployables.vendings.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.vendings, true );
					} );

				widgets.Checkbox( HASH_STR( "CCTV Camera" ), &vars->world_items.deployables.cctv_cameras.enabled, 0, vars->world_items.deployables.cctv_cameras.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.cctv_cameras );
					} );

				widgets.Checkbox( HASH_STR( "Seismic Sensor" ), &vars->world_items.deployables.seismic_sensor.enabled, 0, vars->world_items.deployables.seismic_sensor.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.seismic_sensor );
					} );

				widgets.Checkbox( HASH_STR( "Sleeping Bag" ), &vars->world_items.deployables.sleeping_bags.enabled, 0, vars->world_items.deployables.sleeping_bags.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.sleeping_bags, true );
					} );

				widgets.Checkbox( HASH_STR( "Workbench 1" ), &vars->world_items.deployables.workbench_1.enabled, 0, vars->world_items.deployables.workbench_1.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.workbench_1, true );
					} );

				widgets.Checkbox( HASH_STR( "Workbench 2" ), &vars->world_items.deployables.workbench_2.enabled, 0, vars->world_items.deployables.workbench_2.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.workbench_2, true );
					} );

				widgets.Checkbox( HASH_STR( "Workbench 3" ), &vars->world_items.deployables.workbench_3.enabled, 0, vars->world_items.deployables.workbench_3.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.deployables.workbench_3, true );
					} );
			}
			cm.endchild( );
		}
		EndGroup( );
		} );

	TabsManager::get( ).add_page( 2, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Ores" ) );
			{
				widgets.Checkbox( HASH_STR( "Show Ores" ), &vars->world_items.ores.enabled );
				TooltipManager::get( ).draw( HASH_STR( "This enables the ores category to work" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Stone Ore" ), &vars->world_items.ores.stone_ore.enabled, 0, vars->world_items.ores.stone_ore.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.ores.stone_ore );
					} );

				widgets.Checkbox( HASH_STR( "Metal Ore" ), &vars->world_items.ores.metal_ore.enabled, 0, vars->world_items.ores.metal_ore.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.ores.metal_ore );
					} );

				widgets.Checkbox( HASH_STR( "Sulfur Ore" ), &vars->world_items.ores.sulfur_ore.enabled, 0, vars->world_items.ores.sulfur_ore.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.ores.sulfur_ore );
					} );
			}
			cm.endchild( );
		}
		EndGroup( );
		} );

	TabsManager::get( ).add_page( 2, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Animals" ) );
			{
				widgets.Checkbox( HASH_STR( "Show Animals" ), &vars->world_items.animals.enabled );
				TooltipManager::get( ).draw( HASH_STR( "This enables the animals category to work" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Brown Bear" ), &vars->world_items.animals.bear.enabled, 0, vars->world_items.animals.bear.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.bear, true );
					} );

				widgets.Checkbox( HASH_STR( "Polar Bear" ), &vars->world_items.animals.polar_bear.enabled, 0, vars->world_items.animals.polar_bear.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.polar_bear, true );
					} );

				widgets.Checkbox( HASH_STR( "Boar" ), &vars->world_items.animals.boar.enabled, 0, vars->world_items.animals.boar.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.boar, true );
					} );

				widgets.Checkbox( HASH_STR( "Stag" ), &vars->world_items.animals.deers.enabled, 0, vars->world_items.animals.deers.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.deers, true );
					} );

				widgets.Checkbox( HASH_STR( "Wolf" ), &vars->world_items.animals.wolf.enabled, 0, vars->world_items.animals.wolf.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.wolf, true );
					} );

				widgets.Checkbox( HASH_STR( "Chicken" ), &vars->world_items.animals.chicken.enabled, 0, vars->world_items.animals.chicken.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.chicken, true );
					} );

				widgets.Checkbox( HASH_STR( "Rideable Horse" ), &vars->world_items.animals.horse.enabled, 0, vars->world_items.animals.horse.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.horse, true );
					} );

				widgets.Checkbox( HASH_STR( "Crocodile" ), &vars->world_items.animals.crocodiles.enabled, 0, vars->world_items.animals.crocodiles.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.crocodiles, true );
					} );

				widgets.Checkbox( HASH_STR( "Orange Tiger" ), &vars->world_items.animals.tigers.enabled, 0, vars->world_items.animals.tigers.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.tigers, true );
					} );

				widgets.Checkbox( HASH_STR( "Black Panther" ), &vars->world_items.animals.panthers.enabled, 0, vars->world_items.animals.panthers.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.panthers, true );
					} );

				widgets.Checkbox( HASH_STR( "Snake" ), &vars->world_items.animals.snakes.enabled, 0, vars->world_items.animals.snakes.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.animals.snakes, true );
					} );
			}
			cm.endchild( );
		}
		EndGroup( );
		} );

	TabsManager::get( ).add_page( 2, [ & ] ( ) {
		BeginGroup( );
		{
			cm.beginchild( HASH_STR( "Terrain" ) );
			{
				widgets.Checkbox( HASH_STR( "Show Terrain" ), &vars->world_items.world.enabled );
				TooltipManager::get( ).draw( HASH_STR( "This enables the terrain category to work" ) );

				widgets.Separator( );

				widgets.Checkbox( HASH_STR( "Recycler" ), &vars->world_items.world.recyclers.enabled, 0, vars->world_items.world.recyclers.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.world.recyclers );
					} );

				widgets.Checkbox( HASH_STR( "Supply Drop" ), &vars->world_items.world.supplydrop.enabled, 0, vars->world_items.world.supplydrop.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.world.supplydrop );
					} );

				widgets.Checkbox( HASH_STR( "Corpse" ), &vars->world_items.world.corpses.enabled, 0, vars->world_items.world.corpses.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.world.corpses );
					} );

				widgets.Checkbox( HASH_STR( "Dropped" ), &vars->world_items.world.dropped.enabled, 0, vars->world_items.world.dropped.color.to_array( ), [ & ] ( ) {
					render_item_options( vars->world_items.world.dropped );

					auto& e = vars->world_items.world.categories;

					item_categories [ 0 ].selected = e.weapon;
					item_categories [ 1 ].selected = e.construction;
					item_categories [ 2 ].selected = e.items;
					item_categories [ 3 ].selected = e.resources;
					item_categories [ 4 ].selected = e.attire;
					item_categories [ 5 ].selected = e.tool;
					item_categories [ 6 ].selected = e.medical;
					item_categories [ 7 ].selected = e.food;
					item_categories [ 8 ].selected = e.ammunition;
					item_categories [ 9 ].selected = e.traps;
					item_categories [ 10 ].selected = e.misc;
					item_categories [ 11 ].selected = e.all;
					item_categories [ 12 ].selected = e.common;
					item_categories [ 13 ].selected = e.component;
					item_categories [ 14 ].selected = e.search;
					item_categories [ 15 ].selected = e.favourite;
					item_categories [ 16 ].selected = e.electrical;
					item_categories [ 17 ].selected = e.fun;

					widgets.MultiCombo( HASH_STR( "Categories" ), &item_categories );

					e.weapon = item_categories [ 0 ].selected;
					e.construction = item_categories [ 1 ].selected;
					e.items = item_categories [ 2 ].selected;
					e.resources = item_categories [ 3 ].selected;
					e.attire = item_categories [ 4 ].selected;
					e.tool = item_categories [ 5 ].selected;
					e.medical = item_categories [ 6 ].selected;
					e.food = item_categories [ 7 ].selected;
					e.ammunition = item_categories [ 8 ].selected;
					e.traps = item_categories [ 9 ].selected;
					e.misc = item_categories [ 10 ].selected;
					e.all = item_categories [ 11 ].selected;
					e.common = item_categories [ 12 ].selected;
					e.component = item_categories [ 13 ].selected;
					e.search = item_categories [ 14 ].selected;
					e.favourite = item_categories [ 15 ].selected;
					e.electrical = item_categories [ 16 ].selected;
					e.fun = item_categories [ 17 ].selected;
				} );
			}
			cm.endchild( );
		}
		EndGroup( );
	} );
}

auto menu_interface::c_interface::draw( ) -> void
{
	static bool init = false;
	if ( !init ) {
		for ( int i = 0; i < TabsManager::get( ).get_tabs( ).size( ); ++i ) {
			if ( TabsManager::get( ).get_tabs( ) [ i ].pages.empty( ) ) continue;

			TabsManager::get( ).set_tab( i );
			for ( int j = 0; j < TabsManager::get( ).get_tabs( ) [ i ].pages.size( ); ++j ) {
				TabsManager::get( ).set_subtab( j );
				TabsManager::get( ).get_tabs( ) [ i ].pages [ j ]( );
			}

			TabsManager::get( ).set_subtab( 0 );
		}

		TabsManager::get( ).set_tab( 0 );

		init = true;
	}

	SetNextWindowSize( size );
	Begin( HASH_STR( "GUI" ), 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus );
	{
		BeginChild( HASH_STR( "navbar" ), { 0, 56 }, 0, ImGuiWindowFlags_NoBackground );
		{
			ID3D11Texture2D* texture = monoauth->session->brand->get_texture( );
			if ( texture )
				GetWindowDrawList( )->AddImage( ( ImTextureID ) texture, GetWindowPos( ) + ImVec2 { GetWindowHeight( ) / 2 - 13, GetWindowHeight( ) / 2 - 13 }, GetWindowPos( ) + ImVec2 { GetWindowHeight( ) / 2 + 13, GetWindowHeight( ) / 2 + 13 } );

			SetCursorPosX( 56 );
			PushStyleColor( ImGuiCol_FrameBg, GetColorU32( ImGuiCol_FrameBg, 0.f ) );
			PushStyleVar( ImGuiStyleVar_FrameBorderSize, 0 );
			PushStyleVar( ImGuiStyleVar_FramePadding, { 16, GetWindowHeight( ) / 2 - GImGui->FontSize / 2 } );
			PushItemFlag( ImGuiItemFlags_NoNav, true );
			GetWindowDrawList( )->AddRectFilled( GetCurrentWindow( )->DC.CursorPos, GetCurrentWindow( )->DC.CursorPos + ImVec2 { 1, GetWindowHeight( ) }, GetColorU32( ImGuiCol_Border ) );
			static bool ac = false;
			if ( WidgetsManager::get( ).TextField( HASH_STR( "##search" ), SearchManager::get( ).search_buf, sizeof( SearchManager::get( ).search_buf ), { 200, 0 }, HASH_STR( "Search..." ), I_SEARCH ) ) {
				SearchManager::get( ).update( );
			}

			if ( ac && !ImGui::IsItemActive( ) && SearchManager::get( ).search_buf [ 0 ] == '\0' ) {
				ImGui::SetKeyboardFocusHere( -1 );
			}

			ac = IsItemActive( );

			PopItemFlag( );
			PopStyleVar( 2 );
			PopStyleColor( );

			static float tabs_size = 0;
			SetCursorPos( { GetWindowWidth( ) - tabs_size - 21, 0 } );
			float p1 = GetCurrentWindow( )->DC.CursorPos.x;
			BeginChild( HASH_STR( "tabs" ), { 0, GetWindowHeight( ) }, ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX );
			TabsManager::get( ).render_tabs( 13, true );
			EndChild( );
			SameLine( 0, 0 );
			tabs_size = GetCurrentWindow( )->DC.CursorPos.x - p1;
		}
		EndChild( );

		SetCursorPos( { 0, 56 } );
		PushStyleColor( ImGuiCol_ChildBg, ImColor { 0, 0, 0 }.Value );
		PushStyleColor( ImGuiCol_Border, ImColor { 255, 231, 231, 20 }.Value );
		BeginChild( HASH_STR( "main" ), { 0, -40 }, ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_Border, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse );
		{
			PopStyleColor( 2 );

			if ( strlen( SearchManager::get( ).search_buf ) == 0 && SearchManager::get( ).get_anim( ) < 0.05f ) {
				TabsManager::get( ).render_subtabs( 8 );

				auto window = GetCurrentWindow( );

				PushStyleVar( ImGuiStyleVar_Alpha, GImGui->Style.Alpha * TabsManager::get( ).get_anim( ) * GImGui->Style.Alpha );
				PushStyleVar( ImGuiStyleVar_WindowPadding, { 14, 14 } );
				BeginChild( HASH_STR( "content" ), { 0, 0 }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse );
				{
					TabsManager::get( ).draw_page( window );
				}
				EndChild( );
				PopStyleVar( 2 );
			}
			else {
				PushStyleVar( ImGuiStyleVar_WindowPadding, { 14, 14 } );
				BeginChild( HASH_STR( "content2" ), { 0, 0 }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse );
				{
					ChildManager::get( ).smoothscroll( );
					SearchManager::get( ).draw( );
				}
				EndChild( );
				PopStyleVar( );
			}
		}
		EndChild( );

		SetCursorPosY( GetCursorPosY( ) - GImGui->Style.ItemSpacing.y );
		BeginChild( HASH_STR( "footer" ), { 0, 0 }, 0, ImGuiWindowFlags_NoBackground );
		{
			SetCursorPos( { GetWindowHeight( ) / 2 - 12, GetWindowHeight( ) / 2 - 13 } );
			CompBuilder::get( ).OpenButton( HASH_STR( "lang selector" ), { 32 + fonts->get( HASH_STR( "Geist-SemiBold.ttf" ), 12.00f )->CalcTextSizeA( 12, FLT_MAX, -1, LangManager::get( ).get_lang_name( ).c_str( ) ).x, 24 }, [ & ] ( CompBuilder::OpenButtonEnv env ) {
				GetWindowDrawList( )->AddRectFilled( env.bb.Min, env.bb.Max, GetColorU32( ImGuiCol_ChildBg ), GImGui->Style.FrameRounding );
				GetWindowDrawList( )->AddText( fonts->get( HASH_STR("Glyphter.tff" ), 12.00f ), 12, { env.bb.Min.x + 6, env.bb.GetCenter( ).y - 6 }, GetColorU32( ImGuiCol_Scheme ), I_LANGUAGE__KATAKANA );
				GetWindowDrawList( )->AddText( fonts->get( HASH_STR( "Geist-SemiBold.ttf" ), 12.00f ), 12, { env.bb.Min.x + 26, env.bb.GetCenter( ).y - 6 }, GetColorU32( ImGuiCol_Text ), LangManager::get( ).get_lang_name( ).c_str( ) );

				if ( env.pressed ) {
					env.open = !env.open;
				}

				if ( env.hovered ) env.open = true;

				if ( env.anim.open > 0.05f ) {
					PushStyleVar( ImGuiStyleVar_Alpha, env.anim.open );
					PushStyleVar( ImGuiStyleVar_ItemSpacing, { 0, 0 } );
					PushStyleVar( ImGuiStyleVar_WindowRounding, GImGui->Style.FrameRounding );
					PushStyleVar( ImGuiStyleVar_WindowPadding, { 0, 8 } );
					PushStyleVar( ImGuiStyleVar_FramePadding, { 10, 8 } );
					PushStyleVar( ImGuiStyleVar_WindowBorderSize, 1 );
					PushStyleColor( ImGuiCol_WindowBg, GetColorU32( ImGuiCol_FrameBg ) );
					Begin( HASH_STR( "lang selector" ), 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove );
					{
						SetWindowPos( { env.bb.Min.x, env.bb.GetCenter( ).y - GetWindowHeight( ) / 2 } );
						SetWindowSize( { 100, ( GetCurrentWindow( )->ContentSize.y + GImGui->Style.WindowPadding.y * 2 ) * env.anim.open } );

						BringWindowToDisplayFront( GetCurrentWindow( ) );
						BringWindowToFocusFront( GetCurrentWindow( ) );

						if ( !IsWindowHovered( ImGuiHoveredFlags_AllowWhenBlockedByActiveItem ) && !env.hovered ) {
							env.open = false;
						}

						PushStyleColor( ImGuiCol_FrameBg, GetColorU32( ImGuiCol_FrameBgHovered ) );

						for ( int i = 0; i < LangManager::get( ).get_langs( ).size( ); ++i ) {
							if ( WidgetsManager::get( ).Selectable( LangManager::get( ).get_langs( ) [ i ].label, LangManager::get( ).get_lang( ) == i ) ) {
								LangManager::get( ).set_lang( i );
							}
						}

						PopStyleColor( );
					}
					End( );
					PopStyleColor( );
					PopStyleVar( 6 );
				}
				} );

			//std::string key_text = HASH_STR( "Menu: " ) + std::string( key_name_list [ vars->ui.menu_key ] );
			//ImVec2 key_text_size = ImGui::CalcTextSize( key_text.c_str( ) );

			//GetWindowDrawList( )->AddText( GetWindowPos( ) + ImVec2 { GetWindowWidth( ) - 15 - key_text_size.x, GetWindowHeight( ) / 2 - GImGui->FontSize / 2 - 1 }, GetColorU32( ImGuiCol_Text ), key_text.c_str( ) );

		}
		EndChild( );

		PopupManager::get( ).handle( );
	}
	End( );
}

#endif // !MENU_CPP
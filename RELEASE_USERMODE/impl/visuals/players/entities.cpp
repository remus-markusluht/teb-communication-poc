#ifndef ENTITIES_CPP
#define ENTITIES_CPP

#include <impl/includes.hpp>

void visuals_interface::c_visuals::players( ImDrawList* ImDrawList )
{
	const auto local_actor = entities->local_actor.load( std::memory_order_acquire );
	if ( !local_actor )
		return;

	const auto actors = entities->player_actors.load( std::memory_order_acquire );
	if ( !actors )
		return;

	for ( const auto& [key, player] : *actors ) {

		/* 	
		double actor_width = std::abs( player.bounds.right - player.bounds.left );
		double actor_height = std::abs( player.bounds.bottom - player.bounds.top );

		double actor_middle = player.bounds.left + ( actor_width / 2.00 );

		double top_text_offset = 20.00;
		double bottom_text_offset = 0.00;

		double right_text_offset = 0.00;
		double left_text_offset = 0.00;

		if ( config.boxes.is_enabled( ) && player.flags.is_in_bounds )
		{
			framework->draw_2d_box(
				ImVec2( player.bounds.left, player.bounds.top ),
				ImVec2( actor_width, actor_height ),
				color_override && elements_overide && elements_overide->boxes ? *color_override : config.boxes.color.to_im_color( ),
				config.box_thickness,
				ImDrawList
			);
		}

		if ( config.corners.is_enabled( ) && player.flags.is_in_bounds )
		{
			framework->draw_cornered_box(
				ImVec2( player.bounds.left, player.bounds.top ),
				ImVec2( actor_width, actor_height ),
				color_override && elements_overide && elements_overide->boxes ? *color_override : config.corners.color.to_im_color( ),
				config.box_thickness,
				ImDrawList
			);
		}

		if ( config.distance.is_enabled( ) && player.flags.is_in_bounds )
		{
			std::string distance = std::to_string( player.distance ) + HASH_STR( "m" );
			const ImVec2 distance_size = ImGui::CalcTextSize( distance.c_str( ) );

			const ImVec2 distance_position = ImVec2(
				actor_middle - ( distance_size.x / 2 ),
				player.bounds.bottom + bottom_text_offset
			);

			framework->text(
				distance,
				distance_position,
				vars->ui.font_size,
				color_override && elements_overide && elements_overide->distance ? *color_override : config.distance.color.to_im_color( ),
				ImDrawList
			);

			bottom_text_offset += vars->ui.font_size;
		}

		if ( config.team_id.is_enabled( ) && player.team_index && player.flags.is_in_bounds )
		{
			std::string team_id = HASH_STR( "Team " ) + std::to_string( player.team_index );
			const ImVec2 team_size = ImGui::CalcTextSize( team_id.c_str( ) );

			const ImVec2 team_position = ImVec2(
				actor_middle - ( team_size.x / 2 ),
				player.bounds.bottom + bottom_text_offset
			);

			framework->text(
				team_id,
				team_position,
				vars->ui.font_size,
				color_override && elements_overide && elements_overide->team_id ? *color_override : config.team_id.color.to_im_color( ),
				ImDrawList
			);

			bottom_text_offset += vars->ui.font_size;
		}
		*/
	}
}

#endif // !ENTITIES_CPP
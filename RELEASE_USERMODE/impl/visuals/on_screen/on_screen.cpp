#ifndef ON_SCREEN_CPP
#define ON_SCREEN_CPP

#include <impl/includes.hpp>

void visuals_interface::c_visuals::framerate( ImDrawList* ImDrawList )
{
	int framerate = static_cast< int >( ImGui::GetIO( ).Framerate );
	ImColor color = framerate < 60 ? ImColor( 255, 0, 0 ) : ImColor( 255, 255, 255 );

	std::string fps = std::to_string( framerate ) + HASH_STR( " FPS" );
	ImVec2 fps_size = ImGui::CalcTextSize( fps.c_str( ) );

	ImVec2 fps_position = ImVec2( 10, render->game_height - fps_size.y - 25.00f );

	framework->text(
		fps,
		fps_position,
		vars->ui.font_size,
		color,
		ImDrawList
	);
}

void visuals_interface::c_visuals::on_screen( ImDrawList* ImDrawList )
{
	if ( vars->ui.framerate.is_enabled( ) )
		framerate( ImDrawList );
}

#endif // !ON_SCREEN_CPP

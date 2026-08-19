#ifndef WORLD_CPP
#define WORLD_CPP

#include <impl/includes.hpp>

void visuals_interface::c_visuals::world( ImDrawList* ImDrawList )
{
	const auto actors = entities->world_actors.load( std::memory_order_acquire );
	if ( !actors )
		return;

	for ( const auto& [key, entity] : *actors ) {

	}
}

#endif // !WORLD_CPP
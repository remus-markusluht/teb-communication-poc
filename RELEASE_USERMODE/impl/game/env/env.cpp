#ifndef ENV_CPP
#define ENV_CPP

#include <impl/includes.hpp>

void env_interface::c_env::first_thread( )
{
	static constexpr ch::milliseconds base_projectile_interval = ch::milliseconds( 1 );

	ch::high_resolution_clock::time_point now = ch::high_resolution_clock::now( );

	ch::high_resolution_clock::time_point base_projectile_tick = now - base_projectile_interval;

	std::vector<ch::milliseconds> intervals =
	{
		base_projectile_interval
	};

	static ch::milliseconds lowest_interval = *std::min_element( intervals.begin( ), intervals.end( ) );

	while ( true ) {

		utility::update_function( base_projectile_interval, base_projectile_tick,
			[ & ] { base_projectile( ); }
		);

		utility::sleep_for( lowest_interval.count( ) );
	}
}

#endif // !ENV_CPP
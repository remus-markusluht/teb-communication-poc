#ifndef UTILITY_CPP
#define UTILITY_CPP

#include <impl/includes.hpp>

auto utility::update_function( ch::milliseconds time, ch::high_resolution_clock::time_point& timestamp, const std::function<void( )>& task ) -> void 
{
	ch::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now( );

	if ( ( current_time - timestamp ) >= time ) 
	{
		task( );
		timestamp = current_time;
	}
}

void utility::sleep_for( float milliseconds )
{
	static bool initialized = false;
	if ( !initialized )
	{
		ULONG actualResolution;
		LI_FN( ZwSetTimerResolution ).safe_cached( )( 1, true, &actualResolution );
		initialized = true;
	}

	LARGE_INTEGER interval { };
	interval.QuadPart = -1 * ( int ) ( milliseconds * 10000.0f );

	LI_FN( NtDelayExecution ).safe_cached( )( false, &interval );
}

void utility::copy_to_clipboard( const std::string& string )
{
	LI_FN( OpenClipboard ).safe_cached( )( 0 );
	LI_FN( EmptyClipboard ).safe_cached( )( );

	HGLOBAL hg = GlobalAlloc( GMEM_MOVEABLE, string.size( ) );
	if ( !hg ) {
		LI_FN( CloseClipboard ).safe_cached( )( );
		return;
	}

	memcpy( LI_FN( GlobalLock ).safe_cached( )( hg ), string.c_str( ), string.size( ) );

	LI_FN( GlobalUnlock ).safe_cached( )( hg );

	LI_FN( SetClipboardData ).safe_cached( )( CF_TEXT, hg );
	LI_FN( CloseClipboard ).safe_cached( )( );

	LI_FN( GlobalFree ).safe_cached( )( hg );
}

#endif // !UTILITY_CPP

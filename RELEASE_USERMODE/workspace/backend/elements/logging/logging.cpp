#ifndef LOGGING_CPP
#define LOGGING_CPP

#include <impl/includes.hpp>

void logging::console( const char* title )
{
    const auto console_handle = LI_FN( GetConsoleWindow ).safe_cached( )( );

    RECT r;
    LI_FN( GetWindowRect ).safe_cached( )( console_handle, &r );
    LI_FN( MoveWindow ).safe_cached( )( console_handle, r.left, r.top, 900, 650, TRUE );

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof( cfi );
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 16;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy( cfi.FaceName, HASH_STR( L"Cascadia Code" ) );

    LI_FN( SetCurrentConsoleFontEx ).safe_cached( )( LI_FN( GetStdHandle ).safe_cached( )( STD_OUTPUT_HANDLE ), FALSE, &cfi );
    ::SetWindowPos( console_handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
    SetConsoleTitleA( title );
}

void logging::log( const char* fmt, ... )
{
    char buffer [ 1024 ] {};

    va_list args;
    va_start( args, fmt );
    vsnprintf( buffer, sizeof( buffer ), fmt, args );
    va_end( args );

#ifdef TEST
    printf( HASH_STR( "%s\n" ), buffer );
#endif // TEST
}

void logging::error_box( u32 code )
{
    std::ostringstream message;

    message << HASH_STR( "The application encountered a fatal error and cannot continue.\n\n" )
        << HASH_STR( "System Architecture: " )
        << sizeof( void* ) * 8 << HASH_STR( "-bit\n" )
        << HASH_STR( "Error Code: 0x" ) << code << HASH_STR( "\n\n" )
        << HASH_STR( "Please restart the application." );

    LI_FN( MessageBoxA ).safe_cached( )( nullptr, message.str( ).c_str( ), HASH_STR( "Application Error" ), MB_ICONERROR | MB_OK );
    LI_FN( ExitProcess ).safe_cached( )( 1 );
}

#endif // !LOGGING_CPP

#ifndef IME_HPP
#define IME_HPP

#include <impl/includes.hpp>

namespace ime
{
	inline BOOL CALLBACK enum_windows_proc( HWND hwnd, LPARAM lParam )
	{
		struct EnumData
		{
			DWORD process_id;
			HWND hwnd;
		}*p_enum_data = ( EnumData* ) lParam;

		char class_name [ 256 ];
		char window_text [ 256 ];

		if ( LI_FN( GetClassNameA ).safe_cached( )( hwnd, class_name, sizeof( class_name ) ) && LI_FN( GetWindowTextA ).safe_cached( )( hwnd, window_text, sizeof( window_text ) ) )
		{
			if ( strcmp( class_name, HASH_STR( "IME" ) ) == 0 && strcmp( window_text, HASH_STR( "Default IME" ) ) == 0 )
			{
				DWORD window_process_id;
				LI_FN( GetWindowThreadProcessId ).safe_cached( )( hwnd, &window_process_id );

				if ( window_process_id == p_enum_data->process_id )
				{
					p_enum_data->hwnd = hwnd;
					return FALSE;
				}
			}
		}

		return TRUE;
	}

	inline HWND find_ime_window_by_process_id( DWORD process_id )
	{
		struct EnumData
		{
			DWORD process_id;
			HWND hwnd;
		} enum_data;

		enum_data.process_id = process_id;
		enum_data.hwnd = NULL;

		LI_FN( EnumWindows ).safe_cached( )( enum_windows_proc, ( LPARAM ) &enum_data );

		return enum_data.hwnd;
	}
}

#endif // ! guard
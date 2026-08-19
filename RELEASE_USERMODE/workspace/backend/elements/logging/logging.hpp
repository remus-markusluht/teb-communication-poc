#ifndef LOGGING_HPP
#define LOGGING_HPP

namespace logging {

	void console( const char* title );
	void log( const char* fmt, ... );
	void error_box( u32 code );
}

#endif // !LOGGING_HPP

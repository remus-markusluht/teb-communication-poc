#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace utility {

	NTSTATUS( NtDelayExecution )( BOOL Alertable, PLARGE_INTEGER DelayInterval );
	NTSTATUS( ZwSetTimerResolution )( IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution );

	void update_function( ch::milliseconds time, ch::high_resolution_clock::time_point& timestamp, const std::function<void( )>& task );

	static inline std::default_random_engine generator { std::random_device{ }( ) };

	template<typename T>
	T generate_number( T min, T max )
	{
		if constexpr ( std::is_integral_v<T> ) {
			std::uniform_int_distribution<T> distribution( min, max );
			return distribution( generator );
		}
		else if constexpr ( std::is_floating_point_v<T> ) {
			std::uniform_real_distribution<T> distribution( min, max );
			return distribution( generator );
		}
		else {
			static_assert( false, "generate_number: unsupported type" );
		}
	}

	void sleep_for( float milliseconds );
	void copy_to_clipboard( const std::string& string );
}

#endif // !UTILITY_HPP

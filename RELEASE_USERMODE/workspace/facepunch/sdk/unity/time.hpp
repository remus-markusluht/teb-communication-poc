#pragma once

namespace unity {

	class c_time : public sdk::c_base_class {
	public:
		inline static c_time* klass( )
		{
			static c_time* ins = nullptr;
			if ( !ins )
				ins = g_vm->read<c_time*>( g_vm->unity_player + Offsets::Instances::TimeManager_c );

			return ins;
		}

		declare_static_member( float, delta_time, 0xA8 );

		declare_static_member( float, maximum_delta_time, 0x40 );
		declare_static_member( float, maximum_particle_delta_time, 0x41 );

		declare_static_member( float, unscaled_delta_time, 0x2B );
		declare_static_member( float, fixed_unscaled_delta_time, 0x13 );

		declare_static_member( float, fixed_delta_time, 0x100 );
		declare_static_member( float, smooth_delta_time, 0xB0 );

		declare_static_member( double, time, 0x12 );
		declare_static_member( double, time_as_double, 0x90 );
		declare_static_member( float, fixed_time, 0x30 );
		declare_static_member( float, time_scale, 0xFC );

		declare_static_member( float, unscaled_time, 0x14 );
		declare_static_member( float, fixed_unscaled_time, 0x08 );

	public:
		static double tick_to_nano_seconds_conversion_factor( ) 
		{
			const double first_read = g_vm->read<double>( g_vm->unity_player + 0x1CFBB48 );
			const double second_read = g_vm->read<double>( g_vm->unity_player + 0x1CFBB50 );

			return first_read / second_read;
		}

		static double get_time_since_startup_in_seconds( ) 
		{
			double v2; // xmm0_8
			unsigned __int64 v3; // rax
			LARGE_INTEGER v5; // [rsp+30h] [rbp+8h] BYREF
			LARGE_INTEGER PerformanceCount; // [rsp+38h] [rbp+10h] BYREF

			const auto dword_181D12744 = g_vm->read<int>( g_vm->unity_player + 0x1D12744 );
			if ( dword_181D12744 == -1 )
			{
				v5.QuadPart = 0;
				QueryPerformanceCounter( &v5 );
				g_vm->write<u64>( g_vm->unity_player + 0x1D12858, v5.QuadPart );
			}

			PerformanceCount.QuadPart = 0;
			QueryPerformanceCounter( &PerformanceCount );

			const auto qword_181D12858 = g_vm->read<u64>( g_vm->unity_player + 0x1D12858 );
			const auto delta = static_cast<i64>( PerformanceCount.QuadPart - qword_181D12858 );

			if ( delta < 0 )
			{
				v3 = ( delta & 1 ) | ( static_cast<u64>( delta ) >> 1 );
				v2 = static_cast< double >( static_cast< int >( v3 ) ) + static_cast< double >( static_cast< int >( v3 ) );
			}
			else
			{
				v2 = static_cast< double >( delta );
			}

			return v2 * tick_to_nano_seconds_conversion_factor( ) / 1000000000.0;
		}

		static float realtime_since_startup( ) 
		{
			const auto v1_array = g_vm->read<u64>( g_vm->unity_player + 0x1C12B80 );
			if ( !v1_array )
				return 0.0;

			return get_time_since_startup_in_seconds( ) - g_vm->read<double>( v1_array );
		}
	};
}
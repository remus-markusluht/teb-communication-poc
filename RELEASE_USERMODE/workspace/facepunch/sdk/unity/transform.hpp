#pragma once

namespace unity {

	struct TransformData
	{
		u64 pTransformArray;
		//char pad [ 0x2 ]; // 0x20 - 0x18 no pad needed not sure why
		u64 pTransformIndices;
	};

	struct TransformAccessReadOnly
	{
		declare_member( math::vector3, scale, 0x110 );

		u64 pTransformData; // 0x0
		i32 index; // 0x8
	};

	struct Matrix34
	{
		math::quaternion vec0;
		math::quaternion vec1;
		math::quaternion vec2;
	};

	class c_transform : public c_component {
	public:
		declare_member( TransformAccessReadOnly*, read_only, 0x38 );

		// 45 0F 58 0C C0 41 8B 04 89 85 C0 0F 89 ? ? ? ? 44 0F 28 64 24
		static inline math::vector3 get_position( u64 native_transform_pointer )
		{
			static const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
			static const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
			static const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

			TransformAccessReadOnly sTransformAccessReadOnly = g_vm->read<TransformAccessReadOnly>( native_transform_pointer + 0x38 );
			if ( !sTransformAccessReadOnly.pTransformData )
				return { };

			// sTransformData = *( _QWORD* ) ( sTransformAccessReadOnly.m128i_i64 [ 0 ] + 0x18 );
			// pTransformIndices = *( _QWORD* ) ( sTransformAccessReadOnly.m128i_i64 [ 0 ] + 0x20 );

			TransformData sTransformData = g_vm->read<TransformData>( sTransformAccessReadOnly.pTransformData + 0x18 );
			if ( !sTransformData.pTransformArray || !sTransformData.pTransformIndices )
				return { };

			int index = g_vm->read<int>( sTransformData.pTransformIndices + 0x4 * sTransformAccessReadOnly.index );
			__m128 result = g_vm->read<__m128>( sTransformData.pTransformArray + 0x30 * sTransformAccessReadOnly.index );

			constexpr u32 max_itterations = 300;
			u32 itterations_done = 0;

			while ( index >= 0 && ++itterations_done < max_itterations )
			{
				Matrix34 sMatrix34 = g_vm->read<Matrix34>( sTransformData.pTransformArray + 0x30 * index );

				// we do _mm_castsi128_ps because it takes a 128-bit integer vector and converts it to 128-bit float vector (__m128)
				// because in pseudo they just implicitly cast it but we can't do that (__m128) C-style cast, but we have functions for that

				// __m128i to __m128 C-Style cast in C++ is _mm_castsi128_ps
				// __m128 to __m128i C-Style cast in C++ is _mm_castps_si128

				// (__m128)_mm_shuffle_epi32(vec1, 0x55)
				// _mm_castsi128_ps to cast _mm_shuffle_epi32 result __m128i to __m128
				// _mm_shuffle_epi32 takes in a __m128i so we convert our vec1 to sMatrix34.vec1
				// it uses vec1 cause of this line 
				// 
				// v12 = 6LL * (unsigned int)transform_index;
				// *(__m128i *)(sTransformData + 8 * v12 + 0x10);
				// 8 * 6 = 48 or 0x30 sTransformData we read a struct but it accesses it from pTransformArray which is our Matrix34
				// then 0x10 is vec1 in Matrix34 struct

				__m128 xxxx = _mm_castsi128_ps( _mm_shuffle_epi32( *( __m128i* )( &sMatrix34.vec1 ), 0x00 ) );    // xxxx
				__m128 yyyy = _mm_castsi128_ps( _mm_shuffle_epi32( *( __m128i* )( &sMatrix34.vec1 ), 0x55 ) );    // yyyy
				__m128 zwxy = _mm_castsi128_ps( _mm_shuffle_epi32( *( __m128i* )( &sMatrix34.vec1 ), 0x8E ) );    // zwxy
				__m128 wzyw = _mm_castsi128_ps( _mm_shuffle_epi32( *( __m128i* )( &sMatrix34.vec1 ), 0xDB ) );    // wzyw
				__m128 zzzz = _mm_castsi128_ps( _mm_shuffle_epi32( *( __m128i* )( &sMatrix34.vec1 ), 0xAA ) );    // zzzz
				__m128 yxwy = _mm_castsi128_ps( _mm_shuffle_epi32( *( __m128i* )( &sMatrix34.vec1 ), 0x71 ) );    // yxwy

				// sTransformData + 8 * v12 + 0x20
				// 0x20 is vec2 in Matrix34 struct
				__m128 tmp7 = _mm_mul_ps( *( __m128* )( &sMatrix34.vec2 ), result );

				result = _mm_add_ps(
					_mm_add_ps(
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps( _mm_mul_ps( yyyy, mulVec0 ), yxwy ),
									_mm_mul_ps( _mm_mul_ps( zzzz, mulVec1 ), zwxy ) ),
								_mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( tmp7 ), 0x00 ) ) ),
							tmp7 ),
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps( _mm_mul_ps( zzzz, mulVec2 ), wzyw ),
									_mm_mul_ps( _mm_mul_ps( xxxx, mulVec0 ), yxwy ) ),
								_mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( tmp7 ), 0x55 ) ) ),
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps( _mm_mul_ps( xxxx, mulVec1 ), zwxy ),
									_mm_mul_ps( _mm_mul_ps( yyyy, mulVec2 ), wzyw ) ),
								_mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( tmp7 ), 0xAA ) ) ) ) ),
					*( __m128* )( &sMatrix34.vec0 ) );

				index = g_vm->read<int>( sTransformData.pTransformIndices + 0x4 * index );
			}

			return math::vector3( result.m128_f32 [ 0 ], result.m128_f32 [ 1 ], result.m128_f32 [ 2 ] );
		}

		static inline math::quaternion get_local_rotation( u64 native_transform_pointer )
		{
			TransformAccessReadOnly sTransformAccessReadOnly = g_vm->read<TransformAccessReadOnly>( native_transform_pointer + 0x38 );
			if ( !sTransformAccessReadOnly.pTransformData )
				return { };

			TransformData sTransformData = g_vm->read<TransformData>( sTransformAccessReadOnly.pTransformData + 0x18 );
			if ( !sTransformData.pTransformArray || !sTransformData.pTransformIndices )
				return { };

			u32 index = _mm_cvtsi128_si32( _mm_srli_si128( *( __m128i* )( &sTransformAccessReadOnly ), 8 ) );

			return g_vm->read<math::quaternion>( sTransformData.pTransformArray + 0x30 * index + 0x10 );
		}

		static inline math::vector3 get_local_position( u64 native_transform_pointer )
		{
			TransformAccessReadOnly sTransformAccessReadOnly = g_vm->read<TransformAccessReadOnly>( native_transform_pointer + 0x38 );
			if ( !sTransformAccessReadOnly.pTransformData )
				return { };

			TransformData sTransformData = g_vm->read<TransformData>( sTransformAccessReadOnly.pTransformData + 0x18 );
			if ( !sTransformData.pTransformArray || !sTransformData.pTransformIndices )
				return { };

			u32 index = _mm_cvtsi128_si32( _mm_srli_si128( *( __m128i* )( &sTransformAccessReadOnly ), 8 ) );

			return g_vm->read<math::vector3>( sTransformData.pTransformArray + 0x30 * index );
		}
	};
}
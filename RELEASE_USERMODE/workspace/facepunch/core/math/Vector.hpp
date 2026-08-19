#ifndef VECTOR_HPP
#define VECTOR_HPP

#define RAD2DEG( x ) ( (float)(x) * (float)(180.f / M_PI) )
#define DEG2RAD( x ) ( (float)(x) * (float)(M_PI / 180.f) )

namespace math {

	struct quaternion;

	struct vector2 {
	public:
		float x, y;

		vector2( ) : x( 0 ), y( 0 ) { }
		vector2( float x, float y ) : x( x ), y( y ) { }
		vector2( float a ) : x( a ), y( a ) { }

		vector2 operator		+ ( const vector2& o ) const { return { x + o.x, y + o.y }; }
		vector2& operator		+= ( const vector2& o ) { x += o.x; y += o.y; return *this; }

		vector2 operator		- ( const vector2& o ) const { return { x - o.x, y - o.y }; }
		vector2& operator		-= ( const vector2& o ) { x -= o.x; y -= o.y; return *this; }

		vector2 operator		* ( float offset ) const { return { x * offset, y * offset }; }
		vector2& operator		*= ( float o ) { x *= o; y *= o; return *this; }
		vector2& operator		*= ( const vector2& o ) { x *= o.x; y *= o.y; return *this; }

		vector2 operator		/ ( float offset ) const { return { x / offset, y / offset }; }
		vector2& operator		/= ( float o ) { x /= o; y /= o; return *this; }
		vector2& operator		/= ( const vector2& o ) { x /= o.x; y /= o.y; return *this; }

		vector2& operator		=  ( const vector2& o ) { x = o.x; y = o.y; return *this; }

		u32 to_bits( float variable ) const
		{
			u32 bits;
			std::memcpy( &bits, &variable, sizeof( variable ) );
			return bits;
		}

		bool infinite( ) const { return ( to_bits( x ) & 0x7FFFFFFF ) == 0x7F800000 || ( to_bits( y ) & 0x7FFFFFFF ) == 0x7F800000; }
		bool nan( ) const { return ( to_bits( x ) & 0x7FFFFFFF ) > 0x7F800000 || ( to_bits( y ) & 0x7FFFFFFF ) > 0x7F800000; }

		bool empty( ) const
		{
			constexpr float epsilon = 1e-4f;
			return fabs( x ) < epsilon && fabs( y ) < epsilon;
		}

		bool valid( ) const { return !empty( ) && !infinite( ) && !nan( ); }

		float distance( const vector2& o ) const { return sqrtf( powf( o.x - x, 2.0 ) + powf( o.y - y, 2.0 ) ); }
		float magnitude( ) const { return sqrt( ( x * x ) + ( y * y ) ); }

		vector2 normalize( )
		{
			x = std::clamp( x, -89.0f, 89.0f );

			while ( y > 180.0f ) y -= 360.0f;
			while ( y < -180.0f ) y += 360.0f;

			return vector2( x, y );
		}

		vector2 normalized( )
		{
			float lenght = magnitude( );
			return vector2( x / lenght, y / lenght );
		}

		quaternion to_quaternion( ) const;
	};

	struct vector3 {
	public:
		float x, y, z;

		vector3( ) : x( 0 ), y( 0 ), z( 0 ) { }
		vector3( float x, float y, float z ) : x( x ), y( y ), z( z ) { }
		vector3( float a ) : x( a ), y( a ), z( a ) { }

		vector3 operator		+ ( const vector3& o ) const { return { x + o.x, y + o.y, z + o.z }; }
		vector3& operator		+= ( const vector3& o ) { x += o.x; y += o.y; z += o.z; return *this; }

		vector3 operator		- ( const vector3& o ) const { return { x - o.x, y - o.y, z - o.z }; }
		vector3& operator		-= ( const vector3& o ) { x -= o.x; y -= o.y; z -= o.z; return *this; }

		vector3 operator		* ( float offset ) const { return { x * offset, y * offset, z * offset }; }
		vector3& operator		*= ( float o ) { x *= o; y *= o; z *= o; return *this; }
		vector3& operator		*= ( const vector3& o ) { x *= o.x; y *= o.y; z *= o.z; return *this; }

		vector3 operator		/ ( float offset ) const { return { x / offset, y / offset, z / offset }; }
		vector3& operator		/= ( float o ) { x /= o; y /= o; z /= o; return *this; }
		vector3& operator		/= ( const vector3& o ) { x /= o.x; y /= o.y; z /= o.z; return *this; }

		vector3& operator		=  ( const vector3& o ) { x = o.x; y = o.y; z = o.z; return *this; }
		friend bool operator	== ( const vector3& a, const vector3& b ) { return ( std::fabs( a.x - b.x ) < 1e-6f ) && ( std::fabs( a.y - b.y ) < 1e-6f ) && ( std::fabs( a.z - b.z ) < 1e-6f ); }

		u32 to_bits( float variable ) const
		{
			u32 bits;
			std::memcpy( &bits, &variable, sizeof( variable ) );
			return bits;
		}

		bool infinite( ) const { return ( to_bits( x ) & 0x7FFFFFFF ) == 0x7F800000 || ( to_bits( y ) & 0x7FFFFFFF ) == 0x7F800000 || ( to_bits( z ) & 0x7FFFFFFF ) == 0x7F800000; }
		bool nan( ) const { return ( to_bits( x ) & 0x7FFFFFFF ) > 0x7F800000 || ( to_bits( y ) & 0x7FFFFFFF ) > 0x7F800000 || ( to_bits( z ) & 0x7FFFFFFF ) > 0x7F800000; }

		bool empty( ) const
		{
			constexpr float epsilon = 1e-4f;
			return fabs( x ) < epsilon && fabs( y ) < epsilon && fabs( z ) < epsilon;
		}

		bool valid( ) const { return !empty( ) && !infinite( ) && !nan( ); }

		float distance( const vector3& o ) const { return sqrtf( powf( o.x - x, 2.0 ) + powf( o.y - y, 2.0 ) + powf( o.z - z, 2.0 ) ); }
		float magnitude( ) const { return sqrt( ( x * x ) + ( y * y ) + ( z * z ) ); }

		float dot( vector3 b ) const { return x * b.x + y * b.y + z * b.z; }

		vector3 cross( const vector3& other ) const
		{
			return vector3( y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x );
		}

		vector3 normalize( )
		{
			x = std::clamp( x, -89.0f, 89.0f );

			while ( y > 180.0f ) y -= 360.0f;
			while ( y < -180.0f ) y += 360.0f;

			while ( z > 180.0f ) z -= 360.0f;
			while ( z < -180.0f ) z += 360.0f;

			return vector3( x, y, z );
		}

		vector3 normalized( )
		{
			float lenght = magnitude( );
			return vector3( x / lenght, y / lenght, z / lenght );
		}
	};

	struct quaternion {
	public:
		float x, y, z, w;

		quaternion( ) : x( 0 ), y( 0 ), z( 0 ), w( 0 ) { }
		quaternion( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) { }
		quaternion( float a ) : x( a ), y( a ), z( a ), w( a ) { }

		quaternion operator		+ ( const quaternion& o ) const { return { x + o.x, y + o.y, z + o.z, w + o.w }; }
		quaternion& operator	+= ( const quaternion& o ) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }

		quaternion operator		- ( const quaternion& o ) const { return { x - o.x, y - o.y, z - o.z, w - o.w }; }
		quaternion& operator	-= ( const quaternion& o ) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }

		quaternion operator		* ( float offset ) const { return { x * offset, y * offset, z * offset, w * offset }; }
		quaternion operator		* ( const quaternion& o ) const
		{
			return quaternion
			(
				w * o.x + x * o.w + y * o.z - z * o.y,
				w * o.y - x * o.z + y * o.w + z * o.x,
				w * o.z + x * o.y - y * o.x + z * o.w,
				w * o.w - x * o.x - y * o.y - z * o.z
			);
		}

		quaternion& operator		*= ( float o ) { x *= o; y *= o; z *= o; w *= o; return *this; }
		quaternion& operator		*= ( const quaternion& o ) { return *this = *this * o; }

		quaternion operator			/ ( float offset ) const { return { x / offset, y / offset, z / offset, w / offset }; }
		quaternion& operator		/= ( float o ) { x /= o; y /= o; z /= o; w /= o; return *this; }
		quaternion& operator		/= ( const quaternion& o ) { x /= o.x; y /= o.y; z /= o.z; w /= o.w; return *this; }

		quaternion& operator		=  ( const quaternion& o ) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }

		u32 to_bits( float variable ) const
		{
			u32 bits;
			std::memcpy( &bits, &variable, sizeof( variable ) );
			return bits;
		}

		bool infinite( ) const { return ( to_bits( x ) & 0x7FFFFFFF ) == 0x7F800000 || ( to_bits( y ) & 0x7FFFFFFF ) == 0x7F800000 || ( to_bits( z ) & 0x7FFFFFFF ) == 0x7F800000 || ( to_bits( w ) & 0x7FFFFFFF ) == 0x7F800000; }
		bool nan( ) const { return ( to_bits( x ) & 0x7FFFFFFF ) > 0x7F800000 || ( to_bits( y ) & 0x7FFFFFFF ) > 0x7F800000 || ( to_bits( z ) & 0x7FFFFFFF ) > 0x7F800000 || ( to_bits( w ) & 0x7FFFFFFF ) > 0x7F800000; }

		bool empty( ) const
		{
			constexpr float epsilon = 1e-4f;
			return fabs( x ) < epsilon && fabs( y ) < epsilon && fabs( z ) < epsilon && fabs( w ) < epsilon;
		}

		bool valid( ) const { return !empty( ) && !infinite( ) && !nan( ); }

		float distance( quaternion v ) const { return float( sqrtf( powf( v.x - x, 2.0 ) + powf( v.y - y, 2.0 ) + powf( v.z - z, 2.0 ) + powf( v.w - w, 2.0 ) ) ); }
		float magnitude( ) const { return sqrt( ( x * x ) + ( y * y ) + ( z * z ) + ( w * w ) ); }

		quaternion inverse( ) const { return quaternion( -x, -y, -z, w ); }

		vector3 get_forward( ) const
		{
			return vector3(
				2.0f * ( x * z + w * y ),
				2.0f * ( y * z - w * x ),
				1.0f - 2.0f * ( x * x + y * y )
			);
		}

		vector3 multiply( vector3 p ) const;
		vector3 euler_angles( ) const;
	};

	vector2 rotate_point( float angle, float range, vector2 point, float length );
}

#endif // !VECTOR_HPP
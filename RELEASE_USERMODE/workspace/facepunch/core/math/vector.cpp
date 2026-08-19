#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <impl/includes.hpp>

math::quaternion math::vector2::to_quaternion( ) const
{
	float pitch = DEG2RAD( x );
	float yaw = DEG2RAD( y );
	float roll = 0.0f;

	float halfPitch = pitch * 0.5f;
	float halfYaw = yaw * 0.5f;
	float halfRoll = roll * 0.5f;

	float cp = std::cos( halfPitch );
	float sp = std::sin( halfPitch );
	float cy = std::cos( halfYaw );
	float sy = std::sin( halfYaw );
	float cr = std::cos( halfRoll );
	float sr = std::sin( halfRoll );

	float cpcy = cp * cy;
	float spsy = sp * sy;

	math::quaternion q;
	q.x = sr * cpcy + spsy * cr;
	q.y = sp * cy * cr + cp * sy * sr;
	q.z = cp * sy * cr - sp * cy * sr;
	q.w = cpcy * cr - spsy * sr;

	return math::quaternion( q.y, q.z, -q.x, q.w );
}

math::vector3 math::quaternion::multiply( vector3 p ) const
{
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	vector3 result;

	result.x = ( 1.0f - 2.0f * ( yy + zz ) ) * p.x + ( 2.0f * ( xy - wz ) ) * p.y + ( 2.0f * ( xz + wy ) ) * p.z;
	result.y = ( 2.0f * ( xy + wz ) ) * p.x + ( 1.0f - 2.0f * ( xx + zz ) ) * p.y + ( 2.0f * ( yz - wx ) ) * p.z;
	result.z = ( 2.0f * ( xz - wy ) ) * p.x + ( 2.0f * ( yz + wx ) ) * p.y + ( 1.0f - 2.0f * ( xx + yy ) ) * p.z;

	return result;
}

math::vector3 math::quaternion::euler_angles( ) const
{
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	math::vector3 angles;

	float sinPitch = 2.0f * ( w * y - z * x );
	if ( std::abs( sinPitch ) >= 1.0f )
		angles.y = std::copysign( M_PI / 2.0f, sinPitch );
	else
		angles.y = std::asin( sinPitch );

	angles.x = std::atan2( 2.0f * ( w * x + y * z ), 1.0f - 2.0f * ( xx + yy ) );
	angles.z = std::atan2( 2.0f * ( w * z + x * y ), 1.0f - 2.0f * ( yy + zz ) );

	return angles * 57.29577951308232f;
}

math::vector2 math::rotate_point( float angle, float range, vector2 point, float length )
{
	const auto yaw = ( angle + 45.00f ) * ( 3.1415926535f / 180.00f );
	const auto view_cos = cos( yaw );
	const auto view_sin = sin( yaw );
	const auto x2 = range * ( -view_cos ) + range * view_sin;
	const auto y2 = range * ( -view_cos ) - range * view_sin;

	return { point.x + ( x2 / range * ( length ) ), point.y + ( y2 / range * ( length ) ) };
}


#endif // !VECTOR_CPP
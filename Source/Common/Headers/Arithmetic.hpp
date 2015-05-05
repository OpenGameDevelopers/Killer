#ifndef __KILLER_ARITHMETIC_HPP__
#define __KILLER_ARITHMETIC_HPP__

#include <DataTypes.hpp>
#include <cmath>

namespace Killer
{
	const KIL_FLOAT32 Epsilon = 1.0e-10f;
	const KIL_FLOAT32 HalfEpsilon = 1.0e-5f;
	const KIL_FLOAT32 Pi = 3.1415926535897932384626433832975f;
	const KIL_FLOAT32 FloatInfinite32 =
		static_cast< KIL_FLOAT32 >( 0x7F800000 );

	inline KIL_BOOL IsZero( KIL_FLOAT32 p_Value )
	{
		return ( fabsf( p_Value ) < Epsilon );
	}

	inline KIL_BOOL Absolute( KIL_FLOAT32 p_Value );

	inline KIL_FLOAT32 SquareRoot( KIL_FLOAT32 p_Value )
	{
		return ( sqrtf( p_Value ) );
	}

	inline KIL_FLOAT32 InvSquareRoot( KIL_FLOAT32 p_Value )
	{
		return ( 1.0f / sqrtf( p_Value ) );
	}

	inline KIL_BOOL Equal( KIL_FLOAT32 p_Left, KIL_FLOAT32 p_Right );
	
	inline void SinCos( KIL_FLOAT32 p_Angle, KIL_FLOAT32 &p_Sine,
		KIL_FLOAT32 &p_Cosine )
	{
		p_Sine = sinf( p_Angle );
		p_Cosine = cosf( p_Angle );
	}
}

#endif // __KILLER_ARITHMETIC_HPP__


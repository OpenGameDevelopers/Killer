#ifndef __KILLER_VECTOR3_HPP__
#define __KILLER_VECTOR3_HPP__

#include <DataTypes.hpp>

namespace Killer
{
	class Vector3
	{
	public:
		Vector3( );
		~Vector3( );
		Vector3( const Vector3 &p_Other );
		Vector3( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
			const KIL_FLOAT32 p_Z );
		Vector3 &operator=( const Vector3 &p_Other );

		void Set( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
			const KIL_FLOAT32 p_Z );

		KIL_FLOAT32 GetX( ) const;
		KIL_FLOAT32 GetY( ) const;
		KIL_FLOAT32 GetZ( ) const;

		KIL_FLOAT32 Magnitude( ) const;
		KIL_FLOAT32 MagnitudeSq( ) const;

		KIL_FLOAT32 Distance( const Vector3 &p_Other ) const;
		KIL_FLOAT32 DistanceSq( const Vector3 &p_Other ) const;

		void Normalise( );

		KIL_BOOL IsZero( ) const;
		void Zero( );

		KIL_FLOAT32 Dot( const Vector3 &p_Other ) const;
		Vector3 Cross( const Vector3 &p_Other ) const;

		void Print( ) const;

		Vector3 &operator-( );

		Vector3 operator-( const Vector3 &p_Other ) const;

		Vector3 &operator+=( const Vector3 &p_Other );

	private:
		KIL_FLOAT32	m_X;
		KIL_FLOAT32	m_Y;
		KIL_FLOAT32	m_Z;
	};
}

#endif // __KILLER_VECTOR3_HPP__


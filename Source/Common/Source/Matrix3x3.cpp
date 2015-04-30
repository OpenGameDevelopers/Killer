#include <Matrix3x3.hpp>

namespace Killer
{
	Matrix3x3::Matrix3x3( )
	{
		this->Identity( );
	}

	Matrix3x3::~Matrix3x3( )
	{
	}

	void Matrix3x3::SetColumns( const Vector3 &p_Column1,
		const Vector3 &p_Column2, const Vector3 &p_Column3 )
	{
		m_M[ 0 ] = p_Column1.GetX( );
		m_M[ 1 ] = p_Column1.GetY( );
		m_M[ 2 ] = p_Column1.GetZ( );

		m_M[ 3 ] = p_Column2.GetX( );
		m_M[ 4 ] = p_Column2.GetY( );
		m_M[ 5 ] = p_Column2.GetZ( );

		m_M[ 6 ] = p_Column3.GetX( );
		m_M[ 7 ] = p_Column3.GetY( );
		m_M[ 8 ] = p_Column3.GetZ( );
	}

	void Matrix3x3::Identity( )
	{
		m_M[ 0 ] = m_M[ 4 ] = m_M[ 8 ] = 1.0f;
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 5 ] = m_M[ 8 ] = m_M[ 7 ] = 0.0f;
	}

	Vector3 Matrix3x3::operator*( const Vector3 &p_Vector )
	{
		KIL_FLOAT32 X, Y, Z;

		X =	m_M[ 0 ] * p_Vector.GetX( ) +
			m_M[ 3 ] * p_Vector.GetY( ) +
			m_M[ 6 ] * p_Vector.GetZ( );

		Y =	m_M[ 1 ] * p_Vector.GetX( ) +
			m_M[ 4 ] * p_Vector.GetY( ) +
			m_M[ 7 ] * p_Vector.GetZ( );

		Z =	m_M[ 2 ] * p_Vector.GetX( ) +
			m_M[ 5 ] * p_Vector.GetY( ) +
			m_M[ 8 ] * p_Vector.GetZ( );

		return Vector3( X, Y, Z );
	}
}


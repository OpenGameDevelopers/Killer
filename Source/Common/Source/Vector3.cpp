#include <Vector3.hpp>
#include <Arithmetic.hpp>
#include <iostream>

namespace Killer
{
	Vector3::Vector3( ) :
		m_X( 0.0f ),
		m_Y( 0.0f ),
		m_Z( 0.0f )
	{
	}

	Vector3::~Vector3( )
	{
	}

	Vector3::Vector3( const Vector3 &p_Other ) :
		m_X( p_Other.m_X ),
		m_Y( p_Other.m_Y ),
		m_Z( p_Other.m_Z )
	{
	}

	Vector3::Vector3( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
		const KIL_FLOAT32 p_Z ) :
		m_X( p_X ),
		m_Y( p_Y ),
		m_Z( p_Z )
	{
	}

	Vector3 &Vector3::operator=( const Vector3 &p_Other )
	{
		m_X = p_Other.m_X;
		m_Y = p_Other.m_Y;
		m_Z = p_Other.m_Z;

		return *this;
	}

	void Vector3::Set( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
		const KIL_FLOAT32 p_Z )
	{
		m_X = p_X;
		m_Y = p_Y;
		m_Z = p_Z;
	}

	KIL_FLOAT32 Vector3::GetX( ) const
	{
		return m_X;
	}

	KIL_FLOAT32 Vector3::GetY( ) const
	{
		return m_Y;
	}

	KIL_FLOAT32 Vector3::GetZ( ) const
	{
		return m_Z;
	}

	KIL_FLOAT32 Vector3::Magnitude( ) const
	{
		return SquareRoot( m_X * m_X + m_Y * m_Y + m_Z * m_Z );
	}

	KIL_FLOAT32 Vector3::MagnitudeSq( ) const
	{
		return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z );
	}

	KIL_FLOAT32 Vector3::Distance( const Vector3 &p_Other ) const
	{
		KIL_FLOAT32 X = m_X - p_Other.m_X;
		KIL_FLOAT32 Y = m_Y - p_Other.m_Y;
		KIL_FLOAT32 Z = m_Z - p_Other.m_Z;

		return SquareRoot( X*X + Y*Y + Z*Z );
	}

	KIL_FLOAT32 Vector3::DistanceSq( const Vector3 &p_Other ) const
	{
		KIL_FLOAT32 X = m_X - p_Other.m_X;
		KIL_FLOAT32 Y = m_Y - p_Other.m_Y;
		KIL_FLOAT32 Z = m_Z - p_Other.m_Z;

		return ( X*X + Y*Y + Z*Z );
	}

	void Vector3::Normalise( )
	{
		KIL_FLOAT32 MagnitudeSq = this->MagnitudeSq( );

		if( Killer::IsZero( MagnitudeSq ) )
		{
			Zero( );
		}
		else
		{
			KIL_FLOAT32 Factor = InvSquareRoot( MagnitudeSq );

			m_X *= Factor;
			m_Y *= Factor;
			m_Z *= Factor;
		}
	}

	KIL_BOOL Vector3::IsZero( ) const
	{
		if( !Killer::IsZero( m_X + m_Y + m_Z ) )
		{
			return KIL_TRUE;
		}

		return KIL_FALSE;
	}

	void Vector3::Zero( )
	{
		m_X = m_Y = m_Z = 0.0f;
	}

	KIL_FLOAT32 Vector3::Dot( const Vector3 &p_Other ) const
	{
		return ( m_X * p_Other.m_X + m_Y * p_Other.m_Y + m_Z * p_Other.m_Z );
	}

	Vector3 Vector3::Cross( const Vector3 &p_Other ) const
	{
		Vector3 Cross;

		Cross.m_X = ( m_Y * p_Other.m_Z ) - ( m_Z * p_Other.m_Y );
		Cross.m_Y = ( m_Z * p_Other.m_X ) - ( m_X * p_Other.m_Z );
		Cross.m_Z = ( m_X * p_Other.m_Y ) - ( m_Y * p_Other.m_X );

		return Cross;
	}

	void Vector3::Print( ) const
	{
		std::cout << "< " << m_X << ", " << m_Y << ", " << m_Z << " >";
	}

	Vector3 &Vector3::operator-( )
	{
		m_X = -m_X;
		m_Y = -m_Y;
		m_Z = -m_Z;

		return *this;
	}

	Vector3 Vector3::operator-( const Vector3 &p_Other ) const
	{
		return Vector3( m_X - p_Other.m_X, m_Y - p_Other.m_Y,
			m_Z - p_Other.m_Z );
	}
}


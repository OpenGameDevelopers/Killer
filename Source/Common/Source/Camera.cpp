#include <Camera.hpp>
#include <Arithmetic.hpp>
#include <iostream>
#include <Matrix3x3.hpp>

namespace Killer
{
	Camera::Camera( ) :
		m_Near( 1.0f ),
		m_Far( 100.0f ),
		m_AspectRatio( 1.0f ),
		m_FieldOfView( Pi / 2 ),
		m_ProjectionMode( PROJECTIONMODE_SCREEN )
	{
		m_View.Identity( );
		m_Projection.Identity( );
		m_Position.Zero( );
	}

	Camera::~Camera( )
	{
	}

	void Camera::SetPosition( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
		const KIL_FLOAT32 p_Z )
	{
		m_Position.Set( p_X, p_Y, p_Z );
	}

	void Camera::SetPosition( const Vector3 &p_Position )
	{
		m_Position = p_Position;
	}

	void Camera::GetPosition( Vector3 &p_Position ) const
	{
		p_Position = m_Position;
	}

	void Camera::SetLookPoint( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
		const KIL_FLOAT32 p_Z )
	{
		m_LookPoint.Set( p_X, p_Y, p_Z );
	}

	void Camera::SetLookPoint( const Vector3 &p_LookPoint )
	{
		m_LookPoint = p_LookPoint;
	}

	void Camera::GetLookPoint( Vector3 &p_LookPoint ) const
	{
		p_LookPoint = m_LookPoint;
	}

	void Camera::SetWorldUp( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
		const KIL_FLOAT32 p_Z )
	{
		m_WorldUp.Set( p_X, p_Y, p_Z );
	}

	void Camera::SetWorldUp( const Vector3 &p_WorldUp )
	{
		m_WorldUp = p_WorldUp;
	}

	void Camera::GetWorldUp( Vector3 &p_WorldUp ) const
	{
		p_WorldUp = m_WorldUp;
	}

	void Camera::SetClippingPlanes( const KIL_FLOAT32 p_Near,
		const KIL_FLOAT32 p_Far )
	{
		m_Near = p_Near;
		m_Far = p_Far;
	}

	void Camera::GetClippingPlanes( KIL_FLOAT32 &p_Near,
		KIL_FLOAT32 &p_Far ) const
	{
		p_Near = m_Near;
		p_Far = m_Far;
	}

	void Camera::SetProjectionMode( const PROJECTIONMODE p_ProjectionMode )
	{
		m_ProjectionMode = p_ProjectionMode;
	}

	void Camera::GetProjectionMode( PROJECTIONMODE &p_ProjectionMode ) const
	{
		p_ProjectionMode = m_ProjectionMode;
	}

	void Camera::SetAspectRatio( const KIL_FLOAT32 p_AspectRatio )
	{
		m_AspectRatio = p_AspectRatio;
	}

	KIL_FLOAT32 Camera::GetAspectRatio( ) const
	{
		return m_AspectRatio;
	}

	void Camera::SetFieldOfView( const KIL_FLOAT32 p_FieldOfView )
	{
		m_FieldOfView = p_FieldOfView;
	}

	KIL_FLOAT32 Camera::GetFieldOfView( ) const
	{
		return m_FieldOfView;
	}

	void Camera::GetProjectionMatrix( Matrix4x4 &p_Projection ) const
	{
		p_Projection = m_Projection;
	}

	void Camera::GetViewMatrix( Matrix4x4 &p_View ) const
	{
		p_View = m_View;
	}

	KIL_UINT32 Camera::CalculateProjectionMatrix( )
	{
		switch( m_ProjectionMode )
		{
			case PROJECTIONMODE_SCREEN:
			{
				break;
			}
			case PROJECTIONMODE_ORTHOGONAL:
			{
				break;
			}
			case PROJECTIONMODE_PERSPECTIVE:
			{
				if( Killer::IsZero( m_Far - m_Near ) )
				{
					std::cout << "[Killer::Camera::CalculateProjectionMatrix] "
						"<ERROR> Far - Near planes is zero" << std::endl;

					return KIL_FAIL;
				}

				KIL_FLOAT32 D = 1.0f / tan( m_FieldOfView / 180.0f ) * Pi *
					0.5f;
				KIL_FLOAT32 Reciprocal = 1.0f / ( m_Near - m_Far );

				m_Projection.Identity( );

				m_Projection( 0, 0 ) = D / m_AspectRatio;
				m_Projection( 1, 1 ) = D;
				m_Projection( 2, 2 ) = ( m_Near + m_Far ) * Reciprocal;
				m_Projection( 2, 3 ) = 2 * m_Near * m_Far * Reciprocal;
				m_Projection( 3, 2 ) = -1.0f;
				m_Projection( 3, 3 ) = 0.0f;

				break;
			}
		}

		return KIL_OK;
	}

	KIL_UINT32 Camera::CalculateViewMatrix( )
	{
		Vector3 Direction = ( m_Position - m_LookPoint );
		Direction.Normalise( );

		Vector3 Right = m_WorldUp.Cross( Direction );
		Right.Normalise( );

		Vector3 Up = Direction.Cross( Right );
		Up.Normalise( );

		// The translation vector needs to be multiplied by the right, up, and
		// direction vectors, negated to create an inverse of the translation
		KIL_FLOAT32 PositionX = -Right.Dot( m_Position );
		KIL_FLOAT32 PositionY = -Up.Dot( m_Position );
		KIL_FLOAT32 PositionZ = -Direction.Dot( m_Position );

		// Pre-transpose the matrix, creating the matrix inverse as this is
		// an orthogonal matrix, resulting in:
		// R R R 0
		// U U U 0
		// D D D 0
		// P P P 1
		// R == Right, U == Up, D == Direction, P == Position
		m_View( 0, 3 ) = m_View( 1, 3 ) = m_View( 2, 3 ) = 0.0f;
		m_View( 3, 3 ) = 1.0f;

		m_View( 0, 0 ) = Right.GetX( );
		m_View( 0, 1 ) = Right.GetY( );
		m_View( 0, 2 ) = Right.GetZ( );

		m_View( 1, 0 ) = Up.GetX( );
		m_View( 1, 1 ) = Up.GetY( );
		m_View( 1, 2 ) = Up.GetZ( );

		m_View( 2, 0 ) = Direction.GetX( );
		m_View( 2, 1 ) = Direction.GetY( );
		m_View( 2, 2 ) = Direction.GetZ( );

		m_View( 3, 0 ) = PositionX;
		m_View( 3, 1 ) = PositionY;
		m_View( 3, 2 ) = PositionZ;

		return KIL_OK;
	}
}


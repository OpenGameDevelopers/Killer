#ifndef __KILLER_CAMERA_HPP__
#define __KILLER_CAMERA_HPP__

#include <DataTypes.hpp>
#include <Matrix4x4.hpp>
#include <Vector3.hpp>

namespace Killer
{
	typedef enum
	{
		PROJECTIONMODE_SCREEN	= 0,
		PROJECTIONMODE_ORTHOGONAL,
		PROJECTIONMODE_PERSPECTIVE
	}PROJECTIONMODE;

	class Camera
	{
	public:
		Camera( );
		~Camera( );
		Camera( const Camera &p_Other );
		Camera &operator=( const Camera &p_Other );

		void SetPosition( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
			const KIL_FLOAT32 p_Z );
		void SetPosition( const Vector3 &p_Position );
		void GetPosition( Vector3 &p_Position ) const;

		void SetLookPoint( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
			const KIL_FLOAT32 p_Z );
		void SetLookPoint( const Vector3 &p_LookPoint );
		void GetLookPoint( Vector3 &p_LookPoint ) const;

		void SetWorldUp( const KIL_FLOAT32 p_X, const KIL_FLOAT32 p_Y,
			const KIL_FLOAT32 p_Z );
		void SetWorldUp( const Vector3 &p_WorldUp );
		void GetWorldUp( Vector3 &p_WorldUp ) const;

		void SetClippingPlanes( const KIL_FLOAT32 p_Near,
			const KIL_FLOAT32 p_Far );
		void GetClippingPlanes( KIL_FLOAT32 &p_Near,
			KIL_FLOAT32 &p_Far ) const;

		void SetProjectionMode( const PROJECTIONMODE p_ViewMode );
		void GetProjectionMode( PROJECTIONMODE &p_ViewMode ) const;

		void SetAspectRatio( const KIL_FLOAT32 p_AspectRatio );
		KIL_FLOAT32 GetAspectRatio( ) const;

		void SetFieldOfView( const KIL_FLOAT32 p_FieldOfView );
		KIL_FLOAT32 GetFieldOfView( ) const;

		void GetProjectionMatrix( Matrix4x4 &p_Projection ) const;
		void GetViewMatrix( Matrix4x4 &p_View ) const;

		KIL_UINT32 CalculateProjectionMatrix( );
		KIL_UINT32 CalculateViewMatrix( );

	private:
		Matrix4x4	m_View;
		Matrix4x4	m_Projection;
		Vector3		m_Position;
		Vector3		m_LookPoint;
		Vector3		m_WorldUp;

		KIL_FLOAT32	m_Near;
		KIL_FLOAT32	m_Far;
		KIL_FLOAT32	m_AspectRatio;
		KIL_FLOAT32	m_FieldOfView;

		PROJECTIONMODE	m_ProjectionMode;
	};
}

#endif // __KILLER_CAMERA_HPP__


#ifndef __KILLER_MATRIX4X4_HPP__
#define __KILLER_MATRIX4X4_HPP__

#include <DataTypes.hpp>
#include <Vector3.hpp>

namespace Killer
{
	class Matrix4x4
	{
	public:
		Matrix4x4( );
		~Matrix4x4( );
		Matrix4x4( const Matrix4x4 &p_Other );
		Matrix4x4 &operator=( const Matrix4x4 &p_Other );

		void Identity( );

		Matrix4x4 &Translate( const Vector3 &p_Translation );

		Matrix4x4 &Rotate( const KIL_FLOAT32 p_Angle, const Vector3 &p_Axis );
		Matrix4x4 &Rotate( const KIL_FLOAT32 p_Roll, const KIL_FLOAT32 p_Pitch,
			const KIL_FLOAT32 p_Yaw );

		Matrix4x4 &RotateX( const KIL_FLOAT32 p_X );
		Matrix4x4 &RotateY( const KIL_FLOAT32 p_Y );
		Matrix4x4 &RotateZ( const KIL_FLOAT32 p_Z );

		Matrix4x4 &Scale( const KIL_FLOAT32 p_Scale );
		Matrix4x4 &Scale( const Vector3 &p_Scale );

		Matrix4x4 &ScaleX( const KIL_FLOAT32 p_X );
		Matrix4x4 &ScaleY( const KIL_FLOAT32 p_Y );
		Matrix4x4 &ScaleZ( const KIL_FLOAT32 p_Z );

		KIL_BOOL IsZero( ) const;
		KIL_BOOL IsIdentity( ) const;

		void AsFloat( KIL_FLOAT32 *p_pMatrix ) const;

		void Clean( );

		Matrix4x4 &Transpose( );
		Matrix4x4 TransposeTo( Matrix4x4 &p_Matrix ) const;
		Matrix4x4 &TransposeOf( const Matrix4x4 &p_Matrix );

		Matrix4x4 &AffineInverse( );
		void AffineInverseTo( Matrix4x4 &p_Matrix ) const;
		Matrix4x4 &AffineInverseOf( const Matrix4x4 &p_Matrix );

		Vector3 Transform( const Vector3 &p_Vector ) const;

		KIL_FLOAT32 Trace( ) const;

		// Row-column manipulator
		inline KIL_FLOAT32 &operator( )( const KIL_MEMSIZE p_Row,
			const KIL_MEMSIZE p_Column )
			{ return m_M[ p_Row + ( p_Column * 4 ) ]; }
		// Row-column accessor
		inline KIL_FLOAT32 operator( )( const KIL_MEMSIZE p_Row,
			const KIL_MEMSIZE p_Column ) const
			{ return m_M[ p_Row + ( p_Column * 4 ) ]; }

		// Modify the value at index
		inline KIL_FLOAT32 &operator[ ]( const KIL_MEMSIZE p_Index )
			{ return m_M[ p_Index ]; }
		inline KIL_FLOAT32 &operator[ ]( const int p_Index )
			{ return m_M[ p_Index ]; }

		// Access the value at index
		inline KIL_FLOAT32 operator[ ]( const KIL_MEMSIZE p_Index ) const
			{ return m_M[ p_Index ]; }
		inline KIL_FLOAT32 operator[ ]( const int p_Index ) const
			{ return m_M[ p_Index ]; }

	private:
		// The matrix is column-major
		// 0 4  8 12
		// 1 5  9 13
		// 2 6 10 14
		// 3 7 11 15
		KIL_FLOAT32 m_M[ 16 ];
	};
}

#endif // __KILLER_MATRIX4X4_HPP__


#ifndef __KILLER_MATRIX3X3_HPP__
#define __KILLER_MATRIX3X3_HPP__

#include <DataTypes.hpp>
#include <Vector3.hpp>

namespace Killer
{
	class Matrix3x3
	{
	public:
		Matrix3x3( );
		~Matrix3x3( );
		Matrix3x3( const Matrix3x3 &p_Other );
		Matrix3x3 &operator=( const Matrix3x3 &p_Other );

		void SetColumns( const Vector3 &p_Column1, const Vector3 &p_Column2,
			const Vector3 &p_Column3 );

		void Identity( );

		Vector3 operator*( const Vector3 &p_Vector );

	private:
		KIL_FLOAT32	m_M[ 9 ];
	};
}

#endif // __KILLER_MATRIX3X3_HPP__


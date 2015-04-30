#ifndef __KILLER_VERTEXATTRIBUTES_HPP__
#define __KILLER_VERTEXATTRIBUTES_HPP__

#include <DataTypes.hpp>
#include <GLES2/gl2.h>

namespace Killer
{
	typedef enum
	{
		VERTEXATTRIBUTE_TYPE_UNKNOWN= 0,
		VERTEXATTRIBUTE_TYPE_VEC1,
		VERTEXATTRIBUTE_TYPE_VEC2,
		VERTEXATTRIBUTE_TYPE_VEC3,
		VERTEXATTRIBUTE_TYPE_VEC4,
		VERTEXATTRIBUTE_TYPE_MAT2X2,
		VERTEXATTRIBUTE_TYPE_MAT3X3,
		VERTEXATTRIBUTE_TYPE_MAT4X4,
	}VERTEXATTRIBUTE_TYPE;

	class VertexAttributes
	{
	public:
		explicit VertexAttributes( KIL_MEMSIZE p_MaximumVertexAttributes );
		~VertexAttributes( );
		
		VertexAttributes( const VertexAttributes &p_Other );
		VertexAttributes &operator=( const VertexAttributes &p_Other );

		KIL_UINT32 AddVertexAttribute( VERTEXATTRIBUTE_TYPE p_Type );

		VERTEXATTRIBUTE_TYPE GetAttributeAt( const KIL_MEMSIZE p_Index ) const;

		KIL_MEMSIZE GetVertexAttributeCount( ) const;
		KIL_UINT32 GetVertexAttributes(
			VERTEXATTRIBUTE_TYPE *p_pAttributes ) const;

		KIL_MEMSIZE GetStride( ) const;

	private:
		KIL_MEMSIZE 			m_MaximumVertexAttributes;
		KIL_MEMSIZE				m_AttributeCount;
		KIL_MEMSIZE				m_Stride;
		VERTEXATTRIBUTE_TYPE	*m_pAttributes;
	};

	KIL_MEMSIZE ConvertVertexAttributeToSize(
		const VERTEXATTRIBUTE_TYPE p_Type );
	KIL_MEMSIZE ConvertVertexAttributeToElementCount( 
		const VERTEXATTRIBUTE_TYPE p_Type );
	GLenum ConvertVertexAttributeToGLenum(
		const VERTEXATTRIBUTE_TYPE p_Type );
}

#endif // __KILLER_VERTEXATTRIBUTES_HPP__


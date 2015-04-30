#ifndef __KILLER_VERTEXATTRIBUTES_HPP__
#define __KILLER_VERTEXATTRIBUTES_HPP__

#include <DataTypes.hpp>

namespace Killer
{
	typedef enum
	{
		VERTEXATTRIBUTE_TYPE_VEC1,
		VERTEXATTRIBUTE_TYPE_VEC2,
		VERTEXATTRIBUTE_TYPE_VEC3,
		VERTEXATTRIBUTE_TYPE_VEC4,
		VERTEXATTRIBUTE_TYPE_MAT2X2,
		VERTEXATTRIBUTE_TYPE_MAT3X3,
		VERTEXATTRIBUTE_TYPE_MAT4X4
	}VERTEXATTRIBUTE_TYPE;

	class VertexAttributes
	{
	public:
		explicit VertexAttributes( KIL_MEMSIZE p_MaximumVertexAttributes );
		~VertexAttributes( );
		
		VertexAttributes( const VertexAttributes &p_Other );
		VertexAttributes &operator=( const VertexAttributes &p_Other );

		KIL_UINT32 AddVertexAttribute( VERTEXATTRIBUTE_TYPE p_Type );

		KIL_MEMSIZE GetVertexAttributeCount( ) const;
		KIL_UINT32 GetVertexAttributes( KIL_UINT8 *p_pAttributes ) const;

	private:
		KIL_MEMSIZE m_MaximumVertexAttributes;
		KIL_MEMSIZE	m_AttributeCount;
		KIL_UINT8	*m_pAttributes;
	};
}

#endif // __KILLER_VERTEXATTRIBUTES_HPP__


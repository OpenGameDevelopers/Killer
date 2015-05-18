#ifndef __KILLER_VERTEXATTRIBUTES_HPP__
#define __KILLER_VERTEXATTRIBUTES_HPP__

#include <DataTypes.hpp>
#include <GLES2/gl2.h>
#include <vector>

namespace Killer
{
	typedef enum
	{
		VERTEXATTRIBUTE_TYPE_UNKNOWN= 0,
		VERTEXATTRIBUTE_TYPE_FLOAT1,
		VERTEXATTRIBUTE_TYPE_FLOAT2,
		VERTEXATTRIBUTE_TYPE_FLOAT3,
		VERTEXATTRIBUTE_TYPE_FLOAT4,
		VERTEXATTRIBUTE_TYPE_MAT2X2,
		VERTEXATTRIBUTE_TYPE_MAT3X3,
		VERTEXATTRIBUTE_TYPE_MAT4X4,
	}VERTEXATTRIBUTE_TYPE;

	typedef enum
	{
		VERTEXATTRIBUTE_INTENT_UNKNOWN	= 0,
		VERTEXATTRIBUTE_INTENT_POSITION,
		VERTEXATTRIBUTE_INTENT_NORMAL,
		VERTEXATTRIBUTE_INTENT_TEXTURE,
		VERTEXATTRIBUTE_INTENT_COLOUR,
		VERTEXATTRIBUTE_INTENT_TANGENT,
		VERTEXATTRIBUTE_INTENT_BINORMAL
	}VERTEXATTRIBUTE_INTENT;

	struct VERTEXATTRIBUTE
	{
		VERTEXATTRIBUTE_TYPE	Type;
		VERTEXATTRIBUTE_INTENT	Intent;
	};

	class VertexAttributes
	{
	public:
		explicit VertexAttributes( KIL_MEMSIZE p_MaximumVertexAttributes );
		~VertexAttributes( );
		
		VertexAttributes( const VertexAttributes &p_Other );
		VertexAttributes &operator=( const VertexAttributes &p_Other );

		KIL_UINT32 AddVertexAttribute( VERTEXATTRIBUTE_TYPE p_Type,
			VERTEXATTRIBUTE_INTENT p_Intent );

		struct VERTEXATTRIBUTE GetAttributeAt(
			const KIL_MEMSIZE p_Index ) const;

		KIL_MEMSIZE GetVertexAttributeCount( ) const;
		KIL_UINT32 GetVertexAttributes(
			struct VERTEXATTRIBUTE *p_pAttributes ) const;

		KIL_MEMSIZE GetStride( ) const;

	private:
		KIL_MEMSIZE 							m_MaximumVertexAttributes;
		KIL_MEMSIZE								m_AttributeCount;
		KIL_MEMSIZE								m_Stride;
		std::vector< struct VERTEXATTRIBUTE >	m_Attributes;
	};

	KIL_MEMSIZE ConvertVertexAttributeToSize(
		const struct VERTEXATTRIBUTE p_Attribute );
	KIL_MEMSIZE ConvertVertexAttributeToElementCount( 
		const struct VERTEXATTRIBUTE p_Attribute );
	GLenum ConvertVertexAttributeToGLenum(
		const struct VERTEXATTRIBUTE p_Attribute );
}

#endif // __KILLER_VERTEXATTRIBUTES_HPP__


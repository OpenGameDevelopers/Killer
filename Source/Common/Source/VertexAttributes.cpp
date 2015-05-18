#include <VertexAttributes.hpp>
#include <cstring>
#include <iostream>

namespace Killer
{
	VertexAttributes::VertexAttributes(
		KIL_MEMSIZE p_MaximumVertexAttributes ) :
		m_MaximumVertexAttributes( p_MaximumVertexAttributes ),
		m_AttributeCount( 0 ),
		m_Stride( 0 )
	{
	}

	VertexAttributes::~VertexAttributes( )
	{
	}

	VertexAttributes::VertexAttributes( const VertexAttributes &p_Other ) :
		m_MaximumVertexAttributes( p_Other.m_MaximumVertexAttributes ),
		m_AttributeCount( p_Other.m_AttributeCount ),
		m_Stride( p_Other.m_Stride )
	{
		for( KIL_MEMSIZE Attribute = 0;
			Attribute < p_Other.m_Attributes.size( ); ++Attribute )
		{
			m_Attributes.push_back( p_Other.m_Attributes[ Attribute ] );
		}
	}

	VertexAttributes &VertexAttributes::operator=(
		const VertexAttributes &p_Other )
	{
		m_MaximumVertexAttributes = p_Other.m_MaximumVertexAttributes;
		m_AttributeCount = p_Other.m_AttributeCount;
		m_Stride = p_Other.m_Stride;

		for( KIL_MEMSIZE Attribute = 0;
			Attribute < p_Other.m_Attributes.size( ); ++Attribute )
		{
			m_Attributes.push_back( p_Other.m_Attributes[ Attribute ] );
		}

		return *this;
	}

	KIL_UINT32 VertexAttributes::AddVertexAttribute(
		VERTEXATTRIBUTE_TYPE p_Type,
		VERTEXATTRIBUTE_INTENT p_Intent )
	{
		if( m_AttributeCount > m_MaximumVertexAttributes )
		{
			return KIL_FAIL;
		}

		struct VERTEXATTRIBUTE Attribute;
		Attribute.Type = p_Type;
		Attribute.Intent = p_Intent;

		m_Attributes.push_back( Attribute );
		m_Stride += ConvertVertexAttributeToSize( Attribute );

		++m_AttributeCount;

		return KIL_OK;
	}

	struct VERTEXATTRIBUTE VertexAttributes::GetAttributeAt(
		const KIL_MEMSIZE p_Index ) const
	{
		if( p_Index < m_AttributeCount )
		{
			return m_Attributes[ p_Index ];
		}

		struct VERTEXATTRIBUTE Unknown;

		Unknown.Type = VERTEXATTRIBUTE_TYPE_UNKNOWN;
		Unknown.Intent = VERTEXATTRIBUTE_INTENT_UNKNOWN;

		return Unknown;
	}

	KIL_MEMSIZE VertexAttributes::GetVertexAttributeCount( ) const
	{
		return m_AttributeCount;
	}

	KIL_UINT32 VertexAttributes::GetVertexAttributes(
		struct VERTEXATTRIBUTE *p_pAttributes ) const
	{
		if( p_pAttributes )
		{
			for( KIL_MEMSIZE i = 0; i < m_AttributeCount; ++i )
			{
				p_pAttributes[ i ] = m_Attributes[ i ];
			}

			return KIL_OK;
		}

		return KIL_FAIL;
	}

	KIL_MEMSIZE VertexAttributes::GetStride( ) const
	{
		return m_Stride;
	}

	KIL_MEMSIZE ConvertVertexAttributeToSize(
		const VERTEXATTRIBUTE p_Attribute )
	{
		switch( p_Attribute.Type )
		{
			case VERTEXATTRIBUTE_TYPE_UNKNOWN:
			{
				return 0;
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT1:
			{
				return sizeof( KIL_FLOAT32 );
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT2:
			{
				return sizeof( KIL_FLOAT32 ) * 2;
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT3:
			{
				return sizeof( KIL_FLOAT32 ) * 3;
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT4:
			{
				return sizeof( KIL_FLOAT32 ) * 4;
			}
			case VERTEXATTRIBUTE_TYPE_MAT2X2:
			{
				return sizeof( KIL_FLOAT32 ) * 2 * 2;
			}
			case VERTEXATTRIBUTE_TYPE_MAT3X3:
			{
				return sizeof( KIL_FLOAT32 ) * 3 * 3;
			}
			case VERTEXATTRIBUTE_TYPE_MAT4X4:
			{
				return sizeof( KIL_FLOAT32 ) * 4 * 4;
			}
		}

		return 0;
	}


	KIL_MEMSIZE ConvertVertexAttributeToElementCount( 
		const struct VERTEXATTRIBUTE p_Attribute )
	{
		switch( p_Attribute.Type )
		{
			case VERTEXATTRIBUTE_TYPE_UNKNOWN:
			{
				return 0;
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT1:
			{
				return 1;
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT2:
			{
				return 2;
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT3:
			{
				return 3; 
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT4:
			case VERTEXATTRIBUTE_TYPE_MAT2X2:
			{
				return 4;
			}
			case VERTEXATTRIBUTE_TYPE_MAT3X3:
			{
				return 9;
			}
			case VERTEXATTRIBUTE_TYPE_MAT4X4:
			{
				return 16;
			}
		}

		return 0;
	}

	GLenum ConvertVertexAttributeToGLenum(
		const struct VERTEXATTRIBUTE p_Attribute )
	{
		switch( p_Attribute.Type )
		{
			case VERTEXATTRIBUTE_TYPE_UNKNOWN:
			{
				break;
			}
			case VERTEXATTRIBUTE_TYPE_FLOAT1:
			case VERTEXATTRIBUTE_TYPE_FLOAT2:
			case VERTEXATTRIBUTE_TYPE_FLOAT3:
			case VERTEXATTRIBUTE_TYPE_FLOAT4:
			case VERTEXATTRIBUTE_TYPE_MAT2X2:
			case VERTEXATTRIBUTE_TYPE_MAT3X3:
			case VERTEXATTRIBUTE_TYPE_MAT4X4:
			{
				return GL_FLOAT;
			}
		}

		return GL_INVALID_ENUM;
	}
}


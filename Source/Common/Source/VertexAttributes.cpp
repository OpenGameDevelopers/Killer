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
		m_pAttributes = new VERTEXATTRIBUTE_TYPE[ m_MaximumVertexAttributes ];
		memset( m_pAttributes, 0,
			sizeof( VERTEXATTRIBUTE_TYPE ) * m_MaximumVertexAttributes );
	}

	VertexAttributes::~VertexAttributes( )
	{
		if( m_pAttributes )
		{
			delete [ ] m_pAttributes;
			m_pAttributes = 0;
		}
	}

	VertexAttributes::VertexAttributes( const VertexAttributes &p_Other ) :
		m_MaximumVertexAttributes( p_Other.m_MaximumVertexAttributes ),
		m_AttributeCount( p_Other.m_AttributeCount ),
		m_Stride( p_Other.m_Stride )
	{
		m_pAttributes = new VERTEXATTRIBUTE_TYPE[ m_MaximumVertexAttributes ];
		for( KIL_MEMSIZE i = 0; i < m_AttributeCount; ++i )
		{
			m_pAttributes[ i ] = p_Other.m_pAttributes[ i ];
		}
	}

	VertexAttributes &VertexAttributes::operator=(
		const VertexAttributes &p_Other )
	{
		m_MaximumVertexAttributes = p_Other.m_MaximumVertexAttributes;
		m_AttributeCount = p_Other.m_AttributeCount;
		m_Stride = p_Other.m_Stride;

		m_pAttributes = new VERTEXATTRIBUTE_TYPE[ m_MaximumVertexAttributes ];

		for( KIL_MEMSIZE i = 0; i < m_AttributeCount; ++i )
		{
			m_pAttributes[ i ] = p_Other.m_pAttributes[ i ];
		}

		return *this;
	}

	KIL_UINT32 VertexAttributes::AddVertexAttribute(
		VERTEXATTRIBUTE_TYPE p_Type )
	{
		if( m_AttributeCount > m_MaximumVertexAttributes )
		{
			return KIL_FAIL;
		}

		m_pAttributes[ m_AttributeCount ] = p_Type;
		m_Stride += ConvertVertexAttributeToSize( p_Type );

		++m_AttributeCount;

		return KIL_OK;
	}

	VERTEXATTRIBUTE_TYPE VertexAttributes::GetAttributeAt(
		const KIL_MEMSIZE p_Index ) const
	{
		if( p_Index < m_AttributeCount )
		{
			return m_pAttributes[ p_Index ];			
		}

		return VERTEXATTRIBUTE_TYPE_UNKNOWN;
	}

	KIL_MEMSIZE VertexAttributes::GetVertexAttributeCount( ) const
	{
		return m_AttributeCount;
	}

	KIL_UINT32 VertexAttributes::GetVertexAttributes(
		VERTEXATTRIBUTE_TYPE *p_pAttributes ) const
	{
		if( p_pAttributes )
		{
			for( KIL_MEMSIZE i = 0; i < m_AttributeCount; ++i )
			{
				p_pAttributes[ i ] = m_pAttributes[ i ];
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
		const VERTEXATTRIBUTE_TYPE p_Type )
	{
		switch( p_Type )
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
		const VERTEXATTRIBUTE_TYPE p_Type )
	{
		switch( p_Type )
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
		const VERTEXATTRIBUTE_TYPE p_Type )
	{
		switch( p_Type )
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


#include <VertexAttributes.hpp>
#include <cstring>

namespace Killer
{
	VertexAttributes::VertexAttributes(
		KIL_MEMSIZE p_MaximumVertexAttributes ) :
		m_MaximumVertexAttributes( p_MaximumVertexAttributes ),
		m_AttributeCount( 0 )
	{
		m_pAttributes = new KIL_UINT8[ m_MaximumVertexAttributes ];
		memset( m_pAttributes, 0,
			sizeof( KIL_UINT8 ) * m_MaximumVertexAttributes );
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
		m_AttributeCount( p_Other.m_AttributeCount )
	{
		m_pAttributes = new KIL_UINT8[ m_MaximumVertexAttributes ];
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

		m_pAttributes = new KIL_UINT8[ m_MaximumVertexAttributes ];

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

		++m_AttributeCount;

		return KIL_OK;
	}

	KIL_MEMSIZE VertexAttributes::GetVertexAttributeCount( ) const
	{
		return m_AttributeCount;
	}

	KIL_UINT32 VertexAttributes::GetVertexAttributes(
		KIL_UINT8 *p_pAttributes ) const
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
}


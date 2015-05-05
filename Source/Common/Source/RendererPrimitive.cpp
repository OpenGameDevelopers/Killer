#include <RendererPrimitive.hpp>
#include <GLESExtender.hpp>
#include <iostream>

#define BUFFER_OFFSET( Offset ) ( ( void * ) KIL_NULL + ( Offset ) )

namespace Killer
{
	RendererPrimitive::RendererPrimitive( )	:
		m_Type( PRIMITIVE_TYPE_UNKNOWN ),
		m_Stride( 0 ),
		m_VertexCount( 0 ),
		m_IndexCount( 0 ),
		m_PolygonCount( 0 ),
		m_ID( 0 ),
		m_GLType( GL_INVALID_ENUM ),
		m_VertexBufferObject( 0 ),
		m_IndexBufferObject( 0 ),
		m_VertexArrayObject( 0 ),
		m_DrawWireframe( KIL_FALSE )
	{
	}

	RendererPrimitive::~RendererPrimitive( )
	{
		this->Destroy( );
	}

	KIL_UINT32 RendererPrimitive::Create( const KIL_BYTE *p_pVertices,
		const KIL_UINT16 *p_pIndices, const KIL_MEMSIZE p_VertexCount,
		const KIL_MEMSIZE p_IndexCount,
		const VertexAttributes &p_VertexAttributes,
		const PRIMITIVE_TYPE p_Type )
	{
		if( p_pVertices == KIL_NULL )
		{
			return KIL_FAIL;
		}

		if( p_pIndices == KIL_NULL )
		{
			return KIL_FAIL;
		}

		switch( p_Type )
		{
			case PRIMITIVE_TYPE_TRIANGLE_LIST:
			{
				m_PolygonCount = p_IndexCount / 3;
				m_GLType = GL_TRIANGLES;
				break;
			}
			case PRIMITIVE_TYPE_TRIANGLE_STRIP:
			{
				m_PolygonCount = p_IndexCount - 2;
				m_GLType = GL_TRIANGLE_STRIP;
				break;
			}
			case PRIMITIVE_TYPE_TRIANGLE_FAN:
			{
				m_PolygonCount = p_IndexCount - 2;
				m_GLType = GL_TRIANGLE_FAN;
				break;
			}
			case PRIMITIVE_TYPE_LINE_LIST:
			{
				m_PolygonCount = p_IndexCount / 2;
				m_GLType = GL_LINES;
				break;
			}
			case PRIMITIVE_TYPE_LINE_STRIP:
			{
				m_PolygonCount = p_IndexCount - 1;
				m_GLType = GL_LINE_STRIP;
				break;
			}
			case PRIMITIVE_TYPE_LINE_LOOP:
			{
				m_PolygonCount = p_IndexCount;
				m_GLType = GL_LINE_LOOP;
				break;
			}
			case PRIMITIVE_TYPE_UNKNOWN:
			{
				return KIL_FAIL;
			}
		}

		if( m_PolygonCount == 0 )
		{
			return KIL_FAIL;
		}

		m_Stride = p_VertexAttributes.GetStride( );

		glGenBuffers( 1, &m_VertexBufferObject );
		glGenBuffers( 1, &m_IndexBufferObject );
		glGenVertexArrays( 1, &m_VertexArrayObject );

		glBindVertexArray( m_VertexArrayObject );
		glBindBuffer( GL_ARRAY_BUFFER, m_VertexBufferObject );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject );

		KIL_MEMSIZE Offset = 0;

		for( KIL_MEMSIZE Index = 0;
			Index < p_VertexAttributes.GetVertexAttributeCount( ); ++Index )
		{
			KIL_MEMSIZE Dimension = 0;
			KIL_MEMSIZE TypeSize = 0;
			GLenum Type = GL_INVALID_ENUM;
			VERTEXATTRIBUTE_TYPE Attribute =
				p_VertexAttributes.GetAttributeAt( Index );

			Type = ConvertVertexAttributeToGLenum( Attribute );
			TypeSize = ConvertVertexAttributeToSize( Attribute );
			Dimension = ConvertVertexAttributeToElementCount( Attribute );

			glVertexAttribPointer( Index, Dimension, Type, GL_FALSE,
				m_Stride, BUFFER_OFFSET( Offset ) );

			Offset += TypeSize;
			glEnableVertexAttribArray( Index );
		}

		glBufferData( GL_ARRAY_BUFFER, p_VertexCount * m_Stride,
			p_pVertices, GL_STATIC_DRAW );

		GLenum Error = glGetError( );

		if( Error == GL_OUT_OF_MEMORY )
		{
			this->Destroy( );

			return KIL_FAIL;
		}

		glBufferData( GL_ELEMENT_ARRAY_BUFFER,
			p_IndexCount * sizeof( KIL_UINT16 ), p_pIndices, GL_STATIC_DRAW );

		Error = glGetError( );
		
		if( Error == GL_OUT_OF_MEMORY )
		{
			this->Destroy( );

			return KIL_FAIL;
		}

		m_VertexCount = p_VertexCount;
		m_IndexCount = p_IndexCount;

		glBindVertexArray( 0 );

		return KIL_OK;
	}

	void RendererPrimitive::Destroy( )
	{
		glDeleteBuffers( 1, &m_VertexBufferObject );
		glDeleteBuffers( 1, &m_IndexBufferObject );
		glDeleteVertexArrays( 1, &m_VertexArrayObject );
	}

	KIL_UINT32 RendererPrimitive::SetPrimitiveType(
		const PRIMITIVE_TYPE p_Type )
	{
		m_Type = p_Type;

		KIL_MEMSIZE OldPolygonCount = m_PolygonCount;

		switch( p_Type )
		{
			case PRIMITIVE_TYPE_TRIANGLE_LIST:
			{
				m_PolygonCount = m_IndexCount / 3;
				m_GLType = GL_TRIANGLES;
				break;
			}
			case PRIMITIVE_TYPE_TRIANGLE_STRIP:
			{
				m_PolygonCount = m_IndexCount - 2;
				m_GLType = GL_TRIANGLE_STRIP;
				break;
			}
			case PRIMITIVE_TYPE_TRIANGLE_FAN:
			{
				m_PolygonCount = m_IndexCount - 2;
				m_GLType = GL_TRIANGLE_FAN;
				break;
			}
			case PRIMITIVE_TYPE_LINE_LIST:
			{
				m_PolygonCount = m_IndexCount / 2;
				m_GLType = GL_LINES;
				break;
			}
			case PRIMITIVE_TYPE_LINE_STRIP:
			{
				m_PolygonCount = m_IndexCount - 1;
				m_GLType = GL_LINE_STRIP;
				break;
			}
			case PRIMITIVE_TYPE_LINE_LOOP:
			{
				m_PolygonCount = m_IndexCount;
				m_GLType = GL_LINE_LOOP;
				break;
			}
			case PRIMITIVE_TYPE_UNKNOWN:
			{
				return KIL_FAIL;
			}
		}

		if( m_PolygonCount == 0 )
		{
			m_PolygonCount = OldPolygonCount;

			return KIL_FAIL;
		}

		m_Type = p_Type;

		return KIL_OK;
	}

	void RendererPrimitive::ToggleWireframe( )
	{
		m_DrawWireframe = !m_DrawWireframe;
	}

	KIL_UINT32 RendererPrimitive::Render( )
	{
		if( m_PolygonCount == 0 )
		{
			return KIL_FAIL;
		}

		glBindVertexArray( m_VertexArrayObject );
		glBindBuffer( GL_ARRAY_BUFFER, m_VertexBufferObject );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject );
		
		if( m_DrawWireframe )
		{
			for( KIL_MEMSIZE Index = 0; Index < m_IndexCount; Index += 3 )
			{
				glDrawElements( GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT,
					BUFFER_OFFSET( Index * sizeof( GLushort ) ) );
			}
		}
		else
		{
			glDrawElements( m_GLType, m_IndexCount, GL_UNSIGNED_SHORT,
				BUFFER_OFFSET( 0 ) );
		}

		return KIL_OK;
	}
}


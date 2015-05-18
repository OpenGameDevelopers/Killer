#include <RendererPrimitive.hpp>
#include <GLESExtender.hpp>
#include <Memory.hpp>
#include <Vector3.hpp>
#include <iostream>
#include <cstring>

#define BUFFER_OFFSET( Offset ) ( ( unsigned char * ) KIL_NULL + ( Offset ) )

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
		m_NormalsVertexBufferObject( 0 ),
		m_NormalsIndexBufferObject( 0 ),
		m_NormalsVertexArrayObject( 0 ),
		m_WireframeVertexBufferObject( 0 ),
		m_WireframeIndexBufferObject( 0 ),
		m_WireframeVertexArrayObject( 0 )
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
		KIL_SINT32 PositionOffset = -1;
		KIL_SINT32 NormalsOffset = -1;

		for( KIL_MEMSIZE Index = 0;
			Index < p_VertexAttributes.GetVertexAttributeCount( ); ++Index )
		{
			KIL_MEMSIZE Dimension = 0;
			KIL_MEMSIZE TypeSize = 0;
			GLenum Type = GL_INVALID_ENUM;
			struct VERTEXATTRIBUTE Attribute =
				p_VertexAttributes.GetAttributeAt( Index );

			Type = ConvertVertexAttributeToGLenum( Attribute );
			TypeSize = ConvertVertexAttributeToSize( Attribute );
			Dimension = ConvertVertexAttributeToElementCount( Attribute );
	
			if( Attribute.Intent == VERTEXATTRIBUTE_INTENT_POSITION )
			{
				PositionOffset = Offset;
			}

			if( Attribute.Intent == VERTEXATTRIBUTE_INTENT_NORMAL )
			{
				NormalsOffset = Offset;
			}

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
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		if( ( NormalsOffset != -1 ) && ( PositionOffset != -1 ) )
		{
			glGenBuffers( 1, &m_NormalsVertexBufferObject );
			glGenBuffers( 1, &m_NormalsIndexBufferObject );
			glGenVertexArrays( 1, &m_NormalsVertexArrayObject );

			glBindVertexArray( m_NormalsVertexArrayObject );
			glBindBuffer( GL_ARRAY_BUFFER, m_NormalsVertexBufferObject );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,
				m_NormalsIndexBufferObject );

			glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET( 0 ) );

			glEnableVertexAttribArray( 0 );

			struct NORMALPOSITION
			{
				KIL_FLOAT32 Start[ 3 ];
				KIL_FLOAT32 End[ 3 ];
			};

			struct NORMALPOSITION *pNormalPosition =
				new NORMALPOSITION[ m_VertexCount ];

			for( KIL_MEMSIZE Vertex = 0; Vertex < m_VertexCount; ++Vertex )
			{
				memcpy( pNormalPosition[ Vertex ].Start,
					p_pVertices + ( Vertex * m_Stride ) + PositionOffset, 12 );
				memcpy( pNormalPosition[ Vertex ].End,
					p_pVertices + ( Vertex * m_Stride ) + NormalsOffset, 12 );

				Vector3 Normal( pNormalPosition[ Vertex ].End[ 0 ],
					pNormalPosition[ Vertex ].End[ 1 ],
					pNormalPosition[ Vertex ].End[ 2 ] );

				Vector3 Position( pNormalPosition[ Vertex ].Start[ 0 ],
					pNormalPosition[ Vertex ].Start[ 1 ],
					pNormalPosition[ Vertex ].Start[ 2 ] );

				Normal += Position;

				memcpy( pNormalPosition[ Vertex ].End, &Normal, 12 );
			}

			KIL_UINT16 *pNormalsIndices = new KIL_UINT16[ m_VertexCount * 2 ];

			for( KIL_MEMSIZE Index = 0; Index < m_VertexCount * 2; ++Index )
			{
				pNormalsIndices[ Index ] = Index;
			}

			glBufferData( GL_ARRAY_BUFFER,
				m_VertexCount * sizeof( struct NORMALPOSITION ),
				pNormalPosition, GL_STATIC_DRAW );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( KIL_UINT16 ) *
				m_VertexCount * 2, pNormalsIndices, GL_STATIC_DRAW );

			glBindVertexArray( 0 );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

			SafeDeleteArray< KIL_UINT16 >( pNormalsIndices );
			SafeDeleteArray< NORMALPOSITION >( pNormalPosition );
		}

		if( PositionOffset != -1 )
		{
			glGenBuffers( 1, &m_WireframeVertexBufferObject );
			glGenBuffers( 1, &m_WireframeIndexBufferObject );
			glGenVertexArrays( 1, &m_WireframeVertexArrayObject );

			glBindVertexArray( m_WireframeVertexArrayObject );

			glBindBuffer( GL_ARRAY_BUFFER, m_WireframeVertexBufferObject );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,
				m_WireframeIndexBufferObject );

			glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET( 0 ) );

			glEnableVertexAttribArray( 0 );

			struct POSITION
			{
				KIL_FLOAT32 Position[ 3 ];
			};

			struct POSITION *pPosition = new POSITION[ m_VertexCount ];

			for( KIL_MEMSIZE Vertex = 0; Vertex < m_VertexCount; ++Vertex )
			{
				memcpy( pPosition[ Vertex ].Position,
					p_pVertices + ( Vertex * m_Stride ) + PositionOffset, 12 );
			}

			glBufferData( GL_ARRAY_BUFFER,
				m_VertexCount * sizeof( struct POSITION ), pPosition,
				GL_STATIC_DRAW );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER,
				sizeof( KIL_UINT16 ) * p_IndexCount, p_pIndices,
				GL_STATIC_DRAW );

			glBindVertexArray( 0 );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

			SafeDeleteArray< POSITION >( pPosition );
		}

		return KIL_OK;
	}

	void RendererPrimitive::Destroy( )
	{
		glDeleteBuffers( 1, &m_VertexBufferObject );
		glDeleteBuffers( 1, &m_IndexBufferObject );
		glDeleteVertexArrays( 1, &m_VertexArrayObject );

		glDeleteBuffers( 1, &m_NormalsVertexBufferObject );
		glDeleteBuffers( 1, &m_NormalsIndexBufferObject );
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

	KIL_UINT32 RendererPrimitive::Render( )
	{
		if( m_PolygonCount == 0 )
		{
			std::cout << "[Killer::RendererPrimitive::Render] <ERROR> "
				"No primitves to render" << std::endl;

			return KIL_FAIL;
		}

		glBindVertexArray( m_VertexArrayObject );

		GLenum Error = glGetError( );
		if( Error != GL_NO_ERROR )
		{
			std::cout << "ERROR: " << Error << std::endl;
		}

		glDrawElements( m_GLType, m_IndexCount, GL_UNSIGNED_SHORT,
			BUFFER_OFFSET( 0 ) );

		Error = glGetError( );
		if( Error != GL_NO_ERROR )
		{
			std::cout << "ERROR: " << Error << std::endl;
		}

		glBindVertexArray( 0 );

		return KIL_OK;
	}

	KIL_UINT32 RendererPrimitive::RenderNormals( )
	{
		glBindVertexArray( m_NormalsVertexArrayObject );

		GLenum Error = glGetError( );
		if( Error != GL_NO_ERROR )
		{
			std::cout << "ERROR: " << Error << std::endl;
		}

		glDrawElements( GL_LINES, m_VertexCount * 2, GL_UNSIGNED_SHORT,
			BUFFER_OFFSET( 0 ) );
		Error = glGetError( );
		if( Error != GL_NO_ERROR )
		{
			std::cout << "ERROR: " << Error << std::endl;
		}

		glBindVertexArray( 0 );

		return KIL_OK;
	}

	KIL_UINT32 RendererPrimitive::RenderWireframe( )
	{
		if( m_PolygonCount == 0 )
		{
			std::cout << "[Killer::RendererPrimitive::RenderWireframe] "
				"<ERROR> No primitives to render" << std::endl;

			return KIL_FAIL;
		}


		glBindVertexArray( m_WireframeVertexArrayObject );
		GLenum Error = glGetError( );
		if( Error != GL_NO_ERROR )
		{
			std::cout << "ERROR: " << Error << std::endl;
		}

		for( KIL_MEMSIZE Index = 0; Index < m_IndexCount; Index += 3 )
		{
			glDrawElements( GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT,
				BUFFER_OFFSET( Index * sizeof( GLushort ) ) );
		}

		glBindVertexArray( 0 );

		return KIL_OK;
	}
}


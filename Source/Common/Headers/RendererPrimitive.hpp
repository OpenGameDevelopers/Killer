#ifndef __KILLER_RENDERERPRIMITIVE_HPP__
#define __KILLER_RENDERERPRIMITIVE_HPP__

#include <DataTypes.hpp>
#include <VertexAttributes.hpp>
#include <GLES2/gl2.h>

namespace Killer
{
	typedef enum
	{
		PRIMITIVE_TYPE_UNKNOWN = 0,
		PRIMITIVE_TYPE_TRIANGLE_LIST,
		PRIMITIVE_TYPE_TRIANGLE_STRIP,
		PRIMITIVE_TYPE_TRIANGLE_FAN,
		PRIMITIVE_TYPE_LINE_LIST,
		PRIMITIVE_TYPE_LINE_STRIP,
		PRIMITIVE_TYPE_LINE_LOOP
	}PRIMITIVE_TYPE;

	class RendererPrimitive
	{
	public:
		RendererPrimitive( );
		~RendererPrimitive( );

		KIL_UINT32 Create( const KIL_BYTE *p_pVertices,
			const KIL_UINT16 *p_pIndices, const KIL_MEMSIZE p_VertexCount,
			const KIL_MEMSIZE p_IndexCount,
			const VertexAttributes &p_VertexAttributes,
			const PRIMITIVE_TYPE p_Type );

		void Destroy( );

		KIL_UINT32 SetPrimitiveType( const PRIMITIVE_TYPE p_Type );

		KIL_UINT32 Render( );

	private:
		RendererPrimitive( const RendererPrimitive &p_Other );
		RendererPrimitive &operator=( const RendererPrimitive &p_Other );

		PRIMITIVE_TYPE	m_Type;
		KIL_MEMSIZE		m_Stride;
		KIL_MEMSIZE		m_VertexCount;
		KIL_MEMSIZE		m_IndexCount;
		KIL_MEMSIZE		m_PolygonCount;
		KIL_UINT32		m_ID;
		GLenum			m_GLType;
		GLuint			m_VertexBufferObject;
		GLuint			m_IndexBufferObject;
		GLuint			m_VertexArrayObject;
	};
}

#endif // __KILLER_RENDERERPRIMITIVE_HPP__


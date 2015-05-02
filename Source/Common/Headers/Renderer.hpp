#ifndef __KILLER_RENDERER_HPP__
#define __KILLER_RENDERER_HPP__

#include <EGL/egl.h>
#include <DataTypes.hpp>

namespace Killer
{
	class GameWindow;

	class Renderer
	{
	public:
		Renderer( );
		~Renderer( );

		KIL_UINT32 Initialise( const GameWindow &p_GameWindow );
		KIL_UINT32 Clear( );
		void SwapBuffers( );

		void SetClearColour( const KIL_FLOAT32 p_Red,
			const KIL_FLOAT32 p_Green, const KIL_FLOAT32 p_Blue );

		KIL_MEMSIZE GetMaximumVertexAttributes( ) const;

	private:
		EGLDisplay	m_EGLDisplay;
		EGLSurface	m_EGLSurface;
		KIL_MEMSIZE	m_MaximumVertexAttributes;
	};
}


#endif // __KILLER_RENDERER_HPP__


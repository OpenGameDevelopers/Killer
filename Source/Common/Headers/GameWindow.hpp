#ifndef __KILLER_GAMEWINDOW_HPP__
#define __KILLER_GAMEWINDOW_HPP__

#include <EGL/egl.h>
#include <DataTypes.hpp>

namespace Killer
{
	class GameWindow
	{
	public:
		GameWindow( );
		~GameWindow( );

		KIL_UINT32 Create( );
		KIL_UINT32 Destroy( );
		KIL_UINT32 ProcessEvents( );

	private:
		EGLDisplay	m_EGLDisplay;
		EGLSurface	m_EGLSurface;
		EGLContext	m_EGLContext;
	};
}

#endif // __KILLER_GAMEWINDOW_HPP__


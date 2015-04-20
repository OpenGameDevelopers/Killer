#include <GameWindow.hpp>
#include <GLES2/gl2.h>
#include <iostream>

namespace Killer
{
	GameWindow::GameWindow( ) :
		m_EGLDisplay( EGL_NO_DISPLAY ),
		m_EGLSurface( EGL_NO_SURFACE ),
		m_EGLContext( EGL_NO_CONTEXT )
	{
	}

	GameWindow::~GameWindow( )
	{
		this->Destroy( );
	}

	KIL_UINT32 GameWindow::Create( )
	{
		m_EGLDisplay = eglGetDisplay( EGL_DEFAULT_DISPLAY );

		if( m_EGLDisplay == EGL_NO_DISPLAY )
		{
			std::cout << "[Killer::GameWindow::Create] <ERROR> "
				"No display available" << std::endl;

			return KIL_FAIL;
		}

		EGLint EGLMajor, EGLMinor;

		if( eglInitialize( m_EGLDisplay, &EGLMajor, &EGLMinor ) != EGL_TRUE )
		{
			std::cout << "[Killer::GameWindow::Create] <ERROR> "
				"Could not initialise EGL" << std::endl;

			return KIL_FAIL;
		}

		if( ( EGLMajor < 1 ) || ( ( EGLMajor == 1 ) && ( EGLMinor < 4 ) ) )
		{
			std::cout << "[Killer::GameWindow::Create] <ERROR> "
				"EGL version is not 1.4 or greater.  Current Version is: " <<
				EGLMajor << "." << EGLMinor << std::endl;

			return KIL_FAIL;
		}

		EGLConfig Config;
		EGLint ConfigCount;

		EGLint EGLAttributes[ ] =
		{
			EGL_RED_SIZE,			5,
			EGL_GREEN_SIZE,			6,
			EGL_BLUE_SIZE,			5,
			EGL_ALPHA_SIZE,			0,
			EGL_DEPTH_SIZE,			24,
			EGL_STENCIL_SIZE,		8,
			EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
			EGL_NONE
		};

		if( eglChooseConfig( m_EGLDisplay, EGLAttributes, &Config, 1,
			&ConfigCount ) != EGL_TRUE )
		{
			std::cout << "[Killer::GameWindow::Create] <ERROR> "
				"Unable to choose and EGL configuration" << std::endl;

			return KIL_FAIL;
		}
		
		m_EGLSurface = eglCreateWindowSurface( m_EGLDisplay, Config,
			nullptr, nullptr );

		if( m_EGLSurface == EGL_NO_SURFACE )
		{
			std::cout << "[Killer::GameWindow::Create] <ERROR> "
				"Failed when creating the EGL context" << std::endl;

			return KIL_FAIL;
		}

		GLint ContextAttribs[ ] =
		{
			EGL_CONTEXT_CLIENT_VERSION,	2,
			EGL_NONE
		};

		m_EGLContext = eglCreateContext( m_EGLDisplay, Config,
			EGL_NO_CONTEXT, ContextAttribs );

		if( m_EGLContext == EGL_NO_CONTEXT )
		{
			std::cout << "[Killer::GameWindow::Create] <ERROR> "
				"Failed when creating the EGL context" << std::endl;

			return KIL_FAIL;
		}

		if( eglMakeCurrent( m_EGLDisplay, m_EGLSurface, m_EGLSurface,
			m_EGLContext ) != EGL_TRUE )
		{
			std::cout << "[Killer::GameWindow::Create] <ERROR> "
				"Could not make the EGL context current" << std::endl;

			return KIL_FAIL;
		}

		return KIL_OK;
	}

	KIL_UINT32 GameWindow::Destroy( )
	{
		if( m_EGLContext != EGL_NO_CONTEXT )
		{
			eglDestroyContext( m_EGLDisplay, m_EGLContext );
			m_EGLContext = EGL_NO_CONTEXT;
		}

		if( m_EGLSurface != EGL_NO_SURFACE )
		{
			eglDestroySurface( m_EGLDisplay, m_EGLSurface );
			m_EGLSurface = EGL_NO_SURFACE;
		}

		if( m_EGLDisplay != EGL_NO_DISPLAY )
		{
			eglMakeCurrent( m_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,
				EGL_NO_CONTEXT );
			eglTerminate( m_EGLDisplay );
			m_EGLDisplay = EGL_NO_DISPLAY;
		}

		return KIL_OK;
	}

	KIL_UINT32 GameWindow::ProcessEvents( )
	{
		return KIL_OK;
	}

	EGLDisplay GameWindow::GetEGLDisplay( ) const
	{
		return m_EGLDisplay;
	}

	EGLSurface GameWindow::GetEGLSurface( ) const
	{
		return m_EGLSurface;
	}
}


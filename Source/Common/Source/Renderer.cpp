#include <Renderer.hpp>
#include <GameWindow.hpp>
#include <GLES2/gl2.h>
#include <GLESExtender.hpp>
#include <iostream>

namespace Killer
{
	Renderer::Renderer( ) :
		m_EGLDisplay( EGL_NO_DISPLAY ),
		m_EGLSurface( EGL_NO_SURFACE )
	{
	}

	Renderer::~Renderer( )
	{
	}

	KIL_UINT32 Renderer::Initialise( const GameWindow &p_GameWindow )
	{
		m_EGLDisplay = p_GameWindow.GetEGLDisplay( );
		m_EGLSurface = p_GameWindow.GetEGLSurface( );

		if( m_EGLDisplay == EGL_NO_DISPLAY )
		{
			std::cout << "[Killer::Renderer::Initialise] <ERROR> "
				"EGL Display from GameWindow is not valid" << std::endl;

			return KIL_FAIL;
		}

		if( m_EGLSurface == EGL_NO_SURFACE )
		{
			std::cout << "[Killer::Renderer::Iniitalise] <ERROR> "
				"EGL Surface from GameWindow is not vaild" << std::endl;

			return KIL_FAIL;
		}

		if( InitialiseGLES2Extensions( ) != KIL_OK )
		{
			std::cout << "[Killer::Renderer::Initialise] <ERROR> "
				"Failed to initialise OpenGL | ES 2.0 extensions" << std::endl;

			return KIL_FAIL;
		}

		std::cout << "[Killer::Renderer::Initialise] <INFO> GLES Vendor: " <<
			glGetString( GL_VENDOR ) << std::endl;
		std::cout << "[Killer::Renderer::Initialise] <INFO> GLES Renderer: " <<
			glGetString( GL_RENDERER ) << std::endl;
		std::cout << "[Killer::Renderer::Initialise] <INFO> GLES Version: " <<
			glGetString( GL_VERSION ) << std::endl;
		std::cout << "[Killer::Renderer::Initialise] <INFO> GLES GLSL "
			"Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) <<
			std::endl;

		std::cout << "[Killer::Renderer::Initialise] <INFO> Capabilities:" <<
			std::endl;

		GLint MaxVertexAttribs;
		GLint MaxUniformVectors;
		GLint MaxVaryingVectors;
		GLint MaxVertexTextureImageUnits;
		GLint MaxCombinedTextureImageUnits;
		GLint MaxTextureImageUnits;
		GLint MaxFragmentUniformVectors;

		glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttribs );
		glGetIntegerv( GL_MAX_VERTEX_UNIFORM_VECTORS, &MaxUniformVectors );
		glGetIntegerv( GL_MAX_VARYING_VECTORS, &MaxVaryingVectors );
		glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
			&MaxVertexTextureImageUnits );
		glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
			&MaxCombinedTextureImageUnits );
		glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &MaxTextureImageUnits );
		glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_VECTORS,
			&MaxFragmentUniformVectors );

		std::cout << "\tMaximum vertex shader attributes:      " <<
			MaxVertexAttribs << std::endl;
		std::cout << "\tMaximum vertex shader uniform vectors: " <<
			MaxUniformVectors << std::endl;
		std::cout << "\tMaximum varying vectors:               " <<
			MaxVaryingVectors << std::endl;
		std::cout << "\tMaximum vertex texture image units:    " <<
			MaxVertexTextureImageUnits << std::endl;
		std::cout << "\tMaximum combined texture image units:  " <<
			MaxCombinedTextureImageUnits << std::endl;
		std::cout << "\tMaximum texture image units:           " <<
			MaxTextureImageUnits <<std::endl;
		std::cout << "\tMaximum fragment uniform vectors:      " <<
			MaxFragmentUniformVectors << std::endl;

		return KIL_OK;
	}

	KIL_UINT32 Renderer::Clear( )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT );

		return KIL_OK;
	}

	void Renderer::SwapBuffers( )
	{
		eglSwapBuffers( m_EGLDisplay, m_EGLSurface );
	}

	void Renderer::SetClearColour( const KIL_FLOAT32 p_Red,
		const KIL_FLOAT32 p_Green, const KIL_FLOAT32 p_Blue )
	{
		KIL_FLOAT32 Red = p_Red, Green = p_Green, Blue = p_Blue;

		if( Red < 0.0f )
		{
			Red = 0.0f;
		}
		if( Red > 1.0f )
		{
			Red = 1.0f;
		}

		if( Green < 0.0f )
		{
			Green = 0.0f;
		}
		if( Green > 1.0f )
		{
			Green = 1.0f;
		}

		if( Blue < 0.0f )
		{
			Blue = 0.0f;
		}
		if( Blue > 1.0f )
		{
			Blue = 1.0f;
		}

		glClearColor( Red, Green, Blue, 1.0f );
	}
}


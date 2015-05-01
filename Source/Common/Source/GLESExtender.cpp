#include <GLESExtender.hpp>
#include <EGL/egl.h>
#include <iostream>

PFNGLGENVERTEXARRAYSOESPROC		__glGenVertexArrays = KIL_NULL;
PFNGLDELETEVERTEXARRAYSOESPROC	__glDeleteVertexArrays = KIL_NULL;
PFNGLBINDVERTEXARRAYOESPROC		__glBindVertexArray = KIL_NULL;

namespace Killer
{
	KIL_UINT32 InitialiseGLES2Extensions( )
	{
		// Only the necessary extensions are ever initialised, if this fails,
		// do not go further
		KIL_BOOL Initialised = KIL_FALSE;

		std::cout << "[Killer::InitialiseGLESExtensions] <INFO> "
			"Binding glGenVertexArraysOES ... ";

		Initialised |= ( ( __glGenVertexArrays =
			( PFNGLGENVERTEXARRAYSOESPROC )eglGetProcAddress(
				"glGenVertexArraysOES" ) ) == KIL_NULL );

		if( __glGenVertexArrays )
		{
			std::cout << "[FAIL]" << std::endl;
		}
		else
		{
			std::cout << "[ OK ]" << std::endl;
		}

		std::cout << "[Killer::InitialiseGLESExtensions] <INFO> "
			"Binding glDeleteVertexArraysOES ... ";

		Initialised |= ( ( __glDeleteVertexArrays =
			( PFNGLDELETEVERTEXARRAYSOESPROC )eglGetProcAddress(
				"glDeleteVertexArraysOES" ) ) == KIL_NULL );

		if( __glDeleteVertexArrays )
		{
			std::cout << "[FAIL]" << std::endl;
		}
		else
		{
			std::cout << "[ OK ]" << std::endl;
		}

		std::cout << "[Killer::InitialiseGLESExtensions] <INFO> "
			"Binding glBindVertexArrayOES ... ";

		Initialised |= ( ( __glBindVertexArray =
			( PFNGLBINDVERTEXARRAYOESPROC )eglGetProcAddress(
				"glBindVertexArrayOES" ) ) == KIL_NULL );

		if( __glBindVertexArray )
		{
			std::cout << "[FAIL]" << std::endl;
		}
		else
		{
			std::cout << "[ OK ]" << std::endl;
		}

		return Initialised ? KIL_FAIL : KIL_OK;
	}
}


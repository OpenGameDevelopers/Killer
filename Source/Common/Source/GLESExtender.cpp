#include <GLESExtender.hpp>
#include <EGL/egl.h>

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

		Initialised |= ( ( __glGenVertexArrays =
			( PFNGLGENVERTEXARRAYSOESPROC )eglGetProcAddress(
				"glGenVertexArraysOES" ) ) == KIL_NULL );

		Initialised |= ( ( __glDeleteVertexArrays =
			( PFNGLDELETEVERTEXARRAYSOESPROC )eglGetProcAddress(
				"glDeleteVertexArraysOES" ) ) == KIL_NULL );

		Initialised |= ( ( __glBindVertexArray =
			( PFNGLBINDVERTEXARRAYOESPROC )eglGetProcAddress(
				"glBindVertexArrayOES" ) ) == KIL_NULL );

		return Initialised ? KIL_FAIL : KIL_OK;
	}
}


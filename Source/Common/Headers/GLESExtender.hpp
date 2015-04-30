#ifndef __KILLER_GLESEXTENDER_HPP__
#define __KILLER_GLESEXTENDER_HPP__

#include <DataTypes.hpp>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern PFNGLGENVERTEXARRAYSOESPROC		__glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSOESPROC	__glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYOESPROC		__glBindVertexArray;

#define glGenVertexArrays		__glGenVertexArrays
#define glDeleteVertexArrays	__glDeleteVertexArrays
#define glBindVertexArray		__glBindVertexArray

#ifdef __cplusplus
}
#endif

namespace Killer
{
	KIL_UINT32 InitialiseGLES2Extensions( );
}

#endif // __KILLER_GLESEXTENDER_HPP__


#ifndef __KILLER_DATATYPES_HPP__
#define __KILLER_DATATYPES_HPP__

#include <stdint.h>

typedef signed char		KIL_SCHAR;
typedef unsigned char	KIL_UCHAR;
typedef int8_t			KIL_SCHAR;
typedef uint8_t			KIL_UINT8;
typedef int16_t			KIL_SINT16;
typedef uint16_t		KIL_UINT16;
typedef int32_t			KIL_SINT32;
typedef uint32_t		KIL_UINT32;

typedef KIL_UCHAR	KIL_BYTE;

const KIL_UINT32 KIL_OK		= 0X00000000;
const KIL_UINT32 KIL_FAIL	= 0x7FFFFFFF;

#endif // __KILLER_DATATYPES_HPP__


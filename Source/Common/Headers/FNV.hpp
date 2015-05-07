#ifndef __KILLER_FNV_HPP__
#define __KILLER_FNV_HPP__

#include <DataTypes.hpp>

namespace Killer
{
	const KIL_UINT32 FNV32_PRIME	= 0x01000193;
	const KIL_UINT32 FNV32_OFFSET	= 0x811C9DC5;

	KIL_UINT32 HashBufferFNV1a( void *p_pBuffer, const KIL_MEMSIZE p_Length,
		KIL_UINT32 p_PreviousHash = FNV32_OFFSET );
	KIL_UINT32 HashStringFNV1a( const char *p_pString,
		KIL_UINT32 p_PreviousHash = FNV32_OFFSET );
}

#endif // __KILLER_FNV_HPP__


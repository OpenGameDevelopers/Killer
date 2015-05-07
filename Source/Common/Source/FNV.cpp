#include <FNV.hpp>

namespace Killer
{
	KIL_UINT32 HashBufferFNV1a( void *p_pBuffer, const KIL_MEMSIZE p_Length,
		KIL_UINT32 p_PreviousHash )
	{
		KIL_BYTE *pStart = static_cast< KIL_BYTE * >( p_pBuffer );
		KIL_BYTE *pEnd = pStart + p_Length;

		while( pStart < pEnd )
		{
			p_PreviousHash ^= static_cast< KIL_UINT32 >( *pStart++ );
			p_PreviousHash *= FNV32_PRIME;
		}

		return p_PreviousHash;
	}

	KIL_UINT32 HashStringFNV1a( char *p_pString, KIL_UINT32 p_PreviousHash )
	{
		KIL_BYTE *pString = reinterpret_cast< KIL_BYTE * >( p_pString );

		while( *pString )
		{
			p_PreviousHash ^= static_cast< KIL_UINT32 >( *pString++ );
			p_PreviousHash *= FNV32_PRIME;
		}

		return p_PreviousHash;
	}
}


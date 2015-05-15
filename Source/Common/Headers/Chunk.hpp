#ifndef __KILLER_CHUNK_HPP__
#define __KILLER_CHUNK_HPP__

#include <DataTypes.hpp>
#include <cstdio>

namespace Killer
{
#pragma pack( 1 )
	struct CHUNK
	{
		KIL_UINT16	Type;
		KIL_UINT32	Size;
	};
#pragma pack( )

	const KIL_UINT16 CHUNK_END	= 0xFFFF;

	KIL_UINT32 ReadChunk( struct CHUNK &p_Chunk, FILE *p_pFile );
}

#endif // __KILLER_CHUNK_HPP__


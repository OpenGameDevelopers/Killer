#include <Chunk.hpp>
#include <iostream>

namespace Killer
{
	KIL_UINT32 ReadChunk( struct CHUNK &p_Chunk, FILE *p_pFile )
	{
		if( fread( &p_Chunk, sizeof( p_Chunk ), 1, p_pFile ) == 1 )
		{
			return KIL_OK;
		}

		std::cout << "[Killer::ReadChunk] <ERROR> Unexpected chunk size" <<
			std::endl;

		return KIL_FAIL;
	}
}


#ifndef __KILLER_TIME_HPP__
#define __KILLER_TIME_HPP__

#include <DataTypes.hpp>

namespace Killer
{
	typedef struct __tagBEAT_TIME
	{
		KIL_UINT32	Beat;
		KIL_UINT32	CentiBeat;
	}BEAT_TIME;

	KIL_UINT32 GetBeatTime( BEAT_TIME &p_BeatTime );
}

#endif // __KILLER_TIME_HPP__


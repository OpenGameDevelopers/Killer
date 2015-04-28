#include <Time.hpp>
#include <time.h>
#include <cmath>

namespace Killer
{
	KIL_UINT32 GetBeatTime( BEAT_TIME &p_BeatTime )
	{
		time_t Current;
		Current = time( KIL_NULL );

		struct tm *pTime;
		pTime = gmtime( &Current );

		KIL_FLOAT32 Hour = static_cast< KIL_FLOAT32 >( pTime->tm_hour );
		KIL_FLOAT32 Minute = static_cast< KIL_FLOAT32 >( pTime->tm_min );
		KIL_FLOAT32 Second = static_cast< KIL_FLOAT32 >( pTime->tm_sec );

		KIL_FLOAT32 BeatTime = ( Second + ( Minute * 60.0f ) +
			( ( Hour + 1.0f ) * 3600.0f ) ) / 86.4f;

		p_BeatTime.Beat = BeatTime;
		p_BeatTime.CentiBeat = fmod( BeatTime, 1.0f ) * 100.0f;

		return KIL_OK;
	}
}


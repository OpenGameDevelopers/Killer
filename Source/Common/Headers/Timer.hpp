#ifndef __KILLER_TIMER_HPP__
#define __KILLER_TIMER_HPP__

#include <DataTypes.hpp>
#include <time.h>

namespace Killer
{
	class Timer
	{
	public:
		Timer( );
		~Timer( );

		KIL_UINT64 Start( );
		KIL_UINT64 Stop( );

		KIL_UINT64 GetSeconds( );
		KIL_UINT64 GetMilliseconds( );
		KIL_UINT64 GetMicroseconds( );
		KIL_UINT64 GetNanoseconds( );

	private:
		KIL_BOOL		m_Stopped;
		KIL_UINT64		m_StartTime;
		KIL_UINT64		m_ElapsedTime;
		struct timespec	m_StartTimeSpec;
	};
}

#endif // __KILLER_TIMER_HPP__


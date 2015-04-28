#ifndef __KILLER_FREETIMER_HPP__
#define __KILLER_FREETIMER_HPP__

#include <DataTypes.hpp>
#include <pthread.h>

namespace Killer
{
	// The timer holds time in microseconds
	class FreeTimer
	{
	public:
		FreeTimer( );
		~FreeTimer( );

		KIL_UINT32 Start( );
		KIL_UINT32 Stop( );
		KIL_UINT32 Pause( );
		KIL_UINT32 Resume( );

		KIL_BOOL IsRunning( ) const;
		KIL_BOOL IsStopped( ) const;
		KIL_BOOL IsPaused( ) const;

		KIL_UINT64 GetSeconds( ) const;
		KIL_UINT64 GetMilliseconds( ) const;
		KIL_UINT64 GetMicroseconds( ) const;

	private:
		KIL_UINT64		m_StartTime;
		KIL_UINT64		m_ElapsedTime;
		KIL_BOOL		m_Running;
		KIL_BOOL		m_Stopped;
		KIL_BOOL		m_Paused;
		pthread_t		m_ThreadID;
		pthread_mutex_t	m_TimerLock;
		pthread_cond_t	m_TimerCond;

		static void *Run( void *p_pArg );
	};
}

#endif // __KILLER_FREETIMER_HPP__


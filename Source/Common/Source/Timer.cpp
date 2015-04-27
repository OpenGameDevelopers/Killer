#include <Timer.hpp>
#include <cstring>
#include <iostream>
#include <time.h>

namespace Killer
{
	Timer::Timer( )	:
		m_StartTime( 0ULL ),
		m_ElapsedTime( 0ULL ),
		m_Running( KIL_FALSE ),
		m_Stopped( KIL_FALSE ),
		m_Paused( KIL_FALSE ),
		m_TimerLock( PTHREAD_MUTEX_INITIALIZER ),
		m_TimerCond( PTHREAD_COND_INITIALIZER )
	{
	}

	Timer::~Timer( )
	{
	}

	KIL_UINT32 Timer::Start( )
	{
		pthread_mutex_lock( &m_TimerLock );
		struct timespec TimeSpec;

		clock_gettime( CLOCK_REALTIME, &TimeSpec );

		KIL_UINT64 Second, Microsecond;
		Second = TimeSpec.tv_sec * 1000000ULL;
		Microsecond = TimeSpec.tv_nsec / 1000ULL;

		m_StartTime = Second + Microsecond;

		m_ElapsedTime = 0ULL;

		int Error = pthread_create( &m_ThreadID, KIL_NULL, this->Run,
			this );
		
		if( Error != 0 )
		{
			std::cout << "[Killer::Timer::Start] <ERROR> "
				"Failed to create thread" << std::endl;
			return KIL_FAIL;
		}

		pthread_cond_wait( &m_TimerCond, &m_TimerLock );
		pthread_mutex_unlock( &m_TimerLock );

		m_Running = KIL_TRUE;

		return KIL_OK;
	}

	KIL_UINT32 Timer::Stop( )
	{
		pthread_cancel( m_ThreadID );
		pthread_join( m_ThreadID, KIL_NULL );

		m_Stopped = KIL_TRUE;

		return KIL_OK;
	}

	KIL_UINT32 Timer::Pause( )
	{
		pthread_cancel( m_ThreadID );
		pthread_join( m_ThreadID, KIL_NULL );

		m_Paused = KIL_TRUE;

		return KIL_OK;
	}

	KIL_UINT32 Timer::Resume( )
	{
		if( m_Paused )
		{
			pthread_mutex_lock( &m_TimerLock );
			struct timespec TimeSpec;

			clock_gettime( CLOCK_REALTIME, &TimeSpec );

			KIL_UINT64 Second, Microsecond;
			Second = TimeSpec.tv_sec * 1000000ULL;
			Microsecond = TimeSpec.tv_nsec / 1000ULL;

			m_StartTime = Second + Microsecond;

			int Error = pthread_create( &m_ThreadID, KIL_NULL, this->Run,
				this );
			
			if( Error != 0 )
			{
				std::cout << "[Killer::Timer::Pause] <ERROR> "
					"Failed to create thread" << std::endl;

				return KIL_FAIL;
			}

			pthread_cond_wait( &m_TimerCond, &m_TimerLock );
			pthread_mutex_unlock( &m_TimerLock );

			m_Paused = KIL_FALSE;
		}
		else
		{
			return this->Start( );
		}

		return KIL_OK;
	}

	KIL_BOOL Timer::IsRunning( ) const
	{
		return m_Running;
	}

	KIL_BOOL Timer::IsStopped( ) const
	{
		return m_Stopped;
	}

	KIL_BOOL Timer::IsPaused( ) const
	{
		return m_Paused;
	}

	KIL_UINT64 Timer::GetSeconds( ) const
	{
		return m_ElapsedTime / 1000000ULL;
	}

	KIL_UINT64 Timer::GetMilliseconds( ) const
	{
		return m_ElapsedTime / 1000ULL;
	}

	KIL_UINT64 Timer::GetMicroseconds( ) const
	{
		return m_ElapsedTime;
	}

	void *Timer::Run( void *p_pArg )
	{
		Timer *pThisInst = static_cast< Timer * >( p_pArg );

		struct timespec TimeSpec;

		pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, KIL_NULL );

		pthread_mutex_lock( &pThisInst->m_TimerLock );
		pthread_cond_signal( &pThisInst->m_TimerCond );
		pthread_mutex_unlock( &pThisInst->m_TimerLock );

		KIL_UINT64 PreviousTime = 0ULL;
		KIL_UINT64 DeltaTime = 0ULL;

		clock_gettime( CLOCK_REALTIME, &TimeSpec );
		KIL_UINT64 Second = TimeSpec.tv_sec * 1000000ULL;
		KIL_UINT64 Microsecond = TimeSpec.tv_nsec / 1000ULL;
		PreviousTime = Second + Microsecond;

		while( 1 )
		{
			clock_gettime( CLOCK_REALTIME, &TimeSpec );
			Second = TimeSpec.tv_sec * 1000000ULL;
			Microsecond = TimeSpec.tv_nsec / 1000ULL;

			DeltaTime = ( Second + Microsecond ) - PreviousTime;

			PreviousTime = Second + Microsecond;

			pThisInst->m_ElapsedTime += DeltaTime;
		}

		return KIL_NULL;
	}
}


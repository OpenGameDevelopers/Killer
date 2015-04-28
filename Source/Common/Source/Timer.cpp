#include <Timer.hpp>
#include <iostream>
#include <cstring>

namespace Killer
{
	struct timespec TimeDifference( struct timespec &p_Start,
		struct timespec &p_End )
	{
		struct timespec Difference;

		if( ( p_End.tv_nsec - p_Start.tv_nsec ) < 0 )
		{
			Difference.tv_sec = p_End.tv_sec - p_Start.tv_sec - 1;
			Difference.tv_nsec = 1000000000ULL + p_End.tv_nsec -
				p_Start.tv_nsec;
		}
		else
		{
			Difference.tv_sec = p_End.tv_sec - p_Start.tv_sec;
			Difference.tv_nsec = p_End.tv_nsec - p_Start.tv_nsec;
		}

		return Difference;
	}

	Timer::Timer( ) :
		m_Stopped( KIL_TRUE ),
		m_StartTime( 0ULL ),
		m_ElapsedTime( 0ULL )
	{
		memset( &m_StartTimeSpec, 0, sizeof( m_StartTimeSpec ) );
	}

	Timer::~Timer( )
	{
	}

	KIL_UINT64 Timer::Start( )
	{
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &m_StartTimeSpec );

		KIL_UINT64 Second = m_StartTimeSpec.tv_sec * 1000000000ULL;
		KIL_UINT64 Nanosecond = m_StartTimeSpec.tv_nsec;

		m_StartTime = Second + Nanosecond;

		m_Stopped = KIL_FALSE;

		return KIL_OK;
	}

	KIL_UINT64 Timer::Stop( )
	{
		if( m_StartTime == 0ULL )
		{
			return KIL_FAIL;	
		}

		struct timespec TimeSpec;
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &TimeSpec );

		struct timespec Difference = TimeDifference( m_StartTimeSpec,
			TimeSpec );

		KIL_UINT64 Second = Difference.tv_sec * 1000000000ULL;
		KIL_UINT64 Nanosecond = Difference.tv_nsec;

		m_ElapsedTime = ( Second + Nanosecond );

		m_Stopped = KIL_TRUE;

		return KIL_OK;
	}

	KIL_UINT64 Timer::GetSeconds( )
	{
		if( m_Stopped )
		{
			return m_ElapsedTime / 1000000000ULL;
		}

		struct timespec TimeSpec;
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &TimeSpec );

		struct timespec Difference = TimeDifference( m_StartTimeSpec,
			TimeSpec );

		KIL_UINT64 Second = Difference.tv_sec * 1000000000ULL;
		KIL_UINT64 Nanosecond = Difference.tv_nsec;

		m_ElapsedTime = ( Second + Nanosecond );

		return m_ElapsedTime / 1000000000ULL;
	}

	KIL_UINT64 Timer::GetMilliseconds( )
	{
		if( m_Stopped )
		{
			return m_ElapsedTime / 1000000ULL;
		}

		struct timespec TimeSpec;
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &TimeSpec );

		struct timespec Difference = TimeDifference( m_StartTimeSpec,
			TimeSpec );

		KIL_UINT64 Second = Difference.tv_sec * 1000000000ULL;
		KIL_UINT64 Nanosecond = Difference.tv_nsec;

		m_ElapsedTime = ( Second + Nanosecond );

		return m_ElapsedTime / 1000000ULL;
	}

	KIL_UINT64 Timer::GetMicroseconds( )
	{
		if( m_Stopped )
		{
			return m_ElapsedTime / 1000ULL;
		}

		struct timespec TimeSpec;
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &TimeSpec );

		struct timespec Difference = TimeDifference( m_StartTimeSpec,
			TimeSpec );

		KIL_UINT64 Second = Difference.tv_sec * 1000000000ULL;
		KIL_UINT64 Nanosecond = Difference.tv_nsec;

		m_ElapsedTime = ( Second + Nanosecond );

		return m_ElapsedTime / 1000ULL;
	}

	KIL_UINT64 Timer::GetNanoseconds( )
	{
		if( m_Stopped )
		{
			return m_ElapsedTime;
		}

		struct timespec TimeSpec;
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &TimeSpec );

		struct timespec Difference = TimeDifference( m_StartTimeSpec,
			TimeSpec );

		KIL_UINT64 Second = Difference.tv_sec * 1000000000ULL;
		KIL_UINT64 Nanosecond = Difference.tv_nsec;

		m_ElapsedTime = ( Second + Nanosecond );

		return m_ElapsedTime;
	}
}


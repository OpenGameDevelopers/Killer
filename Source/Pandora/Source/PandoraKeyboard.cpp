#include <Keyboard.hpp>
#include <iostream>
#include <cstring>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

namespace Killer
{
    static KIL_UINT32 s_ScanToKey[ 512 ] =
    {
		// 0
	    0, KIL_KEY_ESCAPE, KIL_KEY_1, KIL_KEY_2, KIL_KEY_3, KIL_KEY_4,
			KIL_KEY_5, KIL_KEY_6,
		// 8
	    KIL_KEY_7, KIL_KEY_8, KIL_KEY_9, KIL_KEY_0, 0, 0, 0, 0,
		// 16
		KIL_KEY_Q, KIL_KEY_W, KIL_KEY_E, KIL_KEY_R, KIL_KEY_T, KIL_KEY_Y,
			KIL_KEY_U, KIL_KEY_I,
		// 24
	    KIL_KEY_O, KIL_KEY_P, 0, 0, KIL_KEY_ENTER, 0, KIL_KEY_A,
			KIL_KEY_S,
		// 32
	    KIL_KEY_D, KIL_KEY_F, KIL_KEY_G, KIL_KEY_H, KIL_KEY_J, KIL_KEY_K,
			KIL_KEY_L, 0,
		// 40
	    0, 0, 0, 0, KIL_KEY_Z, KIL_KEY_X, KIL_KEY_C, KIL_KEY_V,
		// 48
		KIL_KEY_B, KIL_KEY_N, KIL_KEY_M, 0, 0, 0, 0, 0,
		// 56
	    0, KIL_KEY_SPACE, 0, KIL_KEY_F1, KIL_KEY_F2, KIL_KEY_F3,
			KIL_KEY_F4, KIL_KEY_F5,
		// 64
		KIL_KEY_F6, KIL_KEY_F7, KIL_KEY_F8, KIL_KEY_F9, KIL_KEY_F10, 0, 0,
			0,
		// 72
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 80
	    0, 0, 0, 0, 0, 0, 0, KIL_KEY_F11,
		// 88
		KIL_KEY_F12, 0, 0, 0, 0, 0, 0, 0,
		// 96
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 104
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 112
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 118
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 128
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 256
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 384
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 392
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 400
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 408
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 416
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 424
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 432
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 440
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 448
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 456
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 464
	    KIL_KEY_FN, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 512
    };

	KIL_UINT32 Keyboard::Initialise( )
	{
		this->Terminate( );

		for( int Index = 0; ; ++Index )
		{
			char DeviceName[ 64 ];
			char PrintName[ 256 ];
			int FD;

			snprintf( DeviceName, sizeof( DeviceName ), "/dev/input/event%i",
				Index );

			FD = open( DeviceName, O_RDONLY );

			if( FD == -1 )
			{
				break;
			}

			ioctl( FD, EVIOCGNAME( sizeof( PrintName ) ), PrintName );

			if( strcmp( PrintName, "keypad" ) == 0 )
			{
				m_KeypadFD = FD;
				break;
			}
		}

		if( m_KeypadFD == -1 )
		{
			std::cout << "[Killer::Keyboard::Initialise] <ERROR> "
				"Keypad file descriptor invalid" << std::endl;

			return KIL_FAIL;
		}

		return KIL_OK;
	}

	void Keyboard::Terminate( )
	{
		if( m_KeypadFD != -1 )
		{
			close( m_KeypadFD );
			m_KeypadFD = -1;
		}
	}

	KIL_UINT32 Keyboard::GetState( void *p_pState )
	{
		if( p_pState == KIL_NULL )
		{
			std::cout << "[Killer::Keyboard::GetState] <ERRRO> "
				"State parameter was null" << std::endl;

			return KIL_FAIL;
		}

		// This may be overkill
		struct input_event Event[ 64 ];

		int FD = -1, Read, Return;

		fd_set ReadFDS;
		
		FD_ZERO( &ReadFDS );

		FD_SET( m_KeypadFD, &ReadFDS );

		struct timeval TimeOut = { 0, 0 };

		Return = select( m_KeypadFD + 1, &ReadFDS, KIL_NULL, KIL_NULL,
			&TimeOut );
		
		if( Return == -1 )
		{
			std::cout << "[Killer::Keyboard::GetState] <ERROR> "
				"Failed to call select" << std::cout;

			return KIL_FAIL;
		}

		if( FD_ISSET( m_KeypadFD, &ReadFDS ) )
		{
			FD = m_KeypadFD;
		}

		Read = read( FD, Event, sizeof( Event ) );

		if( Read < ( int )( sizeof( Event[ 0 ] ) ) )
		{
			// No data, return
			memcpy( p_pState, &m_KeyState, sizeof( m_KeyState ) );

			return KIL_OK;
		}

		for( size_t i = 0; i < Read / sizeof( Event[ 0 ] ); ++i )
		{
			switch( Event[ i ].type )
			{
				case EV_KEY:
				{
					if( Event[ i ].value )
					{
						m_KeyState.Keys[ s_ScanToKey[ Event[ i ].code ] ] = 1;
					}
					else
					{
						m_KeyState.Keys[ s_ScanToKey[ Event[ i ].code ] ] = 0;
					}
				}
				default:
				{
					break;
				}
			}
		}

		memcpy( p_pState, &m_KeyState, sizeof( m_KeyState ) );

		return KIL_OK;
	}
}


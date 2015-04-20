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
	    0, KEY_ESCAPE, KEY_1, KEY_2, KEY_3, KEY_4,
			KEY_5, KEY_6,
		// 8
	    KEY_7, KEY_8, KEY_9, KEY_0, 0, 0, 0, 0,
		// 16
		KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y,
			KEY_U, KEY_I,
		// 24
	    KEY_O, KEY_P, 0, 0, KEY_ENTER, 0, KEY_A,
			KEY_S,
		// 32
	    KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K,
			KEY_L, 0,
		// 40
	    0, 0, 0, 0, KEY_Z, KEY_X, KEY_C, KEY_V,
		// 48
		KEY_B, KEY_N, KEY_M, 0, 0, 0, 0, 0,
		// 56
	    0, KEY_SPACE, 0, KEY_F1, KEY_F2, KEY_F3,
			KEY_F4, KEY_F5,
		// 64
		KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0,
			0,
		// 72
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 80
	    0, 0, 0, 0, 0, 0, 0, KEY_F11,
		// 88
		KEY_F12, 0, 0, 0, 0, 0, 0, 0,
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
	    KEY_FN, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0,
		// 512
    };

	Keyboard::Keyboard( )
	{
		memset( &m_KeyState, 0, sizeof( m_KeyState ) );
	}

	Keyboard::~Keyboard( )
	{
		this->Terminate( );
	}

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

			return KIL_FAIL;
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

	INPUT_DEVICE_TYPE Keyboard::GetType( ) const
	{
		return INPUT_DEVICE_TYPE_KEYBOARD;
	}

	void Keyboard::KeyUp( const KIL_UINT32 p_Key )
	{
		m_KeyState.Keys[ p_Key ] = 0;
	}

	void Keyboard::KeyDown( const KIL_UINT32 p_Key )
	{
		m_KeyState.Keys[ p_Key ] = 1;
	}

	KIL_BOOL Keyboard::IsKeyUp( const KIL_UINT32 p_Key ) const
	{
		return ( m_KeyState.Keys[ p_Key ] != 1 );
	}

	KIL_BOOL Keyboard::IsKeyDown( const KIL_UINT32 p_Key ) const
	{
		return ( m_KeyState.Keys[ p_Key ] != 0 );
	}
}


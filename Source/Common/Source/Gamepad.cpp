#include <Gamepad.hpp>
#include <sys/time.h>
#include <stddef.h>

namespace Killer
{
	Gamepad::Gamepad( ) :
		m_ButtonsFD( -1 ),
		m_LeftStickFD( -1 ),
		m_RightStickFD( -1 ),
		m_MaxFD( 0 )
	{
		m_GamepadState.Buttons = 0;

		for( size_t i = 0; i < 2; ++i )
		{
			m_GamepadState.AnalogueStick[ i ].X = 0.0f;
			m_GamepadState.AnalogueStick[ i ].Y = 0.0f;
		}
	}

	Gamepad::~Gamepad( )
	{
		this->Terminate( );
	}

	INPUT_DEVICE_TYPE Gamepad::GetType( ) const
	{
		return INPUT_DEVICE_TYPE_GAMEPAD;
	}

	
}


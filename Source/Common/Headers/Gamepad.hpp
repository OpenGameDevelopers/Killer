#ifndef __KILLER_GAMEPAD_HPP__
#define __KILLER_GAMEPAD_HPP__

#include <InputDevice.hpp>
#include <DataTypes.hpp>

namespace Killer
{
	class Gamepad : public InputDevice
	{
	public:
		Gamepad( );
		virtual ~Gamepad( );

		virtual KIL_UINT32 Initialise( );
		virtual void Terminate( );

		virtual INPUT_DEVICE_TYPE GetType( ) const;

		virtual KIL_UINT32 GetState( void *p_pState );

	private:
		GAMEPAD_STATE	m_GamepadState;
		int				m_ButtonsFD;
		int				m_LeftStickFD;
		int				m_RightStickFD;
		int				m_MaxFD;
	};
}

#endif // __KILLER_GAMEPAD_HPP__


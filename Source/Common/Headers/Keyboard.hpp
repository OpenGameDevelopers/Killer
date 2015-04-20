#ifndef __KILLER_KEYBOARD_HPP__
#define __KILLER_KEYBOARD_HPP__

#include <DataTypes.hpp>
#include <InputDevice.hpp>

namespace Killer
{
	class Keyboard : public InputDevice
	{
	public:
		Keyboard( );
		virtual ~Keyboard( );

		virtual KIL_UINT32 Initialise( );
		virtual void Terminate( );

		virtual INPUT_DEVICE_TYPE GetType( ) const;

		virtual KIL_UINT32 GetState( void *p_pState );

		void KeyUp( const KIL_UINT32 p_Key );
		void KeyDown( const KIL_UINT32 p_Key );

		KIL_BOOL IsKeyUp( const KIL_UINT32 p_Key ) const;
		KIL_BOOL IsKeyDown( const KIL_UINT32 p_Key ) const;

	private:
		int			m_KeypadFD;
		KEYSTATE	m_KeyState;
	};
}

#endif // __KILLER_KEYBOARD_HPP__


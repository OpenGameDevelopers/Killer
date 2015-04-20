#ifndef __KILLER_INPUTDEVICE_HPP__
#define __KILLER_INPUTDEVICE_HPP__

#include <DataTypes.hpp>

namespace Killer
{
	typedef enum __tagINPUT_DEVICE_TYPE
	{
		INPUT_DEVICE_TYPE_KEYBOARD,
		INPUT_DEVICE_TYPE_GAMEPAD,
		INPUT_DEVICE_TYPE_UNKNOWN
	}INPUT_DEVICE_TYPE;

	typedef enum __tagKEY
	{
		KEY_TAB	= 9,
		KEY_ENTER	= 13,
		KEY_ESCAPE	= 27,
		KEY_SPACE	= 32,

		KEY_A	= 40,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		KEY_1	= 100,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_0,

		KEY_F1	= 149,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,

		KEY_FN = 200,
	}KEY;

	typedef struct _tagKEYSTATE
	{
		char		Keys[ 256 ];
		KIL_UINT32	Modifiers;
	}KEYSTATE;

	class InputDevice
	{
	public:
		virtual ~InputDevice( );

		virtual KIL_UINT32 Initialise( ) = 0;
		virtual void Terminate( ) = 0;

		virtual INPUT_DEVICE_TYPE GetType( ) const = 0;

		virtual KIL_UINT32 GetState( void *p_pState ) = 0;
	};
}

#endif // __KILLER_INPUTDEVICE_HPP__


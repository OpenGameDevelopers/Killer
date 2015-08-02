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

	typedef struct __tagAXIS_2D
	{
		KIL_FLOAT32	X;
		KIL_FLOAT32	Y;
	}AXIS_2D;

	const KIL_UINT32 GAMEPAD_BUTTON_DPAD_UP		= 0x00000001;
	const KIL_UINT32 GAMEPAD_BUTTON_DPAD_DOWN	= 0x00000002;
	const KIL_UINT32 GAMEPAD_BUTTON_DPAD_LEFT	= 0x00000004;
	const KIL_UINT32 GAMEPAD_BUTTON_DPAD_RIGHT	= 0x00000008;
	const KIL_UINT32 GAMEPAD_BUTTON_Y			= 0x00000010;
	const KIL_UINT32 GAMEPAD_BUTTON_X			= 0x00000020;
	const KIL_UINT32 GAMEPAD_BUTTON_A			= 0x00000040;
	const KIL_UINT32 GAMEPAD_BUTTON_B			= 0x00000080;
	const KIL_UINT32 GAMEPAD_BUTTON_START		= 0x00000100;
	const KIL_UINT32 GAMEPAD_BUTTON_SELECT		= 0x00000200;
	const KIL_UINT32 GAMEPAD_BUTTON_MENU		= 0x00000400;
	const KIL_UINT32 GAMEPAD_BUTTON_L			= 0x00001000;
	const KIL_UINT32 GAMEPAD_BUTTON_R			= 0x00002000;

	typedef struct __tagGAMEPAD_STATE
	{
		KIL_UINT32	Buttons;
		AXIS_2D		AnalogueStick[ 2 ];
	}GAMEPAD_STATE;

	typedef enum __tagKEY
	{
		KIL_KEY_TAB	= 9,
		KIL_KEY_ENTER	= 13,
		KIL_KEY_ESCAPE	= 27,
		KIL_KEY_SPACE	= 32,

		KIL_KEY_A	= 40,
		KIL_KEY_B,
		KIL_KEY_C,
		KIL_KEY_D,
		KIL_KEY_E,
		KIL_KEY_F,
		KIL_KEY_G,
		KIL_KEY_H,
		KIL_KEY_I,
		KIL_KEY_J,
		KIL_KEY_K,
		KIL_KEY_L,
		KIL_KEY_M,
		KIL_KEY_N,
		KIL_KEY_O,
		KIL_KEY_P,
		KIL_KEY_Q,
		KIL_KEY_R,
		KIL_KEY_S,
		KIL_KEY_T,
		KIL_KEY_U,
		KIL_KEY_V,
		KIL_KEY_W,
		KIL_KEY_X,
		KIL_KEY_Y,
		KIL_KEY_Z,

		KIL_KEY_1	= 100,
		KIL_KEY_2,
		KIL_KEY_3,
		KIL_KEY_4,
		KIL_KEY_5,
		KIL_KEY_6,
		KIL_KEY_7,
		KIL_KEY_8,
		KIL_KEY_9,
		KIL_KEY_0,

		KIL_KEY_F1	= 149,
		KIL_KEY_F2,
		KIL_KEY_F3,
		KIL_KEY_F4,
		KIL_KEY_F5,
		KIL_KEY_F6,
		KIL_KEY_F7,
		KIL_KEY_F8,
		KIL_KEY_F9,
		KIL_KEY_F10,
		KIL_KEY_F11,
		KIL_KEY_F12,

		KIL_KEY_FN = 200,
	}KEY;

	typedef struct _tagKIL_KEY_STATE
	{
		char		Keys[ 256 ];
		KIL_UINT32	Modifiers;
	}KIL_KEY_STATE;

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

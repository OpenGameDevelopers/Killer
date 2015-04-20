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

	typedef struct _tagKEY_STATE
	{
		char		Keys[ 256 ];
		KIL_UINT32	Modifiers;
	}KEY_STATE;

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


#include <Keyboard.hpp>
#include <cstring>

namespace Killer
{
	Keyboard::Keyboard( ) :
		m_KeypadFD( -1 )
	{
		memset( &m_KeyState, 0, sizeof( m_KeyState ) );
	}

	Keyboard::~Keyboard( )
	{
		this->Terminate( );
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


#ifndef __KILLER_GAME_HPP__
#define __KILLER_GAME_HPP__

#include <DataTypes.hpp>
#include <GameWindow.hpp>
#include <Renderer.hpp>
#include <Keyboard.hpp>
#include <Gamepad.hpp>

namespace Killer
{
	class Game
	{
	public:
		Game( );
		~Game( );

		KIL_UINT32 Initialise( );
		KIL_UINT32 Execute( );

	private:
		GameWindow	m_Window;
		Renderer	m_Renderer;
		Keyboard	m_Keyboard;
		Gamepad		m_Gamepad;
	};
}

#endif // __KILLER_GAME_HPP__


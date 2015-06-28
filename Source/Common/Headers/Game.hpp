#ifndef ___GAME_HPP__
#define ___GAME_HPP__

#include <System/DataTypes.hpp>
#include <System/Window.hpp>
#include <System/WindowData.hpp>
#include <System/Keyboard.hpp>
#include <System/InputManager.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/CanvasDescription.hpp>
#include <Configuration.hpp>

namespace Killer
{
	class Game
	{
	public:
		Game( );
		~Game( );

		ZED_UINT32 Initialise( );
		ZED_UINT32 Execute( );

	private:
		ZED_UINT32 PreInitialise( );

		ZED::System::Window					*m_pWindow;
		ZED::System::WindowData				*m_pWindowData;
		ZED::System::InputManager			*m_pInputManager;
		ZED::System::Keyboard				m_Keyboard;
		ZED::Renderer::Renderer				*m_pRenderer;
		ZED::Renderer::CanvasDescription	m_Canvas;
		Configuration						m_GameConfiguration;

		ZED_BOOL	m_Running;
	};
}

#endif


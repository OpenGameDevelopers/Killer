#include <Game.hpp>
#include <System/LinuxWindow.hpp>
#include <System/LinuxWindowData.hpp>
#include <System/LinuxInputManager.hpp>
#include <Renderer/RendererFactory.hpp>

namespace Killer
{
	ZED_UINT32 Game::PreInitialise( )
	{
		m_pWindow = new ZED::System::LinuxWindow( );

		if( !m_pWindow )
		{
			zedTrace( "[Killer::Game::PreInitialise] <ERROR> "
				"Failed to create a new window\n" );
				
			return ZED_FAIL;
		}

		m_pWindowData = new ZED::System::LinuxWindowData( );


		if( ZED::Renderer::CreateRenderer( "OpenGL", &m_pRenderer ) != ZED_OK )
		{
			zedTrace( "[Killer::Game::PreInitialise] <ERROR> "
				"Failed to create renderer\n" );

			return ZED_FAIL;
		}

		//m_pRenderer = new ZED::Renderer::LinuxRendererOGL3( );

		if( !m_pRenderer )
		{
			zedTrace( "[Killer::Game::PreInitialise] <ERROR> "
				"Failed to create a new renderer\n" );

			return ZED_FAIL;
		}

		m_pInputManager = new ZED::System::LinuxInputManager( );

		if( !m_pInputManager )
		{
			zedTrace( "[Killer::Game::PreInitialise] <ERROR> "
				"Failed to create new input manager\n" );

			return ZED_FAIL;
		}

		return ZED_OK;
	}
}


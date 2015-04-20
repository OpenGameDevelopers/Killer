#include <Game.hpp>
#include <iostream>

namespace Killer
{
	Game::Game( )
	{
	}

	Game::~Game( )
	{
	}

	KIL_UINT32 Game::Initialise( )
	{
		if( m_Window.Create( ) != KIL_OK )
		{
			std::cout << "[Killer::Game::Initialise] <ERROR> "
				"Failed to initialise the game window" << std::endl;

			return KIL_FAIL;
		}

		if( m_Renderer.Initialise( m_Window ) != KIL_OK )
		{
			std::cout << "[Killer::Game::Initialise] <ERROR> "
				"Failed to initialise the renderer" << std::endl;

			return KIL_FAIL;
		}

		if( m_Keyboard.Initialise( ) != KIL_OK )
		{
			std::cout << "[Killer::Game::Initialise] <ERROR> "
				"Failed to initialise the keyboard" << std::endl;

			return KIL_FAIL;
		}

		m_Renderer.SetClearColour( 1.0f, 153 / 255.0f, 51.0f / 255.0f );
		
		return KIL_OK;
	}

	KIL_UINT32 Game::Execute( )
	{
		KEYSTATE OldKeyState;

		KIL_BOOL Quit = 0;

		while( !Quit )
		{
			m_Window.ProcessEvents( );
			KEYSTATE CurrentKeyState;

			m_Keyboard.GetState( &CurrentKeyState );

			if( CurrentKeyState.Keys[ KEY_ESCAPE ] )
			{
				Quit = KIL_TRUE;
			}
			
			m_Renderer.Clear( );
			m_Renderer.SwapBuffers( );
		}

		return KIL_OK;
	}
}


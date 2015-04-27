#include <Game.hpp>
#include <iostream>
#include <Vector3.hpp>
#include <Timer.hpp>
#include <unistd.h>
#include <locale>

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

		if( m_Gamepad.Initialise( ) != KIL_OK )
		{
			std::cout << "[Killer::Game::Initialise] <ERROR> "
				"Failed to initialise the gamepad" << std::endl;
		}

		m_Renderer.SetClearColour( 1.0f, 153 / 255.0f, 51.0f / 255.0f );
		
		return KIL_OK;
	}

	KIL_UINT32 Game::Execute( )
	{
		Timer MathTimer;
		std::cout << "Vector3 test" << std::endl;
		Vector3 V1, V2, V3;
		V1 = Vector3( 1.0f, 0.0f, 0.0f );
		V2 = Vector3( 0.0f, 1.0f, 0.0f );

		std::cout << "V1: ";
		V1.Print( );
		std::cout << std::endl << "V2: ";
		V2.Print( );
		std::cout << std::endl << "V3: ";
		V3.Print( );
		std::cout << std::endl;

		V3 = V1;

		MathTimer.Start( );
		V3 = V1.Cross( V2 );
		MathTimer.Stop( );
		std::cout << "Crossing V1 and V2" << std::endl << "Result: ";
		V3.Print( );
		std::cout << " Took: " << MathTimer.GetMicroseconds( ) << "us" <<
			std::endl;

		MathTimer.Start( );
		KIL_FLOAT32 Dot = V1.Dot( V2 );
		MathTimer.Stop( );

		std::cout << "Dot of V1.V2: " << Dot << " Took: " <<
			MathTimer.GetMicroseconds( ) << "us" << std::endl;

		V1 = Vector3( 10.0f, 12.0f, 70.0f );
		std::cout << "Normalising V1: ";
		V1.Print( );
		std::cout << std::endl << "Result: ";
		V1.Normalise( );
		V1.Print( );
		std::cout << std::endl;

		std::cout << "V1 Magnitude: " << V1.Magnitude( ) << std::endl;
		std::cout << "V1 Magnitude Squared: " << V1.MagnitudeSq( ) <<
			std::endl;

		V1 = Vector3( 10.0f, 0.0f, 0.0f );
		V2 = Vector3( 0.0f, 0.0f, 30.0f );

		std::cout << "Distance between V1 and V2" << std::endl;
		std::cout << "V1: ";
		V1.Print( );
		std::cout << std::endl << "V2: ";
		V2.Print( );
		KIL_FLOAT32 Distance = V1.Distance( V2 );
		std::cout << std::endl << "Distance: " << Distance << std::endl;

		Timer GameTimer;

		KIL_BOOL Quit = 0;

		GameTimer.Start( );

		while( !Quit )
		{
			m_Window.ProcessEvents( );
			KEY_STATE CurrentKeyState;
			GAMEPAD_STATE CurrentGamepadState;

			m_Keyboard.GetState( &CurrentKeyState );
			m_Gamepad.GetState( &CurrentGamepadState );

			if( CurrentKeyState.Keys[ KEY_ESCAPE ] )
			{
				Quit = KIL_TRUE;
			}

			if( CurrentGamepadState.Buttons & GAMEPAD_BUTTON_START )
			{
				Quit = KIL_TRUE;
			}
			
			m_Renderer.Clear( );
			m_Renderer.SwapBuffers( );
		}

		GameTimer.Stop( );

		// Use LC_ALL=<LANG> to get correct format
		// LC_ALL=en_GB - British English
		// LC_ALL=de_DE - German
		// LC_ALL=ja_JP - Japanese
		std::locale::global( std::locale( "" ) );
		std::cout.imbue( std::locale( ) );
		std::cout << "Total running time: " << GameTimer.GetMicroseconds( ) <<
			"\u00B5s" << std::endl;

		return KIL_OK;
	}
}


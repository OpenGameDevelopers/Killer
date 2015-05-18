#include <Game.hpp>
#include <iostream>
#include <iomanip>
#include <Vector3.hpp>
#include <FreeTimer.hpp>
#include <Timer.hpp>
#include <Time.hpp>
#include <unistd.h>
#include <locale>
#include <RendererPrimitive.hpp>
#include <VertexAttributes.hpp>
#include <Camera.hpp>
#include <cstring>
#include <Arithmetic.hpp>
#include <MaterialManager.hpp>
#include <Model.hpp>

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

#pragma pack( 1 )
	struct VERTEX
	{
		KIL_FLOAT32 X, Y, Z;
		KIL_FLOAT32 R, G, B;
		KIL_FLOAT32 S, T;
		KIL_FLOAT32 nX, nY, nZ;
	};
#pragma pack( )

	KIL_UINT32 Game::Execute( )
	{
		std::locale::global( std::locale( "" ) );
		std::cout.imbue( std::locale( ) );

		FreeTimer GameTimer;

		KIL_BOOL Quit = 0;

		GameTimer.Start( );

		Timer Clock;

		Clock.Start( );

		MaterialManager MatMan;

		KIL_UINT32 TextureMaterial;
		if( MatMan.CreateMaterial( "Test/Materials/Test.material",
			TextureMaterial ) != KIL_OK )
		{
			std::cout << "[Killer::Game::Execute] <ERROR> "
				"Failed to create texture material" << std::endl;

			return KIL_FAIL;
		}

		KIL_UINT32 PositionSolidColourMaterial;

		if( MatMan.CreateMaterial(
			"Test/Materials/PositionSolidColour.material",
			PositionSolidColourMaterial ) != KIL_OK )
		{
			std::cout << "[Killer::Game::Execute] <ERROR> "
				"Failed to create wireframe material" << std::endl;

			return KIL_FAIL;
		}

		Model CubeModel( &MatMan );

		if( CubeModel.Load( "Test/Models/TestModel.killer" ) != KIL_OK )
		{
			std::cout << "[Killer::Game::Executable] <ERROR> "
				"Failed to load model" << std::endl;

			return KIL_FAIL;
		}

		Camera TestCamera;

		TestCamera.SetClippingPlanes( 1.0f, 100000.0f );
		TestCamera.SetFieldOfView( Killer::Pi / 2 );
		TestCamera.SetPosition( 0.0f, 0.0f, 100.0f );
		TestCamera.SetLookPoint( 0.0f, 0.0f, 0.0f );
		TestCamera.SetWorldUp( 0.0f, 1.0f, 0.0f );
		TestCamera.SetAspectRatio( 800.0f / 480.0f );
		TestCamera.SetProjectionMode( PROJECTIONMODE_PERSPECTIVE );

		TestCamera.CalculateProjectionMatrix( );
		TestCamera.CalculateViewMatrix( );

		KIL_FLOAT32 ZPosition, ZInc;

		ZPosition = 100.0f;
		ZInc = 1.0f;

		KIL_KEY_STATE OldKeyState;
		m_Keyboard.GetState( &OldKeyState );
		KIL_BOOL WireframeMode = KIL_FALSE;
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
		KIL_FLOAT32 RotateY = 0.0f;
		KIL_FLOAT32 RotateX = 0.0f;

		KIL_FLOAT32 XTrans = 0.0f, YTrans = 0.0f, ZTrans = 0.0f;

		KIL_BOOL NormalsActive = KIL_FALSE;

		while( !Quit )
		{
			m_Window.ProcessEvents( );
			KIL_KEY_STATE CurrentKeyState;
			GAMEPAD_STATE CurrentGamepadState;

			m_Keyboard.GetState( &CurrentKeyState );
			m_Gamepad.GetState( &CurrentGamepadState );

			if( CurrentKeyState.Keys[ KIL_KEY_ESCAPE ] )
			{
				Quit = KIL_TRUE;
			}

			if( CurrentKeyState.Keys[ KIL_KEY_N ] &&
				( OldKeyState.Keys[ KIL_KEY_N ] !=
					CurrentKeyState.Keys[ KIL_KEY_N ] ) )
			{
				if( NormalsActive )
				{
					CubeModel.HideNormals( );
				}
				else
				{
					CubeModel.ShowNormals( );
				}

				NormalsActive = !NormalsActive;
			}

			if( CurrentKeyState.Keys[ KIL_KEY_W ] &&
				( OldKeyState.Keys[ KIL_KEY_W ] !=
					CurrentKeyState.Keys[ KIL_KEY_W ] ) )
			{
				WireframeMode = !WireframeMode;

				if( WireframeMode )
				{
					glDisable( GL_CULL_FACE );
					CubeModel.ToggleWireframe( );
				}
				else
				{
					glEnable( GL_CULL_FACE );
					glFrontFace( GL_CCW );
					glCullFace( GL_BACK );

					CubeModel.ToggleWireframe( );
				}
			}

			RotateY += CurrentGamepadState.AnalogueStick[ 1 ].X * 0.01f;
			RotateX += CurrentGamepadState.AnalogueStick[ 1 ].Y * 0.01f;


			ZTrans += CurrentGamepadState.AnalogueStick[ 0 ].Y * 0.1f;
			XTrans += CurrentGamepadState.AnalogueStick[ 0 ].X * 0.1f;

			if( CurrentGamepadState.Buttons & GAMEPAD_BUTTON_L )
			{
				YTrans += 0.01f;
			}
			if( CurrentGamepadState.Buttons & GAMEPAD_BUTTON_R )
			{
				YTrans -= 0.01f;
			}

			CubeModel.SetPosition( Vector3( XTrans, YTrans, ZTrans ) );
			CubeModel.SetOrientation( Vector3( RotateX, RotateY, 0.0f ) );

			if( CurrentGamepadState.Buttons & GAMEPAD_BUTTON_START )
			{
				Quit = KIL_TRUE;
			}
			
			m_Renderer.Clear( );
			TestCamera.SetPosition( 0.0f, 0.0f, ZPosition );
			TestCamera.CalculateViewMatrix( );
			
			CubeModel.Render( TestCamera );

			m_Renderer.SwapBuffers( );

			if( Clock.GetSeconds( ) >= 1 )
			{
				BEAT_TIME BeatTime;
				GetBeatTime( BeatTime );

				std::cout << "@" << std::setfill( '0' ) << std::setw( 3 ) <<
					BeatTime.Beat << "." << std::setw( 2 ) <<
					BeatTime.CentiBeat << std::endl;

				Clock.Stop( );
				Clock.Start( );
			}

			/*if( ZPosition > 1000.0f )
			{
				ZInc = -1.0f;
			}

			if( ZPosition < 100.0f )
			{
				ZInc = 1.0f;
			}

			ZPosition += ZInc;*/

			memcpy( &OldKeyState, &CurrentKeyState, sizeof( OldKeyState ) );
		}

		GameTimer.Stop( );

		// Use LC_ALL=<LANG> to get correct format
		// LC_ALL=en_GB - British English
		// LC_ALL=de_DE - German
		// LC_ALL=ja_JP - Japanese
		std::cout << "Total running time: " << GameTimer.GetMicroseconds( ) <<
			"\u00B5s" << std::endl;

		return KIL_OK;
	}
}


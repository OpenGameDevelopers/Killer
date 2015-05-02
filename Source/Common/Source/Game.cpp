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
#include <Shader.hpp>
#include <VertexAttributes.hpp>

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

		// Triangle is a position + colour
		struct VERTEX Triangle[ 3 ] =
		{
			/*{ 0.5f, 0.5f, -1.0f, 0.5f, -0.5f, -1.0f },
			{ -0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }*/
			// Top-right, red
			{ 0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f },
			// Bottom-right, blue
			{ 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f },
			// Bottom-left, green
			{ -0.5f, -0.5f, -1.0f, 0.0f, 1.0f, 0.0f }
		};

		KIL_UINT16 TriangleIndices[ 3 ] = { 0, 1, 2 };

		VertexAttributes TriangleAttributes(
			m_Renderer.GetMaximumVertexAttributes( ) );

		TriangleAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3 );
		TriangleAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3 );

		RendererPrimitive TrianglePrimitive;

		TrianglePrimitive.Create( ( KIL_BYTE * )Triangle,
			( KIL_UINT16 * )TriangleIndices, 3, 3, TriangleAttributes,
			PRIMITIVE_TYPE_LIST );

		Shader TriangleShader;

		const char *pVertexSource =
			"attribute vec3 Position;\n"
			"attribute vec3 Colour;\n"
			"varying vec4 f_Colour;\n"
			"void main( )\n"
			"{\n"
			"	f_Colour = vec4( Colour, 1.0 );\n"
			"	gl_Position = vec4( Position, 1.0 );\n"
			"}\n";

		const char *pFragmentSource =
			"precision mediump float;\n"
			"varying vec4 f_Colour;\n"
			"void main( )\n"
			"{\n"
			"	gl_FragColor = f_Colour;\n"
			"}\n";

		TriangleShader.AddShaderSource( SHADER_TYPE_VERTEX, pVertexSource );
		TriangleShader.AddShaderSource( SHADER_TYPE_FRAGMENT,
			pFragmentSource );

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
			if( TriangleShader.Activate( ) != KIL_OK )
			{
				Quit = KIL_TRUE;
			}
			TrianglePrimitive.Render( );
			m_Renderer.SwapBuffers( );

			if( Clock.GetSeconds( ) >= 1 )
			{
				BEAT_TIME BeatTime;
				GetBeatTime( BeatTime );

				std::cout << "@" << std::setfill( '0' ) << std::setw( 3 ) <<
					BeatTime.Beat << "." << BeatTime.CentiBeat << std::endl;

				Clock.Stop( );
				Clock.Start( );
			}
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


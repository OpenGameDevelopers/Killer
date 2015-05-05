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
#include <Camera.hpp>
#include <cstring>
#include <Arithmetic.hpp>

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
		struct VERTEX Triangle[ 8 ] =
		{
			// Top-Left, white (FRONT)
			{ -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },	// 0
			// Top-right, red (FRONT)
			{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },		// 1
			// Bottom-left, green (FRONT)
			{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f },	// 2
			// Bottom-right, blue (FRONT)
			{ 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f },	// 3
			// Top-right, yellow (BACK)
			{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f },	// 4
			// Top-left, black (BACK)
			{ -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f },	// 5
			// Bottom-right, cyan (BACK)
			{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f },	// 6
			// Bottom-left, magenta (BACK)
			{ -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f }	// 7
		};

		KIL_UINT16 TriangleIndices[ 36 ] =
		{
			0, 2, 1, // FRONT
			1, 2, 3,
			1, 3, 6, // RIGHT
			1, 6, 4,
			5, 4, 6, // BACK
			6, 7, 5,
			0, 7, 2, // LEFT
			0, 5, 7,
			2, 7, 6, // BOTTOM
			6, 3, 2,
			1, 4, 5, // TOP
			5, 0, 1
		};

		VertexAttributes TriangleAttributes(
			m_Renderer.GetMaximumVertexAttributes( ) );

		TriangleAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3 );
		TriangleAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3 );

		RendererPrimitive TrianglePrimitive;

		TrianglePrimitive.Create( ( KIL_BYTE * )Triangle,
			( KIL_UINT16 * )TriangleIndices, 8, 36, TriangleAttributes,
			PRIMITIVE_TYPE_TRIANGLE_LIST );

		Shader TriangleShader;

		const char *pVertexSource =
			"attribute vec3 Position;\n"
			"attribute vec3 Colour;\n"
			"uniform mat4 View;\n"
			"uniform mat4 Projection;\n"
			"uniform mat4 World;\n"
			"varying vec4 f_Colour;\n"
			"void main( )\n"
			"{\n"
			"	f_Colour = vec4( Colour, 1.0 );\n"
			"	gl_Position = vec4( Position, 1.0 ) * World * View * Projection;\n"
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

		Shader WireframeShader;

		const char *pWireframeFragment =
			"precision mediump float;\n"
			"uniform vec4 WireframeColour;\n"
			"void main( )\n"
			"{\n"
			"	gl_FragColor = WireframeColour;\n"
			"}\n";

		WireframeShader.AddShaderSource( SHADER_TYPE_VERTEX, pVertexSource );
		WireframeShader.AddShaderSource( SHADER_TYPE_FRAGMENT,
			pWireframeFragment );

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

		Matrix4x4 Projection;
		Matrix4x4 View;

		TestCamera.GetProjectionMatrix( Projection );
		TestCamera.GetViewMatrix( View );

		KIL_FLOAT32 ProjectionRaw[ 16 ];
		KIL_FLOAT32 ViewRaw[ 16 ];

		Projection.AsFloat( ProjectionRaw );
		View.AsFloat( ViewRaw );

		TriangleShader.SetConstantData( "Projection", ProjectionRaw );
		TriangleShader.SetConstantData( "View", ViewRaw );

		WireframeShader.SetConstantData( "Projection", ProjectionRaw );
		WireframeShader.SetConstantData( "View", ViewRaw );

		KIL_FLOAT32 ZPosition, ZInc;

		ZPosition = 100.0f;
		ZInc = 1.0f;

		KIL_FLOAT32 WireframeColour [ 4 ] = { 0.0f, 1.0f, 0.0f, 1.0f };
		WireframeShader.SetConstantData( "WireframeColour", WireframeColour );

		Shader *pActiveShader = &TriangleShader;

		KIL_KEY_STATE OldKeyState;
		m_Keyboard.GetState( &OldKeyState );
		KIL_BOOL WireframeMode = KIL_FALSE;
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
		KIL_FLOAT32 RotateY = 0.0f;//Killer::Pi / 2.0f;
		KIL_FLOAT32 RotateX = 0.0f;

		Matrix4x4 CubeWorld;
		CubeWorld.Identity( );
		KIL_FLOAT32 CubeWorldRaw[ 16 ];
		CubeWorld.AsFloat( CubeWorldRaw );
		TriangleShader.SetConstantData( "World", CubeWorldRaw );
		WireframeShader.SetConstantData( "World", CubeWorldRaw );

		KIL_FLOAT32 XTrans = 0.0f, YTrans = 0.0f, ZTrans = 0.0f;
		
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


			if( CurrentKeyState.Keys[ KIL_KEY_W ] &&
				( OldKeyState.Keys[ KIL_KEY_W ] !=
					CurrentKeyState.Keys[ KIL_KEY_W ] ) )
			{
				WireframeMode = !WireframeMode;

				if( WireframeMode )
				{
					/*TrianglePrimitive.SetPrimitiveType(
						PRIMITIVE_TYPE_LINE_LOOP );*/
					pActiveShader = &WireframeShader;
					glDisable( GL_DEPTH_TEST );
					glDisable( GL_CULL_FACE );

					TrianglePrimitive.ToggleWireframe( );
				}
				else
				{
					/*TrianglePrimitive.SetPrimitiveType(
						PRIMITIVE_TYPE_TRIANGLE_LIST );*/
					pActiveShader = &TriangleShader;
					glEnable( GL_DEPTH_TEST );
					glEnable( GL_CULL_FACE );

					TrianglePrimitive.ToggleWireframe( );
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

			Vector3 CubeTranslation( XTrans, YTrans, ZTrans );

			Matrix4x4 RotateXMatrix, RotateYMatrix, TranslationMatrix;
			RotateXMatrix.RotateX( RotateX );
			RotateYMatrix.RotateY( RotateY );
			TranslationMatrix.Translate( CubeTranslation );

			CubeWorld = ( RotateYMatrix * RotateXMatrix ) *  TranslationMatrix;
			CubeWorld.AsFloat( CubeWorldRaw );

			pActiveShader->SetConstantData( "World", CubeWorldRaw );

			if( CurrentGamepadState.Buttons & GAMEPAD_BUTTON_START )
			{
				Quit = KIL_TRUE;
			}
			
			m_Renderer.Clear( );
			pActiveShader->Activate( );
			TestCamera.SetPosition( 0.0f, 0.0f, ZPosition );
			TestCamera.CalculateViewMatrix( );
			TestCamera.GetViewMatrix( View );
			View.AsFloat( ViewRaw );
			pActiveShader->SetConstantData( "View", ViewRaw );

			TrianglePrimitive.Render( );
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


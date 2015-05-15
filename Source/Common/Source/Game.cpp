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

		KIL_UINT32 WireframeMaterial;

		if( MatMan.CreateMaterial( "Test/Materials/Wireframe.material",
			WireframeMaterial ) != KIL_OK )
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

		struct VERTEX CubeVertices[ 24 ] =
		{
			// Top-Left, white (FRONT)
			{ -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },	// 0
			// Top-right, red (FRONT)
			{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f },		// 1
			// Bottom-left, green (FRONT)
			{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },	// 2
			// Bottom-right, blue (FRONT)
			{ 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },	// 3
			// Top-right, yellow (BACK)
			{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f },	// 4
			// Top-left, black (BACK)
			{ -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f },	// 5
			// Bottom-right, cyan (BACK)
			{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f },	// 6
			// Bottom-left, magenta (BACK)
			{ -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f },	// 7
			// Top-left, red (RIGHT)
			{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },		// 8
			// Top-right, yellow (RIGHT)
			{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },	// 9
			// Bottom-right, cyan (RIGHT)
			{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },	// 10
			// Bottom-left, blue (RIGHT)
			{ 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },	// 11
			// Top-left, black (LEFT)
			{ -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f },	// 12
			// Top-right, white (LEFT)
			{ -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f },	// 13
			// Bottom-right, green (LEFT)
			{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f },	// 14
			// Bottom-left, magenta (LEFT)
			{ -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },	// 15
			// Top-left, black (TOP)
			{ -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },	// 16
			// Top-right, yellow (TOP)
			{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },	// 17
			// Bottom-right, red (TOP)
			{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },		// 18
			// Bottom-left, white (TOP)
			{ -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },	// 19
			// Top-left, green (BOTTOM)
			{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f },	// 20
			// Top-right, blue (BOTTOM) 
			{ 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f },	// 21
			// Bottom-right, cyan (BOTTOM)
			{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f },	// 22
			// Bottom-left, magenta (BOTTOM)
			{ -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f }	// 23
		};

		KIL_UINT16 CubeIndices[ 36 ] =
		{
			0, 2, 1, // FRONT
			1, 2, 3,
			11, 10, 8, // RIGHT
			9, 8, 10,
			5, 4, 6, // BACK
			6, 7, 5,
			12, 15, 14, // LEFT
			14, 13, 12,
			20, 23, 22, // BOTTOM
			22, 21, 20,
			16, 19, 18, // TOP
			18, 17, 16
		};

		VertexAttributes CubeAttributes(
			m_Renderer.GetMaximumVertexAttributes( ) );

		// Position
		CubeAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3 );
		// Colour
		CubeAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3 );
		// ST
		CubeAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT2 );
		// Normal
		CubeAttributes.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3 );

		/*RendererPrimitive CubePrimitive;

		CubePrimitive.Create( ( KIL_BYTE * )CubeVertices,
			( KIL_UINT16 * )CubeIndices, 24, 36, CubeAttributes,
			PRIMITIVE_TYPE_TRIANGLE_LIST );*/

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

		KIL_SINT32 Zero = 0;
		KIL_FLOAT32 One = 1.0f;

		MatMan.SetShaderConstant( TextureMaterial, "Projection",
			ProjectionRaw );
		MatMan.SetShaderConstant( TextureMaterial, "View", ViewRaw );
		MatMan.SetShaderConstant( TextureMaterial, "Texture", &Zero );
		MatMan.SetShaderConstant( TextureMaterial, "Shininess", &One );

		KIL_FLOAT32 WireframeColour [ 4 ] = { 0.0f, 1.0f, 0.0f, 1.0f };

		MatMan.SetShaderConstant( WireframeMaterial, "Projection",
			ProjectionRaw );
		MatMan.SetShaderConstant( WireframeMaterial, "View", ViewRaw );
		MatMan.SetShaderConstant( WireframeMaterial, "WireframeColour",
			WireframeColour );

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

		Matrix4x4 CubeWorld;
		CubeWorld.Identity( );
		KIL_FLOAT32 CubeWorldRaw[ 16 ];
		CubeWorld.AsFloat( CubeWorldRaw );

		KIL_FLOAT32 XTrans = 0.0f, YTrans = 0.0f, ZTrans = 0.0f;

		KIL_UINT32 ActiveMaterial = TextureMaterial;
		
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
					glDisable( GL_DEPTH_TEST );
					glDisable( GL_CULL_FACE );
					CubeModel.ToggleWireframe( );

					//CubePrimitive.ToggleWireframe( );

					ActiveMaterial = WireframeMaterial;
				}
				else
				{
					glEnable( GL_DEPTH_TEST );
					glEnable( GL_CULL_FACE );
					glFrontFace( GL_CCW );
					glCullFace( GL_BACK );

					CubeModel.ToggleWireframe( );

					//CubePrimitive.ToggleWireframe( );

					ActiveMaterial = TextureMaterial;
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

			MatMan.SetShaderConstant( ActiveMaterial, "World", CubeWorldRaw );

			if( CurrentGamepadState.Buttons & GAMEPAD_BUTTON_START )
			{
				Quit = KIL_TRUE;
			}
			
			m_Renderer.Clear( );
			TestCamera.SetPosition( 0.0f, 0.0f, ZPosition );
			TestCamera.CalculateViewMatrix( );
			TestCamera.GetViewMatrix( View );
			View.AsFloat( ViewRaw );
			MatMan.SetShaderConstant( ActiveMaterial, "View", ViewRaw );
			KIL_FLOAT32 Position[ 3 ] = { 0.0f, 0.0f, ZPosition };

			if( ActiveMaterial == TextureMaterial )
			{
				MatMan.SetShaderConstant( ActiveMaterial, "EyePosition",
					Position );
			}

			MatMan.Apply( ActiveMaterial );

			//CubePrimitive.Render( );
			
			CubeModel.Render( );

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


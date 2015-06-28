#include <MainMenuState.hpp>
#include <GameStateManager.hpp>
#include <Renderer/Renderer.hpp>
#include <Utility/InputBinder.hpp>
#include <Utility/EventRouter.hpp>
#include <Renderer/VertexAttributes.hpp>

namespace Killer
{
	MainMenuState::MainMenuState( )
	{
		m_pInputBinder = new ZED::Utility::InputBinder( );
		m_pEventRouter = new ZED::Utility::EventRouter( "Main Menu", ZED_TRUE,
			2 );
	}

	MainMenuState::~MainMenuState( )
	{
	}

	ZED_UINT32 MainMenuState::Enter( )
	{
		zedTrace( "[Killer::MainMenuState::Enter] <INFO> "
			"Entering Main Menu State\n" );

		ZED::Utility::SetGlobalEventRouter( this->m_pEventRouter );
		GameStateManager::GetInstance( ).SetInputBinder( m_pInputBinder );

		GameStateManager::GetInstance( ).GetRenderer( )->ClearColour( 0.2f,
			0.2f, 0.8f );

		ZED_FLOAT32 Triangle[ 9 ] =
		{
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		ZED_UINT16 Indices[ 3 ] =
		{
			0, 1, 2
		};

		ZED::Renderer::VertexAttributes Attributes( 16 );
		Attributes.AddVertexAttribute( ZED::VERTEXATTRIBUTE_TYPE_FLOAT3,
			ZED::VERTEXATTRIBUTE_INTENT_POSITION );

		m_TestTriangle.Create( 3, ( ZED_BYTE * )( Triangle ), 3,
			Indices, Attributes, ZED::Renderer::PRIMITIVE_TYPE_TRIANGLE_LIST );

		const char *pTriangleVertexShader =
			"#version 110\n"
			"attribute vec3 a_Position;\n"
			"void main( )\n"
			"{\n"
			"	gl_Position = vec4( a_Position, 1.0 );\n"
			"}\n";

		const char *pTriangleFragmentShader =
			"#version 110\n"
			"void main( )\n"
			"{\n"
			"	gl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );\n"
			"}\n";

		if( m_OpenGLShader.Compile( &pTriangleVertexShader,
			ZED_VERTEX_SHADER, ZED_FALSE ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		if( m_OpenGLShader.Compile( &pTriangleFragmentShader,
			ZED_FRAGMENT_SHADER, ZED_FALSE ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		return ZED_OK;
	}

	void MainMenuState::Update( const ZED_UINT64 p_DeltaTime )
	{
	}

	void MainMenuState::Render( )
	{
		m_OpenGLShader.Activate( );
		m_TestTriangle.Render( );
	}

	ZED_UINT32 MainMenuState::Exit( )
	{
		zedTrace( "[Killer::MainMenuState::Exit] <INFO> "
			"Exiting Main Menu State\n" );
		GameStateManager::GetInstance( ).Quit( );
		return ZED_OK;
	}

	ZED_CHAR8 *MainMenuState::GetName( ) const
	{
		return "Main Menu";
	}
}


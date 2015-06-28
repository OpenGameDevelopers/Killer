#include <GameStateManager.hpp>
#include <Game/GameState.hpp>
#include <Game/GameStateManager.hpp>
#include <System/Debugger.hpp>

namespace Killer
{
	GameStateManager::GameStateManager( )
	{
	}

	GameStateManager::~GameStateManager( )
	{
	}

	ZED_UINT32 GameStateManager::Initialise( )
	{
		if( ZED::Game::GameStateManager::Initialise( ) != ZED_OK )
		{
			zedTrace( "[Killer::GameStateManager::Initialise] <ERROR> "
				"Failed to initialise the base Game State Manager\n" );

			return ZED_FAIL;
		}

		if( !m_pRenderer )
		{
			zedTrace( "[Killer::GameStateManager::Initialise] <ERROR> "
				"Renderer not set\n" );

			return ZED_FAIL;
		}

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::Update( const ZED_UINT64 p_DeltaTime )
	{
		m_GameStateStack.top( )->Update( p_DeltaTime );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::Render( )
	{
		m_GameStateStack.top( )->Render( );

		return ZED_OK;
	}

	GameStateManager &GameStateManager::GetInstance( )
	{
		static GameStateManager Instance;
		return Instance;
	}
}



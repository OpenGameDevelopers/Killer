#ifndef ___GAMESTATEMANAGER_HPP__
#define ___GAMESTATEMANAGER_HPP__

#include <Game/GameStateManager.hpp>

namespace ZED
{
	namespace Game
	{
		class GameState;
		class GameStateInputListener;
	}
}

namespace Killer
{
	class GameStateManager : public ZED::Game::GameStateManager
	{
	public:
		GameStateManager( );
		virtual ~GameStateManager( );

		virtual ZED_UINT32 Initialise( );

		static GameStateManager &GetInstance( );
	
	protected:
		virtual ZED_UINT32 Update( const ZED_UINT64 p_DeltaTime );
		virtual ZED_UINT32 Render( );

	private:
	};
}

#endif // ___GAMESTATEMANAGER_HPP__


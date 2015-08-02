#include <Game.hpp>
#include <PandoraFullscreen.hpp>
#include <iostream>

namespace Killer
{
	KIL_UINT32 Game::PlatformInitialise( )
	{
		if( Killer::EnterPandoraFullscreen( ) != KIL_OK )
		{
			std::cout << "[Killer::main] <ERROR> "
				"Failed to enter fullscreen mode" << std::endl;

			return KIL_FAIL;
		}

		return KIL_OK;
	}

	KIL_UINT32 Game::PlatformTerminate( )
	{
		Killer::ExitPandoraFullscreen( );

		return KIL_OK;
	}
}


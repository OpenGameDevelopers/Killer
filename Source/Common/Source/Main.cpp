#include <Game.hpp>
#include <GitVersion.hpp>
#include <iostream>
#include <PandoraFullscreen.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	if( Killer::EnterPandoraFullscreen( ) != KIL_OK )
	{
		std::cout << "[Killer::main] <ERROR> "
			"Failed to enter fullscreen mode" << std::endl;

		return KIL_FAIL;
	}

	std::cout << "Killer" << std::endl;
	std::cout << "Build Information" << std::endl;
	std::cout << "\tVersion: " << GIT_BUILD_VERSION << std::endl;
	std::cout << "\tTag:     " << GIT_TAG_NAME << std::endl;
	std::cout << "\tCommit:  " << GIT_COMMITHASH << std::endl;

	Killer::Game Killer;

	if( Killer.Initialise( ) != KIL_OK )
	{
		std::cout << "[Killer::main] <ERROR> Failed to start the game" <<
			std::endl;

		return KIL_FAIL;
	}

	Killer.Execute( );

	Killer::ExitPandoraFullscreen( );

	return KIL_OK;
}


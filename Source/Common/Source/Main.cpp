#include <iostream>
#include <GameWindow.hpp>
#include <GitVersion.hpp>
#include <unistd.h>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Killer" << std::endl;
	std::cout << "Build Information" << std::endl;
	std::cout << "\tVersion: " << GIT_BUILD_VERSION << std::endl;
	std::cout << "\tTag:     " << GIT_TAG_NAME << std::endl;
	std::cout << "\tCommit:  " << GIT_COMMITHASH << std::endl;

	Killer::GameWindow TestWindow;

	if( TestWindow.Create( ) != KIL_OK )
	{
		return KIL_FAIL;
	}

	sleep( 3 );

	return 0;
}


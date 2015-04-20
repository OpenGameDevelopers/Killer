#include <iostream>
#include <GameWindow.hpp>
#include <Renderer.hpp>
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
		std::cout << "[Killer::main] <ERROR> "
			"Failed to create the window" << std::endl;
		return KIL_FAIL;
	}

	Killer::Renderer TestRenderer;

	if( TestRenderer.Initialise( TestWindow ) != KIL_OK )
	{
		std::cout << "[Killer::main] <ERROR> "
			"Failed to initialise the renderer" << std::endl;
		return KIL_FAIL;
	}

	TestRenderer.SetClearColour(  1.0f, 153 / 255.0f, 51.0f / 255.0f );
	TestRenderer.Clear( );
	TestRenderer.SwapBuffers( );

	sleep( 3 );

	return 0;
}


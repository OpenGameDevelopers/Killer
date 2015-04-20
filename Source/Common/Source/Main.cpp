#include <iostream>
#include <GitVersion.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Killer" << std::endl;
	std::cout << "Build Information" << std::endl;
	std::cout << "\tVersion: " << GIT_BUILD_VERSION << std::endl;
	std::cout << "\tTag:     " << GIT_TAG_NAME << std::endl;
	std::cout << "\tCommit:  " << GIT_COMMITHASH << std::endl;

	return 0;
}


#include <stdio.h>

#if WIN32
#	include "Windows.h"
#	define sleep(x) Sleep(x)
#else // WIN32
#	include <unistd.h>
#endif // WIN32

#include "World.h"

int main(int argc, char ** argv)
{
	Network::World world(1000.0f, 1000.0f);

	world.init();

	while (1)
	{
		world.update(1.0f);
		sleep(1);
	}

	world.release();

	return(0);
}

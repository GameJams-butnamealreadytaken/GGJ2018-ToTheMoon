#include <stdio.h>
#include <unistd.h>

#include "World.h"

int main(int argc, char ** argv)
{
	Network::World world(1000.0f, 1000.0f);

	world.init();

	for (int i = 0; i < 60; ++i)
	{
		printf("Iteration # %d\n", i+1);
		world.update(1.0f);
		sleep(1);
	}

	world.release();

	return(0);
}

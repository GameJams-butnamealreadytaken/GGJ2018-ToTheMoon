#include "World.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string.h> // memset

namespace Network
{

/**
 * @brief Constructor
 */
World::World(float size_x, float size_y) : m_ShipCount(0), m_bounds(size_x, size_y)
{
	memset(m_aShips, 0, sizeof(m_aShips));
}

/**
 * @brief Destructor
 */
World::~World(void)
{
	// ...
}

/**
 * @brief update
 * @param delta time in seconds
 */
void World::update(float dt)
{
	for (unsigned int i = 0; i < MAX_SHIPS; ++i)
	{
		m_aShips[i].update(dt);

	}
}

}

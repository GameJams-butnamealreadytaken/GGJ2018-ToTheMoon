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
World::World(void) : m_ShipCount(0)
{
	memset(m_aShips, 0, sizeof(m_aShips));
}

/**
 * @brief Destructor
 */
World::~World(void)
{

}

/**
 * @brief update
 * @param delta time in seconds
 */
void World::update(double dt)
{
	// TODO
}

}

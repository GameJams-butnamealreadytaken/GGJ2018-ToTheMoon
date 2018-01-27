#include "World.h"

#if __gnu_linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif // __gnu_linux__

#include <string.h> // memset

namespace Network
{

/**
 * @brief Constructor
 */
World::World(float size_x, float size_y) : m_ShipCount(0), m_halfSize(size_x, size_y)
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
		Ship & ship = m_aShips[i];

		ship.update(dt);

		ship.clampPosition(m_halfSize);
	}
}

/**
 * @brief Create Ship
 * @return new Ship
 */
Ship * World::createShip(void)
{
	return(createShip(0.0f, 0.0f));
}

/**
 * @brief Create Ship
 * @param x
 * @param y
 * @return new Ship
 */
Ship * World::createShip(float x, float y)
{
	Ship * ship = m_aShips + m_ShipCount;

	++m_ShipCount;

	*ship = Ship(x, y);

	return(ship);
}

}

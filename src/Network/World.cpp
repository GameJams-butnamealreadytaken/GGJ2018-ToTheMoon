#include "World.h"

#if __gnu_linux__
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <net/if.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#	include <unistd.h>
#else
#	include <winsock2.h>
#	include <ws2tcpip.h>
#endif // __gnu_linux__

#include <string.h> // memset

#define BRD_HELO_ADDR "192.168.1.255"
#define BRD_HELO_PORT (8123)

namespace Network
{

/**
 * @brief Constructor
 */
World::World(float size_x, float size_y) : m_ShipCount(0), m_halfSize(size_x, size_y)
{
	memset(m_aShips, 0, sizeof(m_aShips));

	m_sock = -1;
}

/**
 * @brief Destructor
 */
World::~World(void)
{
	// ...
}

/**
 * @brief Initialize
 * @return
 */
bool World::init(void)
{
	if (!initSocket())
	{
		return(false);
	}

	if (!broadcastHelloMessage())
	{
		releaseSocket();
		return(false);
	}

	return(true);
}

/**
 * @brief Release
 */
void World::release(void)
{
	releaseSocket();
}

/**
 * @brief Initialize socket
 * @return
 */
bool World::initSocket(void)
{
	return(false); // TODO
}

/**
 * @brief World::releaseSocket
 * @return
 */
void World::releaseSocket(void)
{
#if WIN32
	closesocket(m_sock);
#else // WIN32
	close(m_sock);
#endif // WIN32
}

/**
 * @brief Broadcast Hello Message
 * @return
 */
bool World::broadcastHelloMessage(void)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock == -1)
	{
		return(false);
	}

	int enable = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void*)&enable, sizeof(int)) < 0)
	{
#if WIN32
		closesocket(sock);
#else // WIN32
		close(sock);
#endif // WIN32
		return(false);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(BRD_HELO_PORT);
	addr.sin_addr.s_addr = inet_addr(BRD_HELO_ADDR);

	unsigned int MSG [1024];
#if WIN32
	SSIZE_T size = sendto(sock, (void*)MSG, sizeof(MSG), 0, (sockaddr*)&addr, sizeof(addr));
#else // WIN32
	ssize_t size = sendto(sock, (void*)MSG, sizeof(MSG), 0, (sockaddr*)&addr, sizeof(addr));
#endif // WIN32

	if (size < 0)
	{
#if WIN32
		closesocket(sock);
#else // WIN32
		close(sock);
#endif // WIN32
		return(false);
	}

#if WIN32
	closesocket(sock);
#else // WIN32
	close(sock);
#endif // WIN32

	return(true);
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

#include "World.h"

#include "WorldListener.h"

#include <stdio.h>
#include <assert.h>

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

#define PORT (8123)

#define BRD_HELO_ADDR	"192.168.1.255"
#define BRD_HELO_PORT	(PORT)

#define MAX_MESSAGE_SIZE (512)

#define ENABLE_DEBUG_PRINT 1

namespace Network
{

/**
 * @brief Constructor
 */
World::World(float size_x, float size_y) 
: m_ShipCount(0)
, m_halfSize(size_x, size_y)
, m_TransmitterCount(0)
, m_pListener(nullptr)
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
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (m_sock < 0)
	{
		return(false);
	}

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(PORT);
	si.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(m_sock, (struct sockaddr*)&si, sizeof(si)) <0)
	{
#if WIN32
		closesocket(m_sock);
#else // WIN32
		close(m_sock);
#endif // WIN32
		return(false);
	}

	int enable = 1;
	
#if WIN32
	if (setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (const char *)&enable, sizeof(int)) < 0)
	{
		closesocket(m_sock);
#else // WIN32
	if (setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (void*)&enable, sizeof(int)) < 0)
		{
		close(m_sock);
#endif // WIN32
		return(false);
	}

	return(true);
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
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(BRD_HELO_PORT);
	addr.sin_addr.s_addr = inet_addr(BRD_HELO_ADDR);

	HelloMessage msg;
#if WIN32
	SSIZE_T size = sendto(m_sock, (const char*)&msg, sizeof(msg), 0, (sockaddr*)&addr, sizeof(addr));
#else // WIN32
	ssize_t size = sendto(m_sock, (void*)&msg, sizeof(msg), 0, (sockaddr*)&addr, sizeof(addr));
#endif // WIN32

	return(true);
}

/**
 * @brief World::handleHelloMessage
 */
void World::handleHelloMessage(HelloMessage * msg, struct sockaddr* sender, unsigned int sendsize)
{
	char machine[NI_MAXHOST];
	char service[NI_MAXSERV];

	if (0 == getnameinfo(sender, sendsize, machine, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV))
	{
		SyncShipStateMessage response;
		response.shipId = 0;
		response.position = vec2(0.0f, 0.0f);
		response.target = vec2(0.0f, 0.0f);
		response.speed = 0.0f;

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(BRD_HELO_PORT);
		addr.sin_addr.s_addr = inet_addr(machine);
#if WIN32
		SSIZE_T size = sendto(m_sock, (const char*)&response, sizeof(SyncShipStateMessage), 0, (sockaddr*)&addr, sizeof(addr));
#else // WIN32
		ssize_t size = sendto(m_sock, (void*)&response, sizeof(SyncShipStateMessage), 0, (sockaddr*)&addr, sizeof(addr));
#endif // WIN32
	
		assert(size > 0);
	}
}

/**
 * @brief World::handleSyncShipStateMessage
 */
void World::handleSyncShipStateMessage(SyncShipStateMessage * msg, struct sockaddr* sender, unsigned int sendsize)
{
	Ship * ship = nullptr; // FIXME : find ship msg->shipId

	if (!ship)
	{
		ship = createShip();
		assert(nullptr != ship);
		if (m_pListener)
		{
			m_pListener->onShipCreated(ship);
		}
	}

	// Set Attributes
	ship->m_position = msg->position;
	ship->m_target = msg->target;
	ship->m_speed = msg->speed;
}

/**
 * @brief World::handleCreateShipMessage
 */
void World::handleCreateShipMessage(CreateShipMessage * msg, struct sockaddr* sender, unsigned int sendsize)
{
	Ship * ship = createShip();
	assert(nullptr != ship);
	if (m_pListener)
	{
		m_pListener->onShipCreated(ship);
	}

	// Set Attributes
	ship->m_position = msg->position;
	ship->m_target = msg->target;
	ship->m_speed = msg->speed;
}

/**
 * @brief World::handleCreateTransmitterMessage
 */
void World::handleCreateTransmitterMessage(CreateTransmitterMessage * msg, struct sockaddr* sender, unsigned int sendsize)
{
	// TODO
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

	//
	// Receive messages

	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(m_sock, &fdset);

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	if (select(m_sock+1, &fdset, nullptr, nullptr, &timeout) > 0)
	{
		struct sockaddr_storage sender;
		socklen_t sendsize = sizeof(sender);
		memset(&sender, 0, sizeof(sender));

#if WIN32	
		char MSG [MAX_MESSAGE_SIZE];
		SSIZE_T size = recvfrom(m_sock, MSG, sizeof(MSG), 0, (struct sockaddr*)&sender, &sendsize);
#else // WIN32
		unsigned char MSG[MAX_MESSAGE_SIZE];
		ssize_t size = recvfrom(m_sock, MSG, sizeof(MSG), 0, (struct sockaddr*)&sender, &sendsize);
#endif // WIN32
		

		if (size <= 0)
		{
			return;
		}

		MSG_ID id = *((MSG_ID*)MSG);

		switch (id)
		{
			case HELLO:
			{
				static_assert(sizeof(HelloMessage) < MAX_MESSAGE_SIZE, "HelloMessage is too big !");
				assert(sizeof(HelloMessage) == size);
				handleHelloMessage((HelloMessage*)MSG, (struct sockaddr*)&sender, sendsize);
			}
			break;

			case SYNC_SHIP_STATE:
			{
				static_assert(sizeof(SyncShipStateMessage) < MAX_MESSAGE_SIZE, "ShipStateMessage is too big !");
				assert(sizeof(SyncShipStateMessage) == size);
				handleSyncShipStateMessage((SyncShipStateMessage*)MSG, (struct sockaddr*)&sender, sendsize);
			}
			break;

			case CREATE_SHIP:
			{
				static_assert(sizeof(CreateShipMessage) < MAX_MESSAGE_SIZE, "ShipStateMessage is too big !");
				assert(sizeof(CreateShipMessage) == size);
				handleCreateShipMessage((CreateShipMessage*)MSG, (struct sockaddr*)&sender, sendsize);
			}
			break;

			case CREATE_TRANSMITTER:
			{
				static_assert(sizeof(CreateTransmitterMessage) < MAX_MESSAGE_SIZE, "ShipStateMessage is too big !");
				assert(sizeof(CreateTransmitterMessage) == size);
				handleCreateTransmitterMessage((CreateTransmitterMessage*)MSG, (struct sockaddr*)&sender, sendsize);
			}
			break;
		}

#if ENABLE_DEBUG_PRINT
		char machine[NI_MAXHOST];
		char service[NI_MAXSERV];

		if (0 == getnameinfo((struct sockaddr*)&sender, sendsize, machine, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV))
		{
			switch (id)
			{
				case HELLO:
				{
					printf("HELLO from %s:%s\n", machine, service);
				}
				break;

				case SYNC_SHIP_STATE:
				{
					printf("SHIP_STATE from %s:%s\n", machine, service);
				}
				break;

				case CREATE_SHIP:
				{
					printf("CREATE_SHIP from %s:%s\n", machine, service);
				}
				break;

				case CREATE_TRANSMITTER:
				{
					printf("CREATE_TRANSMITTER from %s:%s\n", machine, service);
				}
				break;
			}
		}
#endif // ENABLE_DEBUG_PRINT
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

/**
* @brief Create Transmitter
* @param x
* @param y
* @return new Transmitter
*/
Transmitter * World::createTransmitter(void)
{
	return(createTransmitter(0.0f, 0.0f));
}

/**
* @brief Create Transmitter
* @param x
* @param y
* @return new Transmitter
*/
Transmitter * World::createTransmitter(float x, float y)
{
	Transmitter * transmitter = m_aTransmitters + m_TransmitterCount;

	++m_TransmitterCount;

	*transmitter = Transmitter(x, y);

	return(transmitter);
}


}

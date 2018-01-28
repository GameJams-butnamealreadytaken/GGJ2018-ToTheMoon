#include "World.h"

#include "WorldListener.h"
#include "NetworkHelper.h"

#include <stdio.h>
#include <assert.h>
#include <string.h> // memset

#define MAX_MESSAGE_SIZE (512)

#define ENABLE_DEBUG_PRINT 0
#define ENABLE_CHECKS 1

namespace Network
{

/**
 * @brief Constructor
 */
World::World(float size_x, float size_y) 
: m_ShipCount(0)
, m_TransmitterCount(0)
, m_halfSize(size_x, size_y)
, m_pListener(nullptr)
{
	memset(m_aShips, 0, sizeof(m_aShips));
	memset(m_aOwnedShips, 0, sizeof(m_aOwnedShips));
	memset(m_aTransmitters, 0, sizeof(m_aTransmitters));
	memset(m_aOwnedTransmitters, 0, sizeof(m_aOwnedTransmitters));
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
	if (!m_network.InitSocket())
	{
		return(false);
	}

	char szBroadcast[256];
	NetworkHelper::discoverNetwork(szBroadcast, 256);

	if (!broadcastHelloMessage())
	{
		m_network.CloseSocket();
		return(false);
	}

	return(true);
}

/**
 * @brief Release
 */
void World::release(void)
{
	m_network.CloseSocket();
}

/**
 * @brief Broadcast Hello Message
 * @return
 */
bool World::broadcastHelloMessage(void)
{
#if __gnu_linux__
	uuid_generate(m_MyHelloUUID);
#else
	UuidCreate(&m_MyHelloUUID);
#endif // __gnu_linux__

	HelloMessage msg;
#if __gnu_linux__
	uuid_copy(msg.helloId, m_MyHelloUUID);
#else
	memcpy(&msg.helloId, (void*)&m_MyHelloUUID, sizeof(uuid_t));
#endif // __gnu_linux__

	return(m_network.BroadcastMessage(msg));
}

/**
 * @brief World::handleHelloMessage
 */
void World::handleHelloMessage(HelloMessage * msg, char * machine, char * service)
{
	printf("HELLO from %s:%s\n", machine, service);
	fflush(stdout);

#if WIN32
	RPC_STATUS status;
	if (UuidCompare(&m_MyHelloUUID, &msg->helloId, &status) == 0)
#else // WIN32
	if (uuid_compare(m_MyHelloUUID, msg->helloId) == 0)
#endif // WIN32
	{
		return;
	}

	if (CURRENT_NETWORK_VERSION != msg->version)
	{
		printf("BAD VERSION !\n");
		return; // BAD VERSION !
	}

	for (int i = 0; i < MAX_SHIPS; ++i)
	{
		if (m_aOwnedShips[i])
		{
			SyncShipStateMessage response;
#if __gnu_linux__
			uuid_copy(response.shipId, m_aOwnedShips[i]->m_uuid);
#else
			memcpy(&response.shipId, (void*)&m_aOwnedShips[i]->m_uuid, sizeof(uuid_t));
#endif // __gnu_linux__
			response.position = m_aOwnedShips[i]->getPosition();
			response.target = m_aOwnedShips[i]->getTarget();
			response.speed = m_aOwnedShips[i]->getSpeed();
			response.team = m_aOwnedShips[i]->getTeam();

			m_network.SendMessageToMachine(response, machine);
		}
	}

	for (int i = 0; i < MAX_TRANSMITTERS; ++i)
	{
		if (m_aOwnedTransmitters[i])
		{
			SyncTransmitterStateMessage response;
#if __gnu_linux__
			uuid_copy(response.transmitterId, m_aOwnedTransmitters[i]->m_uuid);
#else
			memcpy(&response.transmitterId, (void*)&m_aOwnedTransmitters[i]->m_uuid, sizeof(uuid_t));
#endif // __gnu_linux__
			response.position = m_aOwnedTransmitters[i]->getPosition();
			response.team = m_aOwnedTransmitters[i]->getTeam();

			m_network.SendMessageToMachine(response, machine);
		}
	}

	//
	// Say HELLO to the new client
	if (m_network.RegisterClient(machine, msg->helloId))
	{
		HelloMessage msg;
		m_network.SendMessageToMachine(msg, machine);
	}
}

/**
 * @brief World::handlePingMessage
 */
void World::handlePingMessage(PingMessage * msg, char * machine, char * service)
{
	printf("PING from %s:%s\n", machine, service);
	fflush(stdout);

	// TODO
}

/**
 * @brief World::handleCreateShipMessage
 */
void World::handleCreateShipMessage(CreateShipMessage * msg, char * machine, char * service)
{
	printf("CREATE_SHIP from %s:%s\n", machine, service);
	fflush(stdout);

	Ship * ship = createShipInternal(msg->shipId, 0, 0.0f, 0.0f);
	assert(nullptr != ship);

	// Set Attributes
	ship->m_position = msg->position;
	ship->m_target = msg->target;
	ship->m_speed = msg->speed;
	ship->m_team = msg->team;

	// Notify the game
	if (m_pListener)
	{
		m_pListener->onShipCreated(ship);
	}
}

/**
 * @brief World::handleDestroyShipMessage
 */
void World::handleDestroyShipMessage(DestroyShipMessage * msg, char * machine, char * service)
{
	printf("DESTROY_SHIP from %s:%s\n", machine, service);
	fflush(stdout);

	// TODO
}

/**
 * @brief World::handleSyncShipStateMessage
 */
void World::handleSyncShipStateMessage(SyncShipStateMessage * msg, char * machine, char * service)
{
	printf("SYNC_SHIP_STATE from %s:%s\n", machine, service);
	fflush(stdout);

	bool bCreated = false;

	Ship * ship = findShip(msg->shipId);

	if (!ship)
	{
		ship = createShipInternal(msg->shipId, 0, 0.0f, 0.0f);
		assert(nullptr != ship);
		bCreated = true;
	}

	// Set Attributes
	ship->m_position = msg->position;
	ship->m_target = msg->target;
	ship->m_speed = msg->speed;
	ship->m_team = msg->team;

	if (bCreated)
	{
		if (m_pListener)
		{
			m_pListener->onShipCreated(ship);
		}
	}
}

/**
 * @brief World::handleCreateTransmitterMessage
 */
void World::handleCreateTransmitterMessage(CreateTransmitterMessage * msg, char * machine, char * service)
{
	printf("CREATE_TRANSMITTER from %s:%s\n", machine, service);
	fflush(stdout);

	Transmitter * transmitter = createTransmitterInternal(msg->transmitterId, 0, 0.0f, 0.0f);
	assert(nullptr != transmitter);

	// Set Attributes
	transmitter->m_position = msg->position;
	transmitter->m_team = msg->team;

	// Notify the game
	if (m_pListener)
	{
		m_pListener->onTransmitterCreate(transmitter);
	}
}

/**
 * @brief World::handleDestroyTransmitterMessage
 */
void World::handleDestroyTransmitterMessage(DestroyTransmitterMessage * msg, char * machine, char * service)
{
	printf("DESTROY_TRANSMITTER from %s:%s\n", machine, service);
	fflush(stdout);

	// TODO
}

/**
 * @brief World::handleSyncTransmitterStateMessage
 */
void World::handleSyncTransmitterStateMessage(SyncTransmitterStateMessage * msg, char * machine, char * service)
{
	printf("SYNC_TRANSMITTER_STATE from %s:%s\n", machine, service);
	fflush(stdout);

	bool bCreated = false;

	Transmitter * transmitter = findTransmitter(msg->transmitterId);

	if (!transmitter)
	{
		transmitter = createTransmitterInternal(msg->transmitterId, 0, 0.0f, 0.0f);
		assert(nullptr != transmitter);
		bCreated = true;
	}

	// Set Attributes
	transmitter->m_position = msg->position;
	transmitter->m_team = msg->team;

	if (bCreated)
	{
		if (m_pListener)
		{
			m_pListener->onTransmitterCreate(transmitter);
		}
	}
}

/**
 * @brief update
 * @param delta time in seconds
 */
void World::update(float dt)
{
	for (unsigned int i = 0; i < m_ShipCount; ++i)
	{
		Ship & ship = m_aShips[i];

		ship.update(dt, m_network);

		ship.clampPosition(m_halfSize);
	}

	for (unsigned int i = 0; i < m_TransmitterCount; ++i)
	{
		Transmitter & transmitter = m_aTransmitters[i];

		transmitter.update(dt, m_network);
	}

	//
	// Receive messages
	unsigned int size = MAX_MESSAGE_SIZE;
	char MSG [MAX_MESSAGE_SIZE];

	char machine[1025] = { '\0' };
	char service[1025] = { '\0' };

	if (m_network.Receive(MSG, size, machine, service))
	{
		if (size > 0)
		{
			MSG_ID id = *((MSG_ID*)MSG);

			switch (id)
			{
				case HELLO:
				{
					static_assert(sizeof(HelloMessage) < MAX_MESSAGE_SIZE, "HelloMessage is too big !");
					assert(sizeof(HelloMessage) == size);
					handleHelloMessage((HelloMessage*)MSG, machine, service);
				}
				break;

				case PING:
				{
					static_assert(sizeof(PingMessage) < MAX_MESSAGE_SIZE, "PingMessage is too big !");
					assert(sizeof(PingMessage) == size);
					handlePingMessage((PingMessage*)MSG, machine, service);
				}
				break;

				case SHIP_CREATE:
				{
					static_assert(sizeof(CreateShipMessage) < MAX_MESSAGE_SIZE, "CreateShipMessage is too big !");
					assert(sizeof(CreateShipMessage) == size);
					handleCreateShipMessage((CreateShipMessage*)MSG, machine, service);
				}
				break;

				case SHIP_DESTROY:
				{
					static_assert(sizeof(DestroyShipMessage) < MAX_MESSAGE_SIZE, "DestroyShipMessage is too big !");
					assert(sizeof(DestroyShipMessage) == size);
					handleDestroyShipMessage((DestroyShipMessage*)MSG, machine, service);
				}
				break;

				case SHIP_SYNC_STATE:
				{
					static_assert(sizeof(SyncShipStateMessage) < MAX_MESSAGE_SIZE, "SyncShipStateMessage is too big !");
					assert(sizeof(SyncShipStateMessage) == size);
					handleSyncShipStateMessage((SyncShipStateMessage*)MSG, machine, service);
				}
				break;

				case TRANSMITTER_CREATE:
				{
					static_assert(sizeof(CreateTransmitterMessage) < MAX_MESSAGE_SIZE, "CreateTransmitterMessage is too big !");
					assert(sizeof(CreateTransmitterMessage) == size);
					handleCreateTransmitterMessage((CreateTransmitterMessage*)MSG, machine, service);
				}
				break;

				case TRANSMITTER_DESTROY:
				{
					static_assert(sizeof(DestroyTransmitterMessage) < MAX_MESSAGE_SIZE, "DestroyTransmitterMessage is too big !");
					assert(sizeof(DestroyTransmitterMessage) == size);
					handleDestroyTransmitterMessage((DestroyTransmitterMessage*)MSG, machine, service);
				}
				break;

				case TRANSMITTER_SYNC_STATE:
				{
					static_assert(sizeof(SyncTransmitterStateMessage) < MAX_MESSAGE_SIZE, "DestroyTransmitterMessage is too big !");
					assert(sizeof(SyncTransmitterStateMessage) == size);
					handleSyncTransmitterStateMessage((SyncTransmitterStateMessage*)MSG, machine, service);
				}
				break;
			}
		}
	}
}

/**
 * @brief Create Ship
 * @param x
 * @param y
 * @return new Ship
 */
Ship * World::createShip(unsigned int team, float x, float y)
{
	uuid_t uuid;
#if __gnu_linux__
	uuid_generate(uuid);
#else
	UuidCreate(&uuid);
#endif // __gnu_linux__

	Ship * ship = createShipInternal(uuid, team, x, y);

	CreateShipMessage message;
#if __gnu_linux__
	uuid_copy(message.shipId, uuid);
#else
	memcpy(&message.shipId, (void*)&uuid, sizeof(uuid_t));
#endif // __gnu_linux__
	message.position = vec2(x, y);
	message.target = vec2(x, y);
	message.speed = 0.0f;
	message.team = team;

	m_network.SendMessageToAllClients(message);

	for (int i = 0; i < MAX_SHIPS; ++i)
	{
		if (nullptr == m_aOwnedShips[i])
		{
			m_aOwnedShips[i] = ship;
			break;
		}
	}

	return(ship);
}

/**
 * @brief Create Ship
 * @param x
 * @param y
 * @return new Ship
 */
Ship * World::createShipInternal(const uuid_t & uuid, unsigned int team, float x, float y)
{
#if ENABLE_CHECKS
	{
		Ship * existingShip = findShip(uuid);
		assert(existingShip == nullptr);
	}
#endif // ENABLE_CHECKS

	Ship * ship = m_aShips + m_ShipCount;

	++m_ShipCount;

	*ship = Ship(uuid, team, x, y);

	return(ship);
}

/**
 * @brief World::findShip
 * @param uuid
 * @return
 */
Ship * World::findShip(const uuid_t & uuid)
{
	Ship * ship = nullptr;

	for (int i = 0; i < m_ShipCount; ++i)
	{
#if WIN32
		RPC_STATUS status;
		if(UuidCompare((uuid_t*)(&uuid), &m_aShips[i].m_uuid, &status) == 0)
#else // WIN32
		if (uuid_compare(uuid, m_aShips[i].m_uuid) == 0)
#endif // WIN32
		{
			ship = m_aShips+i;
			break;
		}
	}

	return(ship);
}

/**
* @brief Create Transmitter
* @param x
* @param y
* @return new Transmitter
*/
Transmitter * World::createTransmitter(unsigned int team, float x, float y)
{
	uuid_t uuid;
#if __gnu_linux__
	uuid_generate(uuid);
#else
	UuidCreate(&uuid);
#endif // __gnu_linux__

	Transmitter * transmitter = createTransmitterInternal(uuid, team, x, y);

	CreateTransmitterMessage message;
#if __gnu_linux__
	uuid_copy(message.transmitterId, uuid);
#else
	memcpy(&message.transmitterId, (void*)&uuid, sizeof(uuid_t));
#endif // __gnu_linux__
	message.position = vec2(x, y);
	message.team = team;

	m_network.SendMessageToAllClients(message);

	for (int i = 0; i < MAX_TRANSMITTERS; ++i)
	{
		if (nullptr == m_aOwnedTransmitters[i])
		{
			m_aOwnedTransmitters[i] = transmitter;
			break;
		}
	}

	return(transmitter);
}

/**
 * @brief createTransmitterInternal
 * @param uuid
 * @param x
 * @param y
 * @return
 */
Transmitter * World::createTransmitterInternal(const uuid_t & uuid, unsigned int team, float x, float y)
{
#if ENABLE_CHECKS
	{
		Transmitter * existingTransmitter = findTransmitter(uuid);
		assert(existingTransmitter == nullptr);
	}
#endif // ENABLE_CHECKS

	Transmitter * transmitter = m_aTransmitters + m_TransmitterCount;

	++m_TransmitterCount;

	*transmitter = Transmitter(uuid, team, x, y);

	return(transmitter);
}

/**
 * @brief World::findTransmitter
 * @param uuid
 * @return
 */
Transmitter * World::findTransmitter(const uuid_t & uuid)
{
	Transmitter * ship = nullptr;

	for (int i = 0; i < m_ShipCount; ++i)
	{
#if WIN32
		RPC_STATUS status;
		if(UuidCompare((uuid_t*)(&uuid), &m_aTransmitters[i].m_uuid, &status) == 0)
#else // WIN32
		if (uuid_compare(uuid, m_aTransmitters[i].m_uuid) == 0)
#endif // WIN32
		{
			ship = m_aTransmitters+i;
			break;
		}
	}

	return(ship);
}

}

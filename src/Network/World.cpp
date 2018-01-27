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
, m_halfSize(size_x, size_y)
, m_TransmitterCount(0)
, m_pListener(nullptr)
{
	memset(m_aShips, 0, sizeof(m_aShips));
	memset(m_aOwnedShips, 0, sizeof(m_aOwnedShips));
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
	HelloMessage msg;

	return(m_network.BroadcastMessage(msg));
}

/**
 * @brief World::handleHelloMessage
 */
void World::handleHelloMessage(HelloMessage * msg, char * machine, char * service)
{
	printf("HELLO from %s:%s\n", machine, service);
	fflush(stdout);

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
			response.position = vec2(0.0f, 0.0f);
			response.target = vec2(0.0f, 0.0f);
			response.speed = 0.0f;

			m_network.SendMessageToMachine(response, machine);
		}
	}

	m_network.RegisterClient(machine);
}

/**
 * @brief World::handleSyncShipStateMessage
 */
void World::handleSyncShipStateMessage(SyncShipStateMessage * msg, char * machine, char * service)
{
	printf("SYNC_SHIP_STATE from %s:%s\n", machine, service);
	fflush(stdout);

	Ship * ship = findShip(msg->shipId);

	if (!ship)
	{
		ship = createShipInternal(msg->shipId, 0.0f, 0.0f);
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
void World::handleCreateShipMessage(CreateShipMessage * msg, char * machine, char * service)
{
	printf("CREATE_SHIP from %s:%s\n", machine, service);
	fflush(stdout);

	Ship * ship = createShipInternal(msg->shipId, 0.0f, 0.0f);
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
void World::handleCreateTransmitterMessage(CreateTransmitterMessage * msg, char * machine, char * service)
{
	printf("CREATE_TRANSMITTER from %s:%s\n", machine, service);
	fflush(stdout);

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

				case SYNC_SHIP_STATE:
				{
					static_assert(sizeof(SyncShipStateMessage) < MAX_MESSAGE_SIZE, "ShipStateMessage is too big !");
					assert(sizeof(SyncShipStateMessage) == size);
					handleSyncShipStateMessage((SyncShipStateMessage*)MSG, machine, service);
				}
				break;

				case CREATE_SHIP:
				{
					static_assert(sizeof(CreateShipMessage) < MAX_MESSAGE_SIZE, "ShipStateMessage is too big !");
					assert(sizeof(CreateShipMessage) == size);
					handleCreateShipMessage((CreateShipMessage*)MSG, machine, service);
				}
				break;

				case CREATE_TRANSMITTER:
				{
					static_assert(sizeof(CreateTransmitterMessage) < MAX_MESSAGE_SIZE, "ShipStateMessage is too big !");
					assert(sizeof(CreateTransmitterMessage) == size);
					handleCreateTransmitterMessage((CreateTransmitterMessage*)MSG, machine, service);
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
Ship * World::createShip(float x, float y)
{
	uuid_t uuid;
#if __gnu_linux__
	uuid_generate(uuid);
#else
	UuidCreate(&uuid);
#endif // __gnu_linux__

	Ship * ship = createShipInternal(uuid, x, y);

	CreateShipMessage message;
#if __gnu_linux__
	uuid_copy(message.shipId, uuid);
#else
	memcpy(&message.shipId, (void*)&uuid, sizeof(uuid_t));
#endif // __gnu_linux__
	message.position = vec2(x, y);
	message.target = vec2(x, y);
	message.speed = 0.0f;

	m_network.SendMessageToAllClients(message);

	m_aOwnedShips[0] = ship; // FIXME !

	return(ship);
}

/**
 * @brief Create Ship
 * @param x
 * @param y
 * @return new Ship
 */
Ship * World::createShipInternal(const uuid_t & uuid, float x, float y)
{
#if ENABLE_CHECKS
	{
		Ship * existingShip = findShip(uuid);
		assert(existingShip == nullptr);
	}
#endif // ENABLE_CHECKS

	Ship * ship = m_aShips + m_ShipCount;

	++m_ShipCount;

	*ship = Ship(uuid, x, y);

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

	for (int i = 0; i < MAX_SHIPS; ++i)
	{
#if WIN32
		RPC_STATUS status;
		if(UuidCompare((uuid_t*)(&uuid), &m_aShips[i].m_uuid, &status) == 0)
#else // WIN32
		if (uuid_compare(uuid, m_aShips[i].m_uuid))
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

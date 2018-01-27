#pragma once

#include "utils.h"

#include "NetworkHelper.h"

#include "Ship.h"
#include "Transmitter.h"

struct sockaddr;

namespace Network
{

class WorldListener;

class World
{
public:

	//
	// Constructor / Destructor
	World				(float size_x, float size_y);
	~World				(void);

	//
	// Initialize
	bool init			(void);
	void release		(void);

	//
	// Update
	void update			(float dt);

	//
	// Create Ship
	Ship * createShip	(unsigned int team, float x, float y);
	Ship * findShip		(const uuid_t & uuid);

	//
	// Create Transmitter
	Transmitter * createTransmitter	(unsigned int team, float x, float y);
	Transmitter * findTransmitter	(const uuid_t & uuid);

	void setListener(WorldListener * pListener)
	{
		m_pListener = pListener;
	}

protected:

	Transmitter * createTransmitterInternal(const uuid_t & uuid, unsigned int team, float x, float y);
	Ship * createShipInternal(const uuid_t & uuid, unsigned int team, float x, float y);

	bool broadcastHelloMessage(void);

	void handleHelloMessage(HelloMessage * msg, char * machine, char * service);
	void handlePingMessage(PingMessage * msg, char * machine, char * service);

	void handleCreateShipMessage(CreateShipMessage * msg, char * machine, char * service);
	void handleDestroyShipMessage(DestroyShipMessage * msg, char * machine, char * service);
	void handleSyncShipStateMessage(SyncShipStateMessage * msg, char * machine, char * service);

	void handleCreateTransmitterMessage(CreateTransmitterMessage * msg, char * machine, char * service);
	void handleDestroyTransmitterMessage(DestroyTransmitterMessage * msg, char * machine, char * service);
	void handleSyncTransmitterStateMessage(SyncTransmitterStateMessage * msg, char * machine, char * service);

private:

	//
	// Ships
	static const unsigned int MAX_SHIPS = 256;
	Ship m_aShips [MAX_SHIPS];
	unsigned int m_ShipCount;
	Ship * m_aOwnedShips [MAX_SHIPS];

	//
	// Transmitters
	static const unsigned int MAX_TRANSMITTERS = 2048;
	Transmitter m_aTransmitters[MAX_TRANSMITTERS];
	unsigned int m_TransmitterCount;
	Transmitter * m_aOwnedTransmitters [MAX_TRANSMITTERS];

	//
	// ...
	vec2 m_halfSize;

	NetworkHelper m_network;

	WorldListener * m_pListener;

	uuid_t m_MyHelloUUID;
};

}

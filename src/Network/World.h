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
	Ship * createShip	(void);
	Ship * createShip	(float x, float y);

	//
	// Create Transmitter
	Transmitter * createTransmitter	(void);
	Transmitter * createTransmitter	(float x, float y);

	void setListener(WorldListener * pListener)
	{
		m_pListener = pListener;
	}

protected:

	bool broadcastHelloMessage(void);

	void handleHelloMessage(HelloMessage * msg, char * machine, char * service);
	void handleSyncShipStateMessage(SyncShipStateMessage * msg, char * machine, char * service);
	void handleCreateShipMessage(CreateShipMessage * msg, char * machine, char * service);
	void handleCreateTransmitterMessage(CreateTransmitterMessage * msg, char * machine, char * service);

private:

	static const unsigned int MAX_SHIPS = 256;
	Ship m_aShips [MAX_SHIPS];
	unsigned int m_ShipCount;

	Ship * m_aOwnedShips [MAX_SHIPS];

	static const unsigned int MAX_TRANSMITTERS = 2048;
	Transmitter m_aTransmitters[MAX_TRANSMITTERS];
	unsigned int m_TransmitterCount;

	vec2 m_halfSize;

	NetworkHelper m_network;

	WorldListener * m_pListener;
};

}

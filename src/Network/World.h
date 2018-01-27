#pragma once

#include "utils.h"

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

protected:

	bool initSocket(void);
	void releaseSocket(void);

	bool broadcastHelloMessage(void);

	void handleHelloMessage(HelloMessage * msg, struct ::sockaddr* sender, unsigned int sendsize);
	void handleSyncShipStateMessage(SyncShipStateMessage * msg, struct ::sockaddr * sender, unsigned int sendsize);
	void handleCreateShipMessage(CreateShipMessage * msg, struct ::sockaddr* sender, unsigned int sendsize);
	void handleCreateTransmitterMessage(CreateTransmitterMessage * msg, struct ::sockaddr * sender, unsigned int sendsize);

private:

	static const unsigned int MAX_SHIPS = 256;
	Ship m_aShips [MAX_SHIPS];
	unsigned int m_ShipCount;

	static const unsigned int MAX_TRANSMITTERS = 2048;
	Transmitter m_aTransmitters[MAX_TRANSMITTERS];
	unsigned int m_TransmitterCount;

	vec2 m_halfSize;

	int m_sock;

	WorldListener * m_pListener;
};

}

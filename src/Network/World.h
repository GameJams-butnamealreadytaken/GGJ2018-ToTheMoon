#pragma once

#include "Network.h"

#include "Ship.h"

struct sockaddr;

namespace Network
{

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

protected:

	bool initSocket(void);
	void releaseSocket(void);

	bool broadcastHelloMessage(void);

	void handleHelloMessage(HelloMessage * msg, struct ::sockaddr* sender, unsigned int sendsize);
	void handleShipStateMessage(ShipStateMessage * msg, struct ::sockaddr * sender, unsigned int sendsize);

private:

	static const unsigned int MAX_SHIPS = 256;

	Ship m_aShips [MAX_SHIPS];

	unsigned int m_ShipCount;

	vec2 m_halfSize;

	int m_sock;

};

}

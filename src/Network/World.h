#pragma once

#include "Network.h"

#include "Ship.h"

namespace Network
{

class World
{
public:

	//
	// Constructor / Destructor
	World(float size_x, float size_y);
	~World(void);

	//
	// Initialize
	bool init();
	void release();

	//
	// Update
	void update(float dt);

	//
	// Create Ship
	Ship * createShip(void);
	Ship * createShip(float x, float y);

protected:

private:

	static const unsigned int MAX_SHIPS = 256;

	Ship m_aShips [MAX_SHIPS];

	unsigned int m_ShipCount;

	vec2 m_halfSize;

};

}

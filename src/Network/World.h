#pragma once

#include "Ship.h"

namespace Network
{

class World
{
public:

	World();
	~World();

	void		update		(double dt);

protected:

private:

	Ship m_aShips [256];

	unsigned int m_ShipCount;

};

}

#pragma once

#include "utils.h"

namespace Network
{

class NetworkHelper;

class Ship
{
	friend class World;

public:

	//
	// Constructor / Destructor
	Ship(void);
	Ship(const uuid_t & id, unsigned int team, unsigned int eShipType);
	Ship(const uuid_t & id, unsigned int team, unsigned int eShipType, float x, float y);
	~Ship(void);

	//
	// Speed (getter / setter)
	float getSpeed(void) const
	{
		return(m_speed);
	}

	void setSpeed(float speed)
	{
		m_speed = speed;
		m_bNeedSync = true;
	}

	//
	// Target (getter / setter)
	const vec2 & getTarget(void) const
	{
		return(m_target);
	}

	void setTarget(float x, float y)
	{
		m_target.x = x;
		m_target.y = y;
		m_bNeedSync = true;
	}

	//
	// Position (getter only)
	const vec2 & getPosition(void) const
	{
		return(m_position);
	}

	//
	// Team
	unsigned int getTeam(void) const
	{
		return(m_team);
	}

	//
	// Team
	unsigned int getType(void) const
	{
		return(m_eShipType);
	}

protected:

	//
	// Update
	void update(float dt, NetworkHelper & network);

	void clampPosition(const vec2 & halfSize);

private:

	uuid_t m_uuid;

	vec2 m_position;

	vec2 m_target;

	float m_speed; // unit / s

	unsigned int m_team;

	unsigned int m_eShipType;

	bool m_bNeedSync;
};

}

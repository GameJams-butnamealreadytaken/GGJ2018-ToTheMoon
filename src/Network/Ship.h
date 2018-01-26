#pragma once

#include "Network.h"

namespace Network
{

class Ship
{
	friend class World;

public:

	//
	// Constructor / Destructor
	Ship(void);
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
	}

	//
	// Target (getter / setter)
	float getTarget(void) const
	{
		return(m_speed);
	}

	void setTarget(float x, float y)
	{
		m_target.x = x;
		m_target.y = y;
	}

	//
	// Position (getter only)
	const vec2 & getPosition(void) const
	{
		return(m_position);
	}

protected:

	//
	// Update
	void update(float dt);


private:

	vec2 m_position;

	vec2 m_target;

	float m_speed; // unit / s

};

}

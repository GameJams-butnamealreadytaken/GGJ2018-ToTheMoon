#pragma once

#include "utils.h"

namespace Network
{

class Ship
{
	friend class World;

public:

	//
	// Constructor / Destructor
	Ship(void);
	Ship(float x, float y);
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
	const vec2 & getTarget(void) const
	{
		return(m_target);
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

	void clampPosition(const vec2 & halfSize);

private:

	vec2 m_position;

	vec2 m_target;

	float m_speed; // unit / s

};

}

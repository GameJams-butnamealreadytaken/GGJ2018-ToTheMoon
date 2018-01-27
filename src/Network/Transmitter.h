#pragma once

#include "Network.h"

namespace Network
{

class Transmitter
{
	friend class World;

public:

	//
	// Constructor / Destructor
	Transmitter(void);
	Transmitter(float x, float y);
	~Transmitter(void);

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

};

}

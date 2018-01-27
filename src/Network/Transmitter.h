#pragma once

#include "utils.h"

namespace Network
{

class NetworkHelper;

class Transmitter
{
	friend class World;

public:

	//
	// Constructor / Destructor
	Transmitter(void);
	Transmitter(const uuid_t & id, float x, float y);
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
	void update(float dt, NetworkHelper & network);

private:

	uuid_t m_uuid;

	vec2 m_position;

};

}

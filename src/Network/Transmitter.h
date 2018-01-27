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
	Transmitter(const uuid_t & id, unsigned int team);
	Transmitter(const uuid_t & id, unsigned int team, float x, float y);
	~Transmitter(void);

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

protected:

	//
	// Update
	void update(float dt, NetworkHelper & network);

private:

	uuid_t m_uuid;

	vec2 m_position;

	unsigned int m_team;
};

}

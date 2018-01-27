#include "Transmitter.h"

namespace Network
{

/**
 * @brief Constructor
 */
Transmitter::Transmitter(void) : m_position(0.0f, 0.0f)
{
	// ...
}

/**
 * @brief Transmitter::Transmitter
 * @param x
 * @param y
 */
Transmitter::Transmitter(const uuid_t & id, unsigned int team) : m_position(0.0f, 0.0f), m_team(team)
{
#if __gnu_linux__
	uuid_copy(m_uuid, id);
#else
	memcpy(&m_uuid, (void*)&id, sizeof(uuid_t));
#endif // __gnu_linux__
}

/**
 * @brief Transmitter::Transmitter
 * @param x
 * @param y
 */
Transmitter::Transmitter(const uuid_t & id, unsigned int team, float x, float y) : m_position(x, y), m_team(team)
{
#if __gnu_linux__
	uuid_copy(m_uuid, id);
#else
	memcpy(&m_uuid, (void*)&id, sizeof(uuid_t));
#endif // __gnu_linux__
}

/**
 * @brief Destructor
 */
Transmitter::~Transmitter(void)
{
	// ..
}

/**
 * @brief update
 * @param delta time in seconds
 */
void Transmitter::update(float dt, NetworkHelper & network)
{
	// ...
}

}

#include "Ship.h"

namespace Network
{

/**
 * @brief Constructor
 */
Ship::Ship(void)
{
	// ...
}

/**
 * @brief Destructor
 */
Ship::~Ship(void)
{
	// ..
}

/**
 * @brief update
 * @param delta time in seconds
 */
void Ship::update(float dt)
{
	vec2 direction;
	direction.x = m_target.x - m_position.x;
	direction.y = m_target.y - m_position.y;

	m_position.x += direction.x * m_speed * dt;
	m_position.y += direction.y * m_speed * dt;
}


}

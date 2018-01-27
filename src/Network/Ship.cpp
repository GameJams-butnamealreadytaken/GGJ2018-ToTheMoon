#include "Ship.h"

namespace Network
{

/**
 * @brief Constructor
 */
Ship::Ship(void) : m_position(0.0f, 0.0f), m_target(0.0f, 0.0f), m_speed(0.0f)
{
	// ...
}

/**
 * @brief Ship::Ship
 * @param x
 * @param y
 */
Ship::Ship(float x, float y) : m_position(x, y), m_target(x, y), m_speed(0.0f)
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

/**
 * @brief Clamp position
 * @param halfSize
 */
void Ship::clampPosition(const vec2 & halfSize)
{
	//
	// Clamp X
	if (m_position.x > halfSize.x)
	{
		m_position.x = halfSize.x;
	}
	else if (m_position.x < -halfSize.x)
	{
		m_position.x = halfSize.x;
	}

	//
	// Clamp Y
	if (m_position.y > halfSize.y)
	{
		m_position.y = halfSize.y;
	}
	else if (m_position.y < -halfSize.y)
	{
		m_position.y = halfSize.y;
	}
}



}

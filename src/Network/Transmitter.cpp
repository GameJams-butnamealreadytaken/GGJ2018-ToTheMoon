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
Transmitter::Transmitter(float x, float y) : m_position(x, y)
{
	// ...
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
void Transmitter::update(float dt)
{

}

}

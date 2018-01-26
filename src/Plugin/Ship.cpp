#include "Ship.h"

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
	// ...
}

/**
* @brief Initialize
*/
void Ship::Initialize(ShObject * pSprite, EBlockType type)
{
	m_type = type;
	m_pSprite = pSprite;
}

/**
* @brief Release
*/
void Ship::Release(void)
{
	m_pBody = shNULL;
	m_pSprite = shNULL;
}

/**
* @brief GetType
*/
Ship::EBlockType Ship::GetType(void)
{
	return(m_type);
}

/**
* @brief GetSprite
*/
ShObject * Ship::GetSprite(void)
{
	return(m_pSprite);
}

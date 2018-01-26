#include "Ship.h"

/**
 * @brief Constructor
 */
Ship::Ship(ShEntity2 * pEntity, const CShVector2 & vPosition)
	: GameObject(pEntity, vPosition)
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
void Ship::Initialize(ShObject * pSprite, EShipType type)
{
	m_type = type;
}

/**
* @brief Release
*/
void Ship::Release(void)
{
}

/**
* @brief GetType
*/
Ship::EShipType Ship::GetType(void)
{
	return(m_type);
}

#include "Ship.h"

/**
 * @brief Constructor
 */
Ship::Ship(ShEntity2 * pEntity, const CShVector2 & vPosition)
	: GameObject(pEntity, vPosition)
	, m_eState(IDLE)
	, m_Destination()
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
* @brief Update
*/
void Ship::Update(float dt)
{
	switch (m_eState)
	{
	case IDLE:
		{

		}
		break;

	case TRAVEL:
		{

		}
		break;

	case FIGHT:
		{

		}
		break;
	}
}

/**
* @brief GetType
*/
Ship::EShipType Ship::GetType(void)
{
	return(m_type);
}

void Ship::SetDestination(const CShVector2 & newDest)
{
	m_Destination = newDest;
}

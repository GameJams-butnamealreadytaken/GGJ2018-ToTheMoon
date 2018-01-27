#include "Ship.h"

/**
 * @brief Constructor
 */
Ship::Ship(ShEntity2 * pEntity, const CShVector2 & vPosition)
	: GameObject(pEntity, vPosition)
{
	SetState((int)IDLE);
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
void Ship::Initialize(EShipType type, Network::Ship * pNetworkShipIN)
{
	m_type = type;
	pNetworkShip = pNetworkShipIN;
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
	switch (m_iState)
	{
	case IDLE:
		{

		}
		break;

	case TRAVEL:
		{
			// check if is on target
			// setSpeed à 0 & setState à Idle si pos, FIGHT sinon
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

/**
* @brief SetTarget
*/
void Ship::SetTarget(const CShVector2 & newTarget, float fSpeed)
{
	pNetworkShip->setTarget(newTarget.m_x, newTarget.m_y);
	pNetworkShip->setSpeed(fSpeed);
	SetState((int)TRAVEL);
}

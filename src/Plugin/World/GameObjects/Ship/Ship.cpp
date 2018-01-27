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
	pNetworkShip->setSpeed(0.0f);
}

/**
* @brief Release
*/
void Ship::Release(void)
{
	pNetworkShip = shNULL;
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
			UpdateSprite();
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

void Ship::UpdateSprite(void)
{
	// Sprite rotation
	CShVector2 curentPos = ShEntity2::GetWorldPosition2(m_pEntity);
	Network::vec2 shipPos = pNetworkShip->getPosition();
	float direction = atan2(shipPos.x - curentPos.m_x, shipPos.y - curentPos.m_y) * 180 / SHC_PI;
	bool needPI = false;
	float orientation = (-direction + 90)*SHC_DEG2RAD;

	ShEntity2::SetWorldRotation(m_pEntity, 0.0f, 0.0f, orientation);

	// Sprite pos
	ShEntity2::SetWorldPosition(m_pEntity, CShVector3(shipPos.x, shipPos.y, ShEntity2::GetWorldPositionZ(m_pEntity)));
}

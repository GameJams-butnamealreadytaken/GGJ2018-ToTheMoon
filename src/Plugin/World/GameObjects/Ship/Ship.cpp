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
void Ship::Initialize(EShipType type, Network::World & world)
{
	m_type = type;
	pNetworkShip = world.createShip();
	pNetworkShip->setSpeed(0.0f); 
	SetShow(true);
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

/*virtual*/ void Ship::OnHit(GameObject* pObject)
{

}

/**
* @brief GetType
*/
Ship::EShipType Ship::GetShipType(void)
{
	return(m_type);
}

/**
* @brief SetTarget
*/
void Ship::SetTarget(float x, float y, float fSpeed)
{
	pNetworkShip->setTarget(x, y);
	pNetworkShip->setSpeed(fSpeed);
	SetState((int)TRAVEL);
}

void Ship::UpdateSprite(void)
{
	// Sprite rotation
	Network::vec2 shipPos = pNetworkShip->getPosition();
	Network::vec2 targetPos = pNetworkShip->getTarget();
	
	float direction = atan2(targetPos.x - shipPos.x, targetPos.y - shipPos.y) * 180 / SHC_PI;
	float orientation = (-direction + 90)*SHC_DEG2RAD;

	ShEntity2::SetWorldRotation(m_pEntity, 0.0f, 0.0f, orientation);

	// Sprite pos
	ShEntity2::SetWorldPosition(m_pEntity, CShVector3(shipPos.x, shipPos.y, ShEntity2::GetWorldPositionZ(m_pEntity)));
}

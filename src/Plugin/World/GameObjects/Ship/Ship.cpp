#include "Ship.h"

/**
 * @brief Constructor
 */
Ship::Ship(ShEntity2 * pEntity, const CShVector2 & vPosition)
	: GameObject(pEntity, vPosition)
	, m_pNetworkShip(shNULL)
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
void Ship::Initialize(EShipType type, const Network::Ship * pNetworkShip)
{
	m_type = type;
	m_pNetworkShip = const_cast<Network::Ship *>(pNetworkShip);
	m_pNetworkShip->setSpeed(0.0f);
	SetShow(true);
}

/**
* @brief Release
*/
void Ship::Release(void)
{
	m_pNetworkShip = shNULL;
}

/**
* @brief Update
*/
void Ship::Update(float dt)
{
	UpdateSprite();

	switch (m_iState)
	{
	case IDLE:
		{

		}
		break;

	case TRAVEL:
		{
			{
				const Network::vec2 & targetPos = m_pNetworkShip->getTarget();

				if (6.0f > ComputeVecteurNorme(m_vPosition.m_x, m_vPosition.m_y, targetPos.x, targetPos.y))
				{
					// setSpeed à 0 & setState à Idle si pos, FIGHT sinon
					m_pNetworkShip->setSpeed(0.0f);
					SetState((int)IDLE);
				}

			}
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
	m_pNetworkShip->setTarget(x, y);
	m_pNetworkShip->setSpeed(fSpeed);
	SetState((int)TRAVEL);
}

/**
* @brief GameObject::UpdateSprite
*/
void Ship::UpdateSprite(void)
{
	// Sprite rotation
	const Network::vec2 & shipPos = m_pNetworkShip->getPosition();
	const Network::vec2 & targetPos = m_pNetworkShip->getTarget();
	
	float direction = atan2(targetPos.x - shipPos.x, targetPos.y - shipPos.y) * 180 / SHC_PI;
	float orientation = (-direction + 90)*SHC_DEG2RAD;

	ShEntity2::SetWorldRotation(m_pEntity, 0.0f, 0.0f, orientation);

	// Sprite pos
	m_vPosition.m_x = shipPos.x;
	m_vPosition.m_y = shipPos.y;
	ShEntity2::SetWorldPosition(m_pEntity, CShVector3(shipPos.x, shipPos.y, ShEntity2::GetWorldPositionZ(m_pEntity)));
}

float Ship::ComputeVecteurNorme(float Ax, float Ay, float Bx, float By)
{
	return sqrt(((Bx - Ax)*(Bx - Ax)) + ((By - Ay)*(By - Ay)));
}

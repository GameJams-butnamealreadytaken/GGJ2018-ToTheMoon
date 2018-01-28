#include "Ship.h"

#include "../Projectile/ProjectileManager.h"
#include "../Transmitter/Transmitter.h"

/**
 * @brief Constructor
 */
Ship::Ship(ShEntity2 * pEntity, const CShVector2 & vPosition)
	: GameObject(pEntity, vPosition)
	, m_pNetworkShip(shNULL)
	, m_fAngle(0.0f)
	, m_pProjectileManager(shNULL)
	, m_fFireRate(0.0f)
	, m_pTargetObject(shNULL)
	, m_pTargetType(e_type_void)
	, m_fAttackRange(10.0f)
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
void Ship::Initialize(EShipType type, const Network::Ship * pNetworkShip, ProjectileManager * pProjectileManager)
{
	m_type = type;
	m_pNetworkShip = const_cast<Network::Ship *>(pNetworkShip);
	m_pNetworkShip->setSpeed(0.0f);
	m_pProjectileManager = pProjectileManager;
	SetShow(true);
}

/**
* @brief Release
*/
void Ship::Release(void)
{
	m_pNetworkShip = shNULL;
	ShEntity2::Destroy(m_pEntity);
	m_pEntity = shNULL;
}

/**
* @brief Update
*/
void Ship::Update(float dt)
{
	// Sprite rotation
	const Network::vec2 & shipPos = m_pNetworkShip->getPosition();
	const Network::vec2 & targetPos = m_pNetworkShip->getTarget();

	UpdateSprite(shipPos);

	m_fFireRate += dt;

	switch (m_type)
	{
		case BASE :
		{
			if (m_fFireRate > 0.5f)
			{
				m_pProjectileManager->Start(ProjectileManager::e_projectile_bullet, GetPosition2(), GetPosition2() + CShVector2(cos(m_fAngle) * 1500.0f, sin(m_fAngle) * 1500.0f), 2.0f);
				m_fFireRate = 0.0f;
			}
		}
		break;

		case TANK :
		{
			if (m_fFireRate > 0.5f)
			{
				m_pProjectileManager->Start(ProjectileManager::e_projectile_bullet, GetPosition2(), GetPosition2() + CShVector2(cos(m_fAngle) * 1500.0f, sin(m_fAngle) * 1500.0f), 4.0f);
				m_fFireRate = 0.0f;
			}
		}
		break;

		case TRORAPIDE : 
		{

		}
		break;

		case PERE_NOWEL : 
		{

		}
		break;
	}

	switch (m_iState)
	{
	case IDLE:
		{

		}
		break;

	case TRAVEL:
		{
			const Network::vec2 & targetPos = m_pNetworkShip->getTarget();

			if (m_fAttackRange > ComputeVecteurNorme(m_vPosition.m_x, m_vPosition.m_y, targetPos.x, targetPos.y))
			{
				m_pNetworkShip->setSpeed(0.0f);
				SetState((int)IDLE);

				if (e_type_ship == m_pTargetType)
				{
					// Attack
				}
				else if (e_type_transmitter == m_pTargetType)
				{
					// Attack
				}

				m_pTargetType = e_type_void;
				m_pTargetObject = shNULL;
			}
		}
		break;

	case FIGHT:
		{

		}
		break;
	}
}

/**
* @brief OnHit
*/
/*virtual*/ void Ship::OnHit(GameObject* pObject)
{

}

/**
* @brief GetType
*/
Ship::EShipType Ship::GetShipType(void) const
{
	return(m_type);
}

/**
* @brief GetType
*/
unsigned int Ship::GetTeam(void) const
{
	return(m_pNetworkShip->getTeam());
}

/**
* @brief GetNetworkShip
*/
Network::Ship * Ship::GetNetworkShip(void) const
{
	return(m_pNetworkShip);
}

/**
* @brief SetTarget
*/
void Ship::SetTarget(float x, float y, float fSpeed)
{
	m_pNetworkShip->setTarget(x, y);
	m_pNetworkShip->setSpeed(fSpeed);

	const Network::vec2 & shipPos = m_pNetworkShip->getPosition();
	const Network::vec2 & targetPos = m_pNetworkShip->getTarget();

	float direction = atan2(targetPos.x - shipPos.x, targetPos.y - shipPos.y) * 180 / SHC_PI;
	m_fAngle = (-direction + 90)*SHC_DEG2RAD;

	ShEntity2::SetWorldRotation(m_pEntity, CShEulerAngles(0.0f, 0.0f, m_fAngle));

	SetState((int)TRAVEL);
}

/**
* @brief SetTarget
*/
void Ship::SetTarget(float x, float y, float fSpeed, Ship * pShip)
{
	SetTarget(x, y, fSpeed);
	m_pTargetType = e_type_ship;
	m_pTargetObject = pShip;
	m_fAttackRange = 200.0f;
}

/**
* @brief SetTarget
*/
void Ship::SetTarget(float x, float y, float fSpeed, Transmitter * pTrans)
{
	SetTarget(x, y, fSpeed);
	m_pTargetType = e_type_transmitter;
	m_pTargetObject = pTrans;
	m_fAttackRange = 200.0f;
}

/**
* @brief GameObject::GetRotationZ
*/
CShEulerAngles Ship::GetRotation(void)
{
	return(ShEntity2::GetWorldRotation(m_pEntity));
}

/**
* @brief GameObject::UpdateSprite
*/
void Ship::UpdateSprite(const Network::vec2 & shipPos)
{
	// Sprite pos
	m_vPosition.m_x = shipPos.x;
	m_vPosition.m_y = shipPos.y;
	ShEntity2::SetWorldPosition(m_pEntity, CShVector3(shipPos.x, shipPos.y, ShEntity2::GetWorldPositionZ(m_pEntity)));
}

float Ship::ComputeVecteurNorme(float Ax, float Ay, float Bx, float By)
{
	return sqrt(((Bx - Ax)*(Bx - Ax)) + ((By - Ay)*(By - Ay)));
}

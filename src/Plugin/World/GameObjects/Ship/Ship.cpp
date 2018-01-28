#include "Ship.h"

#include "../Projectile/ProjectileManager.h"
#include "../Transmitter/Transmitter.h"
#include "../../World.h"

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
	, m_fAttackRange(30.0f)
	, m_iLife(100)
	, m_fSpeed(800.0f)
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

	m_fFireRate += dt;

	UpdateSprite(shipPos);
	UpdateTarget();

	switch (m_iState)
	{
	case IDLE:
		{
		}
		break;

	case TRAVEL:
		{
			if (m_fAttackRange > World::ComputeVecteurNorme(m_vPosition.m_x, m_vPosition.m_y, targetPos.x, targetPos.y))
			{
				if (e_type_ship == m_pTargetType)
				{
					Attack();
					if (static_cast<Ship *>(m_pTargetObject)->IsDead())
					{
						SetIdleState();
					}
				}
				else if (e_type_transmitter == m_pTargetType)
				{
					Attack();
					if (static_cast<Transmitter *>(m_pTargetObject)->IsDead())
					{
						SetIdleState();
					}
				}
				else
				{
					SetIdleState();
				}
			}
		}
		break;

		case HIT:
		{
			SetState((int)TRAVEL);
		}
		break;

		case DESTROYED:
		{
			if (m_fStateTime < 1.0f)
			{
				ShEntity2::SetAlpha(m_pEntity, 1.0f - m_fStateTime);
			}
			else
			{
				// Dead trigger respawn
				// recreate ship on it
			}
		}
		break;
	}
}

/**
* @brief OnHit
*/
/*virtual*/ void Ship::OnHit(GameObject* pObject)
{
	--m_iLife;
	if (m_iLife <= 0)
	{
		SetState((int)DESTROYED);
		Network::DestroyTransmitterMessage(m_pTransmitter);
	}
	else
	{
		SetState((int)HIT);
	}
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
* @brief GetNetworkShip
*/
unsigned int Ship::GetLife(void) const
{
	return(m_iLife);
}

/**
* @brief GetNetworkShip
*/
unsigned int Ship::GetMaxLife(void) const
{
	return(m_iMaxLife);
}

bool Ship::IsDead(void)
{
	return(m_iLife <= 0);
}

/**
* @brief SetTarget
*/
void Ship::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
	ShEntity2::SetWorldRotation(m_pEntity, CShEulerAngles(0.0f, 0.0f, m_fAngle));
}

/**
* @brief SetTarget
*/
void Ship::SetTarget(float x, float y)
{
	m_pNetworkShip->setTarget(x, y);
	m_pNetworkShip->setSpeed(m_fSpeed);

	const Network::vec2 & shipPos = m_pNetworkShip->getPosition();
	const Network::vec2 & targetPos = m_pNetworkShip->getTarget();

	float direction = atan2(targetPos.x - shipPos.x, targetPos.y - shipPos.y) * 180 / SHC_PI;
	m_fAngle = (-direction + 90)*SHC_DEG2RAD;

	ShEntity2::SetWorldRotation(m_pEntity, CShEulerAngles(0.0f, 0.0f, m_fAngle));

	SetState((int)TRAVEL);

	if (e_type_void == m_pTargetType)
	{
		m_pTargetObject = shNULL;
	}
}

/**
* @brief SetTarget
*/
void Ship::SetTarget(float x, float y, Ship * pShip)
{
	m_pTargetType = e_type_ship;
	m_pTargetObject = pShip;
	m_fAttackRange = 600.0f;

	SetTarget(x, y);
}

/**
* @brief SetTarget
*/
void Ship::SetTarget(float x, float y, Transmitter * pTrans)
{
	m_pTargetType = e_type_transmitter;
	m_pTargetObject = pTrans;
	m_fAttackRange = 600.0f;

	SetTarget(x, y);

	ShEntity2::SetAlpha(pTrans->GetSprite(), 0.5f);
}

void Ship::SetVoidTarget(float x, float y)
{
	m_pTargetType = e_type_void;
	m_pTargetObject = shNULL;
	m_fAttackRange = 30.0f;
	SetTarget(x, y);
}

/**
* @brief GameObject::GetRotationZ
*/
CShEulerAngles Ship::GetRotation(void)
{
	return(ShEntity2::GetWorldRotation(m_pEntity));
}

void Ship::SetIdleState(void)
{
	m_pNetworkShip->setSpeed(0.0f);
	SetState((int)IDLE);
	m_pTargetType = e_type_void;
	m_pTargetObject = shNULL;
	m_fAttackRange = 30.0f;
}

/**
* @brief GameObject::UpdateSprite
*/
void Ship::Attack(void)
{
	m_pNetworkShip->setSpeed(0.0f);

	CShVector2 & vTargetPosition2 = m_pTargetObject->GetPosition2();

	static bool bLeft = true;

	if (m_fFireRate > 0.25f)
	{
		float direction = atan2(vTargetPosition2.m_x - GetPosition2().m_x, vTargetPosition2.m_y - GetPosition2().m_y) * 180 / SHC_PI;
		float fAngle = (-direction + 90)*SHC_DEG2RAD;

		if (bLeft)
		{
			m_pProjectileManager->Start(ProjectileManager::e_projectile_bullet, GetPosition2() + 10.0f * CShVector2(cos(fAngle), sin(fAngle)), vTargetPosition2, 4.0f);
		}
		else
		{
			m_pProjectileManager->Start(ProjectileManager::e_projectile_bullet, GetPosition2() + 10.0f * CShVector2(cos(fAngle - 0.01f), sin(fAngle - 0.01f)), vTargetPosition2, 4.0f);
		}

		bLeft = !bLeft;
		m_fFireRate = 0.0f;

		m_pTargetObject->OnHit(this);
	}
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

void Ship::UpdateTarget(void)
{
	if (e_type_ship == m_pTargetType)
	{
		if (static_cast<Ship *>(m_pTargetObject)->IsDead())
		{
			SetIdleState();
		}
		else
		{
			CShVector2 targetPos =  m_pTargetObject->GetPosition2();
			SetTarget(targetPos.m_x, targetPos.m_y);
		}
	}
	else if (e_type_transmitter == m_pTargetType)
	{
		if (static_cast<Transmitter *>(m_pTargetObject)->IsDead())
		{
			SetIdleState();
		}
	}
}

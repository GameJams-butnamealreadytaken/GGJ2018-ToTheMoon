#include "Ship.h"

/**
 * @brief Constructor
 */
Ship::Ship(ShEntity2 * pEntity, const CShVector2 & vPosition)
	: GameObject(pEntity, vPosition)
	, m_target()
	, m_fSpeed(5.0f)
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
void Ship::Initialize(EShipType type)
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
	switch (m_iState)
	{
	case IDLE:
		{

		}
		break;

	case TRAVEL:
		{
			AdjustDirectionToTarget();
			ShEntity2::Translate(m_pEntity, CShVector3(m_orientation, ShEntity2::GetWorldPositionZ(m_pEntity)));
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

void Ship::SetTarget(const CShVector2 & newTarget)
{
	m_target = newTarget;
	SetState((int)TRAVEL);
}

void Ship::AdjustDirectionToTarget(void)
{
	// rotation sprite
	CShVector2 curentPos = ShEntity2::GetWorldPosition2(m_pEntity);
	float direction = atan2(m_target.m_x - curentPos.m_x, m_target.m_y - curentPos.m_y) * 180 / SHC_PI;
	bool needPI = false;
	float orientation = (-direction + 90)*SHC_DEG2RAD;

	ShEntity2::SetWorldRotation(m_pEntity, 0.0f, 0.0f, orientation);

	float u_x = m_target.m_x - curentPos.m_x, u_y = m_target.m_y - curentPos.m_y;

	float u = sqrt((u_x*u_x) + (u_y*u_y));
	float v_x = (1 / u) * u_x;
	float v_y = (1 / u) * u_y;

	m_orientation.m_x = v_x;
	m_orientation.m_y = v_y;
}

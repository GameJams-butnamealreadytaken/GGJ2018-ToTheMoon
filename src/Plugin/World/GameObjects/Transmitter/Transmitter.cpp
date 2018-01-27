#include "Transmitter.h"

#define RADIUS 100.0f
#define LIFE 10

/**
 * @brief Constructor
 */
Transmitter::Transmitter(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
, m_fRadius(RADIUS)
, m_pTransmitter(shNULL)
{
	SetState((int)OFF);
}

/**
 * @brief Destructor
 */
Transmitter::~Transmitter(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Transmitter::Initialize(Network::World & world)
{
	m_pTransmitter = world.createTransmitter(m_vPosition.m_x, m_vPosition.m_y);
	SetShow(true);
}

/**
* @brief Release
*/
void Transmitter::Release(void)
{
	m_pTransmitter = shNULL;
}

/**
* @brief Start
*/
void Transmitter::Start(const CShVector2 & vPosition)
{
	SetPosition2(vPosition);
	SetState((int)APPEAR);
	SetShow(true);
}

/**
* @brief Update
*/
void Transmitter::Update(float dt)
{
	GameObject::Update(dt);

	switch (m_iState)
	{
		case APPEAR:
		{
			if (m_fStateTime < 1.0f)
			{
				ShEntity2::SetAlpha(m_pEntity, m_fStateTime);
			}
			else
			{
				SetState((int)IDLE);
			}
		}
		break;

		case HIT:
		{
			SetState((int)IDLE);
		}
		break;

		case IDLE:
		{

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
				SetState((int)OFF);
			}
		}
		break;
	}
}

/**
* @brief OnHit
*/
/*virtual*/ void Transmitter::OnHit(GameObject* pObject)
{
	m_iLife -= 1; // TODO

	if (m_iLife <= 0)
	{
		SetState(DESTROYED);
	}
	else
	{
		SetState((int)HIT);
	}
}

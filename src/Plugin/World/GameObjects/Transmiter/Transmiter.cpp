#include "Transmiter.h"

#define RADIUS 100.0f
#define LIFE 10

/**
 * @brief Constructor
 */
Transmiter::Transmiter(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
, m_fRadius(RADIUS)
, m_pTransmitter(shNULL)
{
	SetState((int)OFF);
}

/**
 * @brief Destructor
 */
Transmiter::~Transmiter(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Transmiter::Initialize(Network::World & world)
{
	m_pTransmitter = world.createTransmitter();
	SetShow(true);
}

/**
* @brief Release
*/
void Transmiter::Release(void)
{
	m_pTransmitter = shNULL;
}

/**
* @brief Start
*/
void Transmiter::Start(const CShVector2 & vPosition)
{
	SetPosition2(vPosition);
	SetState((int)APPEAR);
	SetShow(true);
}

/**
* @brief Update
*/
void Transmiter::Update(float dt)
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
/*virtual*/ void Transmiter::OnHit(GameObject* pObject)
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

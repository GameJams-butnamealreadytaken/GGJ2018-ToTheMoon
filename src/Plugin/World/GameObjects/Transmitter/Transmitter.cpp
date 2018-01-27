#include "Transmitter.h"

extern bool g_bDisableAnimations;

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
	if (!g_bDisableAnimations)
	{
		m_animationManagerDeploy = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("transmitter"), CShVector2(0.0f, 0.0f), 0.03f, 75, false, true);
	}

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
void Transmitter::Initialize(const Network::Transmitter * pNetworkTransmitter)
{
	m_pTransmitter = const_cast<Network::Transmitter *>(pNetworkTransmitter);
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
	if (!g_bDisableAnimations)
	{
		m_animationManagerDeploy.Play();
	}
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

	m_animationManagerDeploy.Update(dt);

	switch (m_iState)
	{
		case APPEAR:
		{
			if (g_bDisableAnimations)
			{

				SetState((int)IDLE);
			}
			else
			{
				if (!m_animationManagerDeploy.IsPlaying())
				{
					SetState((int)IDLE);
				}
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

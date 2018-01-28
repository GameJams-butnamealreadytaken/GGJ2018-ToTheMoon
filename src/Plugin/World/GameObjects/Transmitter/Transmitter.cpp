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
, m_aNeighbour()
, m_aPrimitives()
{
	if (!g_bDisableAnimations)
	{
		m_animationManagerDeploy = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("transmitter"), CShVector2(0.5f, 0.5f), 0.03f, 75, false, true);
		m_animationManagerIdleRed = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("transmitter_idle_red"), CShVector2(0.5f, 0.5f), 0.03f, 75, false, false);
		m_animationManagerIdleBlue = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("transmitter_idle_blue"), CShVector2(0.5f, 0.5f), 0.03f, 75, false, false);
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
void Transmitter::Initialize(const Network::Transmitter * pNetworkTransmitter, int id)
{
	m_id = id;
	m_pTransmitter = const_cast<Network::Transmitter *>(pNetworkTransmitter);
	SetShow(true);
}

/**
* @brief Release
*/
void Transmitter::Release(void)
{
	m_pTransmitter = shNULL;

	int nNeighboorCount = m_aNeighbour.GetCount();
	for (int i = 0; i < nNeighboorCount; ++i)
	{
		int nPrimitiveCount = m_aPrimitives.GetCount();
		for (int j = 0; j < nPrimitiveCount; ++j)
		{
			m_aNeighbour[i]->RemoveNeighbour(this, m_aPrimitives[j]);
		}
	}
	m_aNeighbour.Empty();

	int nPrimitiveCount = m_aPrimitives.GetCount();
	for (int j = 0; j < nPrimitiveCount; ++j)
	{
		ShPrimitiveSegment::Destroy(m_aPrimitives[j]);
	}
	m_aPrimitives.Empty();
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
					if (GetTeam() == 0)
					{
						m_pCurrentAnimationIdle = &m_animationManagerIdleBlue;
					}
					else if (GetTeam() == 1)
					{
						m_pCurrentAnimationIdle = &m_animationManagerIdleRed;
					}
					else
					{
						SH_ASSERT_ALWAYS();
					}

					m_pCurrentAnimationIdle->Play();
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
			if (!g_bDisableAnimations)
			{
				m_pCurrentAnimationIdle->Update(dt);
			}
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

/**
* @brief AddNeighbour
*/
void Transmitter::AddNeighbour(Transmitter * pTrans, ShPrimitiveSegment * pSegment)
{
	SH_ASSERT(shNULL != pTrans);
	m_aNeighbour.Add(pTrans);
	m_aPrimitives.Add(pSegment);
}

/**
* @brief RemoveNeighbour
*/
void Transmitter::RemoveNeighbour(Transmitter * pTrans, ShPrimitiveSegment * pSegment)
{
	SH_ASSERT(shNULL != pTrans);
	m_aNeighbour.RemoveAll(pTrans);
	SH_ASSERT(shNULL != pSegment);
	m_aPrimitives.RemoveAll(pSegment);
}

int Transmitter::GetNeighbourCount(void)
{
	return(m_aNeighbour.GetCount());
}

Transmitter * Transmitter::GetNeighbour(int id)
{
	SH_ASSERT(id < m_aNeighbour.GetCount());
	return(m_aNeighbour[id]);
}

int Transmitter::GetId(void)
{
	return(m_id);
}

/**
* @brief GetTeam
*/
unsigned int Transmitter::GetTeam(void) const
{
	return(m_pTransmitter->getTeam());
}

Network::Transmitter * Transmitter::GetNetworkTrans(void) const
{
	return(m_pTransmitter);
}

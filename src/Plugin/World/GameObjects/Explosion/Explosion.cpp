#include "Explosion.h"

extern bool g_bDisableAnimations;

/**
 * @brief Constructor
 */
Explosion::Explosion(ShEntity2 * pEntity)
: GameObject(pEntity, CShVector2(0.0f, 0.0f))
{
	if (!g_bDisableAnimations)
	{
		m_animationManager = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("explosion"), CShVector2(0.5f, 0.5f), 0.1f, 9, false, true);
	}

	SetState((int)OFF);
}

/**
 * @brief Destructor
 */
Explosion::~Explosion(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Explosion::Initialize(void)
{

}

/**
* @brief Release
*/
void Explosion::Release(void)
{

}

/**
* @brief Start
*/
void Explosion::Start(const CShVector2 & vPosition)
{
	if (!g_bDisableAnimations)
	{
		SetState((int)ON);
		SetShow(true);
		SetPosition2(vPosition);
	
		m_animationManager.Play();
	}
}

void Explosion::Stop(void)
{
	SetShow(false);
	SetState((int)OFF);
}

/**
* @brief Update
*/
void Explosion::Update(float dt)
{
	GameObject::Update(dt);

	if (!g_bDisableAnimations)
	{
		if (m_iState == ON)
		{
			if (m_animationManager.IsPlaying())
			{
				m_animationManager.Update(dt);
			}
			else
			{
				Stop();
			}
		}
	}
}
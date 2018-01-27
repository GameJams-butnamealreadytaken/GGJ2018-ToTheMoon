#include "Explosion.h"

/**
 * @brief Constructor
 */
Explosion::Explosion(ShEntity2 * pEntity)
: GameObject(pEntity, CShVector2(0.0f, 0.0f))
{
	Animate(9, "ggj", "explosion", 0.1f, true);
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
	m_bAnimationEnded = false;

	SetState((int)ON);
	SetShow(true);
	SetPosition2(vPosition);
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

	if (m_iState == ON)
	{
		if (m_bAnimationEnded)
		{
			Stop();
		}
	}
}
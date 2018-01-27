#include "Explosion.h"

extern bool g_bDisableAnimations;

/**
 * @brief Constructor
 */
Explosion::Explosion(ShEntity2 * pEntity)
: GameObject(pEntity, CShVector2(0.0f, 0.0f))
{
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
}
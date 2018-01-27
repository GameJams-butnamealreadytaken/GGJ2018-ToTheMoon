#include "Explosion.h"

/**
 * @brief Constructor
 */
Explosion::Explosion(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
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
	
}
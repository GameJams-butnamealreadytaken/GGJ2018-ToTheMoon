#include "Bullet.h"

/**
 * @brief Constructor
 */
Bullet::Bullet(ShEntity2 * pEntity)
: Projectile(pEntity, CShVector2(0.0f,0.0f))
{

}

/**
 * @brief Destructor
 */
Bullet::~Bullet(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Bullet::Initialize(void)
{

}

/**
* @brief Release
*/
void Bullet::Release(void)
{

}

/**
* @brief OnHit
*/
/*virtual*/ void Bullet::OnHit(GameObject* pObject)
{

}
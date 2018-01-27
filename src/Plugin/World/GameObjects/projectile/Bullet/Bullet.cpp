#include "Bullet.h"

/**
 * @brief Constructor
 */
Bullet::Bullet(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
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
* @brief Update
*/
/*virtual*/ void Bullet::Update(float dt)
{

}

/**
* @brief OnHit
*/
/*virtual*/ void Bullet::OnHit(GameObject* pObject)
{

}
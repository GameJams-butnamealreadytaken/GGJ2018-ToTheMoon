#include "ProjectileManager.h"

/**
 * @brief Constructor
 */
ProjectileManager::ProjectileManager(void)
{

}

/**
 * @brief Destructor
 */
ProjectileManager::~ProjectileManager(void)
{
	// ...
}

/**
* @brief Initialize
*/
void ProjectileManager::Initialize(const CShIdentifier & levelIdentifier)
{
	for (int iBullet = 0; iBullet < POOL_BULLET; ++iBullet)
	{
		ShEntity2* pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("bullet"), CShVector3(0.0f, 0.0f, 0.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
		m_apBullet[iBullet] = new Bullet(pEntity);
	}
}

/**
* @brief Release
*/
void ProjectileManager::Release(void)
{

}

/**
* @brief Start
*/
void ProjectileManager::Start(const CShVector2 & vPosition, const CShVector2 & vDestination, const CShVector2 & vSpeed)
{
	
}

/**
* @brief Update
*/
void ProjectileManager::Update(float dt)
{
	for (int iBullet = 0; iBullet < POOL_BULLET; ++iBullet)
	{
		Bullet* pBullet = m_apBullet[iBullet];
		pBullet->Update(dt);
	}
}
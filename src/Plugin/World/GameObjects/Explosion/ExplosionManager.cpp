#include "ExplosionManager.h"
#include "Explosion.h"

/**
 * @brief Constructor
 */
ExplosionManager::ExplosionManager(void)
{

}

/**
 * @brief Destructor
 */
ExplosionManager::~ExplosionManager(void)
{
	// ...
}

/**
* @brief Initialize
*/
void ExplosionManager::Initialize(const CShIdentifier & levelIdentifier)
{
	m_iCurrentExplosion = 0;

	for (int iExplosion = 0; iExplosion < POOL_EXPLOSION; ++iExplosion)
	{
		switch (iExplosion)
		{
			ShEntity2* pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("explosion_01"), CShVector3(0.0f, 0.0f, 0.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_apExplosion[iExplosion] = new Explosion(pEntity);
		}
			
	}
}

/**
* @brief Release
*/
void ExplosionManager::Release(void)
{

}

/**
* @brief Start
*/
void ExplosionManager::Start(const CShVector2 & vPosition)
{
	m_apExplosion[m_iCurrentExplosion]->Start(vPosition);
	m_iCurrentExplosion++;
	m_iCurrentExplosion %= POOL_EXPLOSION;
}

/**
* @brief Update
*/
void ExplosionManager::Update(float dt)
{
	for (int iExplosion = 0; iExplosion < POOL_EXPLOSION; ++iExplosion)
	{
		Explosion* pExplosion = m_apExplosion[iExplosion];
		pExplosion->Update(dt);
	}
}
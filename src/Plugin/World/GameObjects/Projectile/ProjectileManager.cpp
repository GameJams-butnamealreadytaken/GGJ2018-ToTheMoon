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
	for (int iProjectile = 0; iProjectile < e_projectile_max; ++iProjectile)
	{
		m_aiCurrentProjectile[iProjectile] = 0;
	}

	for (int iProjectile = 0; iProjectile < e_projectile_max; ++iProjectile)
	{
		ShEntity2* pEntity = shNULL;

		for (int j = 0; j < POOL_PROJECTILE; ++j)
		{
			switch (iProjectile)
			{
				case e_projectile_bullet:
				{
					pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("bullet"), CShVector3(0.0f, 0.0f, 0.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
					m_apProjectile[iProjectile][j] = new Bullet(pEntity);
				}
				break;

				default:
				{
					SH_ASSERT_ALWAYS();
				}
				break;
			}
			
		}
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
void ProjectileManager::Start(EProjectile eProjectile, const CShVector2 & vPosition, const CShVector2 & vDestination, float fSpeed)
{
	m_apProjectile[eProjectile][m_aiCurrentProjectile[eProjectile]]->Start(vPosition, vDestination, fSpeed);
	m_aiCurrentProjectile[eProjectile]++;
	m_aiCurrentProjectile[eProjectile] %= POOL_PROJECTILE;
}

/**
* @brief Update
*/
void ProjectileManager::Update(float dt)
{
	for (int iProjectile = 0; iProjectile < e_projectile_max; ++iProjectile)
	{
		for (int j = 0; j < POOL_PROJECTILE; ++j)
		{
			Projectile* pProjectile = m_apProjectile[iProjectile][j];
			pProjectile->Update(dt);
		}
	}
}
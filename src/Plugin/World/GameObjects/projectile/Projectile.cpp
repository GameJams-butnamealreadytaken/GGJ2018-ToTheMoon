#include "Projectile.h"

/**
 * @brief Constructor
 */
Projectile::Projectile(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
, m_vDestination(0.0f,0.0f)
, m_vSpeed(0.0f,0.0f)
{

}

/**
 * @brief Destructor
 */
Projectile::~Projectile(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Projectile::Initialize(void)
{

}

/**
* @brief Release
*/
void Projectile::Release(void)
{

}

/**
* @brief Start
*/
void Projectile::Start(const CShVector2 & vPosition, const CShVector2 & vDestination, const CShVector2 & vSpeed)
{
	SetPosition2(vPosition);
	m_vSpeed = vSpeed;
	m_vDestination = vDestination;
}
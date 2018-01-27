#include "Projectile.h"

/**
 * @brief Constructor
 */
Projectile::Projectile(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
, m_vDestination(0.0f,0.0f)
, m_fSpeed(0.0f)
, m_vStartPosition(0.0f, 0.0f)
{
	SetState((int)OFF);
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
void Projectile::Start(const CShVector2 & vPosition, const CShVector2 & vDestination, float fSpeed)
{
	SetState((int)ON);
	SetShow(true);
	SetPosition2(vPosition);
	m_fSpeed = fSpeed;
	m_vDestination = vDestination;
	m_vStartPosition = GetPosition2();
	m_fCompletion = 0.0f;
}

void Projectile::Stop(void)
{
	SetShow(false);
	SetState((int)OFF);
}

/**
* @brief Update
*/
void Projectile::Update(float dt)
{
	if (m_iState == ON)
	{
		m_fCompletion += (dt * m_fSpeed);

		if (m_fCompletion < 1.0f)
		{
			SetPosition2(m_vStartPosition + m_fCompletion * (m_vDestination - m_vStartPosition));
		}
		else
		{
			SetPosition2(m_vDestination);
			m_fCompletion = 1.0f;

			Stop();
			SetState((int)OFF);
		}
	}
}
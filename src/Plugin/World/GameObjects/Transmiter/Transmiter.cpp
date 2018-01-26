#include "Transmiter.h"

#define RADIUS 100.0f

/**
 * @brief Constructor
 */
Transmiter::Transmiter(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
, m_eState(IDLE)
, m_fRadius(RADIUS)
{
	// ...
}

/**
 * @brief Destructor
 */
Transmiter::~Transmiter(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Transmiter::Initialize(void)
{

}

/**
* @brief Release
*/
void Transmiter::Release(void)
{

}

/**
* @brief Start
*/
void Transmiter::Start(const CShVector2 & vPosition)
{
	SetPosition2(vPosition);
	SetState((int)APPEAR);
}

/**
* @brief Update
*/
void Transmiter::Update(float dt)
{
	switch (m_eState)
	{
		case APPEAR:
		{

		}
		break;

		case IDLE:
		{

		}
		break;

		case DESTROYED:
		{

		}
		break;
	}
}
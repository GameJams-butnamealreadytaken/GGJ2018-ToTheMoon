#include "Transmiter.h"

/**
 * @brief Constructor
 */
Transmiter::Transmiter(ShEntity2 * pEntity, const CShVector2 & vPosition)
: GameObject(pEntity, vPosition)
, m_eState(IDLE)
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
* @brief Update
*/
void Transmiter::Update(float dt)
{
	switch (m_eState)
	{
		case IDLE:
		{

		}
		break;
	}
}
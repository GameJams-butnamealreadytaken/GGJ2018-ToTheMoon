#include "Planet.h"

/**
 * @brief Constructor
 */
Planet::Planet(EPlanet planet, ShEntity2 * pEntity)
: GameObject(pEntity, CShVector2(0.0f, 0.0f))
{
	if (planet == e_planet_moon)
	{
		Animate(96, "ggj", "moon", 0.5f);
	}

	SetShow(true);
	SetState((int)ON);
}

/**
 * @brief Destructor
 */
Planet::~Planet(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Planet::Initialize(void)
{

}

/**
* @brief Release
*/
void Planet::Release(void)
{

}

/**
* @brief Update
*/
void Planet::Update(float dt)
{
	GameObject::Update(dt);
}

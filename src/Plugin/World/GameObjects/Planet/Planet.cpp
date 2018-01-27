#include "Planet.h"

/**
 * @brief Constructor
 */
Planet::Planet(EPlanet planet, ShEntity2 * pEntity)
: GameObject(pEntity, CShVector2(0.0f, 0.0f))
{
	switch(planet)
	{
		case e_planet_moon :
		{
			//Animate(96, "ggj", "moon", 0.1f);
		}
		break;	

		case e_planet_earth:
		{
			//Animate(96, "ggj", "earth", 0.1f);
		}
		break;

		case e_planet_jupiter:
		{
			//Animate(96, "ggj", "jupiter", 0.1f);
		}
		break;

		case e_planet_mars:
		{
			//Animate(96, "ggj", "mars", 0.1f);
		}
		break;

		default: SH_ASSERT_ALWAYS(); break;
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

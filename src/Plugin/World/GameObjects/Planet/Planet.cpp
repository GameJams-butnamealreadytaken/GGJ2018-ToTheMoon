#include "Planet.h"

extern bool g_bDisableAnimations;

/**
 * @brief Constructor
 */
Planet::Planet(EPlanet planet, ShEntity2 * pEntity)
: GameObject(pEntity, ShEntity2::GetWorldPosition2(pEntity))
{
	if (!g_bDisableAnimations)
	{
		switch (planet)
		{
			case e_planet_moon:
			{
				m_animationManager = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("moon"), CShVector2(0.0f, 0.0f), 0.03f, 96, false, false);
			}
			break;

			case e_planet_earth:
			{
				m_animationManager = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("earth"), CShVector2(0.0f, 0.0f), 0.03f, 96, false, false);
			}
			break;

			case e_planet_jupiter:
			{
				m_animationManager = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("jupiter"), CShVector2(0.0f, 0.0f), 0.03f, 96, false, false);
			}
			break;

			case e_planet_mars:
			{
				m_animationManager = AnimatedSpriteManager(pEntity, CShString("ggj"), CShString("mars"), CShVector2(0.0f, 0.0f), 0.03f, 96, false, false);
			}
			break;

			default: SH_ASSERT_ALWAYS(); break;
		}

		m_animationManager.Play();
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

	if (!g_bDisableAnimations)
	{
		m_animationManager.Update(dt);
	}
}

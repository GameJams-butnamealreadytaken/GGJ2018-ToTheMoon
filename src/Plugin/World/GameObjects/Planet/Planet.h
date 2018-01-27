#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"
#include "../../../Animation/AnimatedSpriteManager.h"

class Planet : public GameObject
{
public:
	enum EState
	{
		OFF,
		ON
	};

	enum EPlanet
	{
		e_planet_moon,
		e_planet_jupiter,
		e_planet_mars,
		e_planet_earth,
	};

	explicit								Planet				(EPlanet planet, ShEntity2 * pEntity);
	virtual									~Planet				(void);

	void									Initialize			(void);
	void									Release				(void);

	void									Update				(float dt);

	virtual void							OnHit				(GameObject* pObject) { }
	virtual GameObject::EType				GetType(void)		{ return(GameObject::e_type_planet); }

protected:
	AnimatedSpriteManager					m_animationManager;
};

#pragma once

#include "ShSDK/ShSDK.h"

#include "../../Network/World.h"

#include "GameObjects/Explosion/ExplosionManager.h"
#include "GameObjects/Projectile/ProjectileManager.h"
#include "GameObjects/Transmiter/Transmiter.h"
#include "GameObjects/Ship/Ship.h"
#include "GameObjects/Planet/Planet.h"

class World
{

public:

	explicit	World				(void);
	virtual		~World				(void);

	void		Initialize			(const CShIdentifier & levelIdentifier);
	void		Release				(void);

	void		Update				(float dt);

	//
	// Touch Events
	void		OnTouchDown			(int iTouch, float positionX, float positionY);
	void		OnTouchUp			(int iTouch, float positionX, float positionY);
	void		OnTouchMove			(int iTouch, float positionX, float positionY);

private:

	CShIdentifier					m_levelIdentifier;
	Network::World					m_world;

	ExplosionManager				m_explosionManager;
	ProjectileManager				m_projectileManager;

	Planet*							m_aPlanet[4];
	CShArray<Transmiter *>			m_apTransmiter;
	CShArray<Ship *>				m_apShip;
	Ship *							m_pShip;

};

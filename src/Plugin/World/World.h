#pragma once

#include "ShSDK/ShSDK.h"

#include "../../Network/World.h"

#include "GameObjects/Transmiter/Transmiter.h"
#include "GameObjects/Ship/Ship.h"

#define POOL_TRANSMITER 50
#define POOL_SHIP 50

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
	Transmiter*						m_apTransmiter[POOL_TRANSMITER];
	Ship*							m_apShip[POOL_SHIP];
};

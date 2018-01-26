#pragma once

#include "ShSDK/ShSDK.h"

#include "../../Network/World.h"
#include "GameObjects/GameObject.h"

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
	CShArray<GameObject*>			m_aGameObject;
};

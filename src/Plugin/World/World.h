#pragma once

#include "ShSDK/ShSDK.h"

#include "../../Network/World.h"
#include "../../Network/WorldListener.h"

#include "GameObjects/Explosion/ExplosionManager.h"
#include "GameObjects/Projectile/ProjectileManager.h"

class ProjectileManager;
class Planet;
class Ship;
class Transmitter;
class Team;
class MiniMap;

class World : public Network::WorldListener
{

public:

	explicit	World				(void);
	virtual		~World				(void);

	void		Initialize			(const CShIdentifier & levelIdentifier);
	void		Release				(void);

	void		Update				(float dt);

	int				GetShipCount		(void);
	Ship *			GetShip				(int iShip);

	int				GetTransmitterCount	(void);
	Transmitter *	GetTransmitter		(int iTransmitter);

	//
	// Touch Events
	void		OnTouchDown			(int iTouch, float positionX, float positionY);
	void		OnTouchUp			(int iTouch, float positionX, float positionY);
	void		OnTouchMove			(int iTouch, float positionX, float positionY);
	
	virtual void onShipCreated		(const Network::Ship * pShip);
	virtual void onTransmitterCreate(const Network::Transmitter * pTrans);

private:
	void		CreateShip			(float x, float y, const Network::Ship * pShip = shNULL);
	void		CreateTransmitter	(float x, float y, const Network::Transmitter * = shNULL);

private:

	CShIdentifier					m_levelIdentifier;
	Network::World					m_world;

	MiniMap *						m_pMiniMap;

	ShUser *						m_pUser;

	ExplosionManager				m_explosionManager;
	ProjectileManager				m_projectileManager;

	Planet*							m_aPlanet[4];
	CShArray<Transmitter *>			m_apTransmitter;
	CShArray<Ship *>				m_apShip;
	Ship *							m_pShip;

	CShArray<Team *>				m_aTeam;
};

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
class PluginInputs;
class CameraPlugin;

class World : public Network::WorldListener
{
public:

	explicit		World					(void);
	virtual			~World					(void);

	void			Initialize				(const CShIdentifier & levelIdentifier);
	void			Release					(void);

	void			Update					(float dt);

	int				GetShipCount			(void);
	Ship *			GetShip					(int iShip);

	int				GetTransmitterCount		(void);
	Transmitter *	GetTransmitter			(int iTransmitter);

	int				GetPlanetCount			(void);
	Planet *		GetPlanet				(int iPlanet);

	//
	// Touch Events
	void			OnTouchDown				(int iTouch, float positionX, float positionY);
	void			OnTouchUp				(int iTouch, float positionX, float positionY);
	void			OnTouchMove				(int iTouch, float positionX, float positionY);
	
	virtual void	onShipCreated			(const Network::Ship * pShip);
	virtual void	onShipDestroyed			(const Network::Ship * pShip);

	virtual void	onTransmitterCreated	(const Network::Transmitter * pTrans);
	virtual void	onTransmitterDestroyed	(const Network::Transmitter * pTrans);
	
	void			Start					(unsigned int team);

private:

	Ship *			CreateShip				(float x, float y, const Network::Ship * pShip);
	Transmitter *	CreateTransmitter		(float x, float y, const Network::Transmitter * pTransmitter);

private:

	CShIdentifier						m_levelIdentifier;
	Network::World						m_world;

	MiniMap *							m_pMiniMap;

	CameraPlugin *						m_pCamera;

	ShUser *							m_pUser;

	PluginInputs *						m_pInputs;

	ExplosionManager					m_explosionManager;
	ProjectileManager					m_projectileManager;

	CShArray<Planet*>					m_aPlanet;
	CShArray<Transmitter *>				m_apTransmitter;
	CShArray<Ship *>					m_apShip;
	Ship *								m_pShip;

	CShArray<Team *>					m_aTeam;
};

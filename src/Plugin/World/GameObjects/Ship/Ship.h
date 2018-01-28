#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

#include "../Projectile/ProjectileManager.h"
#include "../../../../Network/World.h"

class Transmitter;

class Ship : public GameObject
{
public:
	//
	// BEWARE ! This enum must match Game/State/ShipSelection/GameStateShipSelection::EShipType
	enum EShipType
	{
		BASE,
		TANK,
		TRORAPIDE,
		PERE_NOWEL,
	};

	enum EShipState
	{
		IDLE,
		TRAVEL,
		HIT,
		DESTROYED,
	};

								Ship					(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual						~Ship					(void);

	void						Initialize				(const EShipType type, const Network::Ship * pNetworkShip, ProjectileManager * pProjectileManager);
	void						Release					(void);

	virtual void				Update					(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual void				OnHit					(GameObject* pObject);
	virtual GameObject::EType	GetType					(void) { return(e_type_ship); }


	void						SetAngle				(float fAngle);
	void						SetTarget				(float x, float y, Ship * pShip);
	void						SetTarget				(float x, float y, Transmitter * pTrans);
	void						SetVoidTarget			(float x, float y);
	void						SetTarget				(float x, float y);

	CShEulerAngles				GetRotation				(void);
	EShipType					GetShipType				(void) const;
	unsigned int				GetTeam					(void) const;
	Network::Ship *				GetNetworkShip			(void) const;

	bool						IsDead					(void);

private:
	void						SetIdleState			(void);
	void						Attack					(void);
	void						UpdateSprite			(const Network::vec2 & shipPos);
	void						UpdateTarget			(void);

private:

	EShipType			m_type;

	Network::Ship *		m_pNetworkShip;

	GameObject *		m_pTargetObject;
	EType				m_pTargetType;

	ProjectileManager *	m_pProjectileManager;
	float				m_fFireRate;

	float				m_fAttackRange;

	float				m_fAngle;

	int					m_iLife;
	float				m_fSpeed;

};

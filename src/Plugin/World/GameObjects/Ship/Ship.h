#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

#include "../../../../Network/World.h"

class Ship : public GameObject
{
public:
	enum EShipType
	{
		BASE,
		TANK,
		TRORAPIDE,
	};

	enum EShipState
	{
		IDLE,
		TRAVEL,
		FIGHT,
	};

								Ship					(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual						~Ship					(void);

	void						Initialize				(EShipType type, Network::World & world);
	void						Release					(void);

	virtual void				Update					(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual void				OnHit					(GameObject* pObject);
	virtual GameObject::EType	GetType					(void) { return(e_type_ship); }

	void						SetTarget				(float x, float y, float fSpeed);

	EShipType					GetShipType				(void);

	virtual CShVector2			GetShipPosition			(void);

private:
	void						UpdateSprite			(void);

private:

	EShipType	m_type;

	Network::Ship * m_pNetworkShip;
};

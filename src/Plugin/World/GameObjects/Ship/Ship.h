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

	void						Initialize				(const EShipType type, const Network::Ship * pNetworkShip);
	void						Release					(void);

	virtual void				Update					(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual void				OnHit					(GameObject* pObject);
	virtual GameObject::EType	GetType					(void) { return(e_type_ship); }

	void						SetTarget				(float x, float y, float fSpeed);

	EShipType					GetShipType				(void);

private:
	void						UpdateSprite			(void);

	float						ComputeVecteurNorme		(float Ax, float Ay, float Bx, float By);

private:

	EShipType	m_type;

	Network::Ship * m_pNetworkShip;
};

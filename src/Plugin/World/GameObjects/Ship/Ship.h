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
	virtual				~Ship					(void);

	void				Initialize				(EShipType type, Network::World world);
	void				Release					(void);

	virtual void		Update					(float dt) SH_ATTRIBUTE_OVERRIDE;

	EShipType			GetType					(void);

	void				SetTarget				(float x, float y, float fSpeed);

private:
	void				UpdateSprite			(void);

private:

	EShipType	m_type;

	Network::Ship * pNetworkShip;
};

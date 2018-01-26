#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

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

						Ship			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual				~Ship			(void);

	void				Initialize		(ShObject * pObject, EShipType type);
	void				Release			(void);

	virtual void		Update			(float dt) SH_ATTRIBUTE_OVERRIDE;

	EShipType			GetType			(void);

	void				SetDestination	(const CShVector2 & newDest);

private:

	EShipType	m_type;
	EShipState	m_eState;

	CShVector2	m_Destination;
};

#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

class Ship
{
public:
	enum EShipType
	{
		BASE,
		TANK,
		TRORAPIDE,
	};

						Ship			(void);
	virtual				~Ship			(void);

	void				Initialize		(ShObject * pObject, EShipType type);
	void				Release			(void);

	EShipType			GetType			(void);
	ShObject *			GetSprite		(void);

private:

	ShObject *	m_pSprite;
	EShipType	m_type;
	
};

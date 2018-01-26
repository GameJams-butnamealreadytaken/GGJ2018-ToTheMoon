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

	void				Initialize		(ShObject * pObject, EBlockType type);
	void				Release			(void);

	EBlockType			GetType			(void);
	ShObject *			GetSprite		(void);

private:

	ShObject *	m_pSprite;
	EShipType	m_type;
	
};

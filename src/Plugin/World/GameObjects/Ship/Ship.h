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

						Ship			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual				~Ship			(void);

	void				Initialize		(ShObject * pObject, EShipType type);
	void				Release			(void);

	EShipType			GetType			(void);

private:

	EShipType	m_type;
	
};

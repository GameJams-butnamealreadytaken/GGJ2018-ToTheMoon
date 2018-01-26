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

						Ship					(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual				~Ship					(void);

	void				Initialize				(EShipType type);
	void				Release					(void);

	virtual void		Update					(float dt) SH_ATTRIBUTE_OVERRIDE;

	EShipType			GetType					(void);

	void				SetTarget				(const CShVector2 & newTarget);

private:
	void				AdjustDirectionToTarget	(void);

private:

	EShipType	m_type;

	CShVector2	m_target;
	CShVector2	m_orientation;

	float		m_fSpeed;
};

#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

class Transmiter : public GameObject
{
public:

	enum ETransmiterState
	{
		IDLE,
		HIT,
		APPEAR,
		DESTROYED,
		OFF,
	};

	explicit			Transmiter			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual				~Transmiter			(void);

	void				Initialize			(void);
	void				Release				(void);

	void				Start				(const CShVector2 & vPosition);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual void		OnHit				(GameObject* pObject);
	virtual GameObject::EType GetType		(void)	{ return(e_type_transmiter); }
private:

	float				m_fRadius;
	int					m_iLife;
};

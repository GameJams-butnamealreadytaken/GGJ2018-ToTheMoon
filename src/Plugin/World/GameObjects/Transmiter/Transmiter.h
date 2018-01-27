#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

#include "../../../../Network/World.h"

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

	void				Initialize			(Network::World & world);
	void				Release				(void);

	void				Start				(const CShVector2 & vPosition);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual void		OnHit				(GameObject* pObject);
	virtual GameObject::EType GetType		(void)	{ return(e_type_transmiter); }
private:

	float					m_fRadius;
	int						m_iLife;

	Network::Transmitter *	m_pTransmitter;
};

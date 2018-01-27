#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

#include "../../../Animation/AnimatedSpriteManager.h"
#include "../../../../Network/World.h"

class Transmitter : public GameObject
{
public:

	enum ETransmitterState
	{
		IDLE,
		HIT,
		APPEAR,
		DESTROYED,
		OFF,
	};

	explicit			Transmitter			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual				~Transmitter		(void);

	void				Initialize			(const Network::Transmitter * pNetworkTransmitter, int id);
	void				Release				(void);

	void				Start				(const CShVector2 & vPosition);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual void		OnHit				(GameObject* pObject);
	virtual GameObject::EType GetType		(void)	{ return(e_type_transmitter); }

	void				AddNeighbour		(Transmitter * pTrans, ShPrimitiveSegment * pSegment);
	void				RemoveNeighbour		(Transmitter * pTrans);

	int					GetNeighbourCount	(void);
	Transmitter *		GetNeighbour		(int id);

	int					GetId				(void);

private:

	AnimatedSpriteManager	m_animationManagerDeploy;
	AnimatedSpriteManager	m_animationManagerIdle;

	int						m_id;

	float					m_fRadius;
	int						m_iLife;

	Network::Transmitter *			m_pTransmitter;
	CShArray<Transmitter *>			m_aNeighbour;
};

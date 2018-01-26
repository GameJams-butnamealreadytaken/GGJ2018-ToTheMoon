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
		TRAVEL,
		FIGHT,
	};

	explicit			Transmiter			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual				~Transmiter			(void);

	void				Initialize			(void);
	void				Release				(void);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	void				SetDestination		(const CShVector2 & newDest);

private:

	ETransmiterState	m_eState;
};

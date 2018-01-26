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
		APPEAR,
		DESTROYED,
	};

	explicit			Transmiter			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual				~Transmiter			(void);

	void				Initialize			(void);
	void				Release				(void);

	void				Start				(const CShVector2 & vPosition);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

private:

	ETransmiterState	m_eState;
	float				m_fRadius;
};

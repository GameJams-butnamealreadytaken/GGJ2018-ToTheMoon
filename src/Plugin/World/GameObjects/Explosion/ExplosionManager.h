#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "Explosion.h"

#define POOL_EXPLOSION 50

class ExplosionManager
{
public:

	explicit								ExplosionManager	(void);
	virtual									~ExplosionManager	(void);

	void									Initialize			(const CShIdentifier & levelIdentifier);
	void									Release				(void);

	void									Start				(const CShVector2 & vPosition);

	virtual void							Update				(float dt);


protected:
	int										m_iCurrentExplosion;
	Explosion*								m_apExplosion[POOL_EXPLOSION];
};

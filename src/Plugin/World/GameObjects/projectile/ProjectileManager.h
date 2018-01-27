#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"



#include "Projectile.h"
#include "Bullet/Bullet.h"

#define POOL_BULLET 500

class ProjectileManager
{
public:

	explicit								ProjectileManager	(void);
	virtual									~ProjectileManager	(void);

	void									Initialize			(const CShIdentifier & levelIdentifier);
	void									Release				(void);

	void									Start				(const CShVector2 & vPosition, const CShVector2 & vDestination, const CShVector2 & vSpeed);

	virtual void							Update				(float dt);


protected:
	Bullet*									m_apBullet[POOL_BULLET];
};

#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"



#include "Projectile.h"
#include "Bullet/Bullet.h"

#define POOL_PROJECTILE 500

class ProjectileManager
{
public:

	enum EProjectile
	{
		e_projectile_bullet,
		e_projectile_max,
	};

	explicit								ProjectileManager	(void);
	virtual									~ProjectileManager	(void);

	void									Initialize			(const CShIdentifier & levelIdentifier);
	void									Release				(void);

	void									Start				(EProjectile eProjectile, const CShVector2 & vPosition, const CShVector2 & vDestination, const CShVector2 & vSpeed);

	virtual void							Update				(float dt);


protected:
	int										m_aiCurrentProjectile[e_projectile_max];
	Projectile*								m_apProjectile[e_projectile_max][POOL_PROJECTILE];
};

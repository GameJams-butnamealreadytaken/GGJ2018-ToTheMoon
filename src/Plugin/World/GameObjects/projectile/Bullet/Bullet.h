#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../../projectile/Projectile.h"

class Bullet : public Projectile
{
public:

	explicit								Bullet				(ShEntity2 * pEntity);
	virtual									~Bullet				(void);

	void									Initialize			(void);
	void									Release				(void);

	virtual void							OnHit				(GameObject* pObject);
	virtual GameObject::EType				GetType				(void) { return(GameObject::e_type_bullet);  }

protected:

};

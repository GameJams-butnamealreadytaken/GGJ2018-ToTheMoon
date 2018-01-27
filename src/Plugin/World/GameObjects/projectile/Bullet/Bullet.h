#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../../GameObject.h"

class Bullet : public GameObject
{
public:

	explicit								Bullet				(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual									~Bullet				(void);

	void									Initialize			(void);
	void									Release				(void);

	virtual void							Update				(float dt);

	virtual void							OnHit				(GameObject* pObject);
	virtual GameObject::EType				GetType				(void) { return(GameObject::e_type_bullet);  }

protected:
	CShVector2								m_vSpeed;
	CShVector2								m_vDestination;
};

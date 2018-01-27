#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../GameObject.h"

class Explosion : public GameObject
{
public:

	enum EProjectileState
	{
		OFF,
		ON
	};

	explicit								Explosion			(ShEntity2 * pEntity, const CShVector2 & vPosition);
	virtual									~Explosion			(void);

	void									Initialize			(void);
	void									Release				(void);

	void									Start				(const CShVector2 & vPosition);
	void									Stop				(void);

	void									Update				(float dt);

	virtual void							OnHit				(GameObject* pObject) = 0;
	virtual GameObject::EType				GetType(void)		{ return(GameObject::e_type_explosion); }

protected:

};

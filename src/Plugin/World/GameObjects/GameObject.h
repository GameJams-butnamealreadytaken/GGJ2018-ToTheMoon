#pragma once

#include "ShSDK/ShSDK.h"

class GameObject
{

public:

	explicit		GameObject			(ShEntity2* pEntity, const CShVector2 & vPosition);
	virtual			~GameObject			(void);

	void			Initialize			(void);
	void			Release				(void);

	void			Animate				(int iSpriteCount, char * szSpriteLibrary, char * szSpriteName, float fAnimationInterFrameTime);
	void			Update				(float dt);

	ShEntity2 *		GetSprite			(void);
	CShVector2 &	GetPosition			(void);

private:

	bool					m_bAnimated;
	CShArray<ShSprite*>		m_aSprite;
	int						m_iCurrentAnimationSprite;
	float					m_fAnimationInterFrameTime;
	float					m_fAnimationTime;

	ShEntity2 *				m_pEntity;
	CShVector2				m_vPosition;
};

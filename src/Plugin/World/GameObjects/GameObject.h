#pragma once

#include "ShSDK/ShSDK.h"

class GameObject
{

public:

	explicit		GameObject			(ShEntity2* pEntity, const CShVector2 & vPosition);
	virtual			~GameObject			(void);

	virtual void	Initialize			(void);
	virtual void	Release				(void);

	virtual void	Animate				(int iSpriteCount, char * szSpriteLibrary, char * szSpriteName, float fAnimationInterFrameTime);
	virtual void	Update				(float dt);

	ShEntity2 *		GetSprite			(void);
	CShVector2 &	GetPosition			(void);

protected:

	bool					m_bAnimated;
	CShArray<ShSprite*>		m_aSprite;
	int						m_iCurrentAnimationSprite;
	float					m_fAnimationInterFrameTime;
	float					m_fAnimationTime;

	ShEntity2 *				m_pEntity;
	CShVector2				m_vPosition;
};

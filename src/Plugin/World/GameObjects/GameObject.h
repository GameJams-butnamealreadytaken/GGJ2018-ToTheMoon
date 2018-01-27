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

	void			SetState			(int iState);

	void			SetShow				(bool bShow);

	ShEntity2 *		GetSprite			(void);

	void			SetPosition2		(const CShVector2 & vPosition);
	CShVector2 &	GetPosition2			(void);

protected:
	int						m_iState;
	float					m_fStateTime;
	ShEntity2 *				m_pEntity;
	CShVector2				m_vPosition;

	bool					m_bAnimated;
	CShArray<ShSprite*>		m_aSprite;
	int						m_iCurrentAnimationSprite;
	float					m_fAnimationInterFrameTime;
	float					m_fAnimationTime;
};

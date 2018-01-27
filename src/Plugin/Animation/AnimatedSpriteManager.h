#pragma once

#include "ShSDK/ShSDK.h"

class AnimatedSpriteManager
{
public:

	//
	// Construction / Destruction
	explicit		AnimatedSpriteManager			(void);
	explicit		AnimatedSpriteManager			(ShEntity2* pEntity, const CShString & strSpriteLibrary, const CShString & strSpriteName, const CShVector2 & vPivot, float fInterFrameTime, int iFrameCount, bool bReversed, bool bPlayOnlyOnce);
	virtual			~AnimatedSpriteManager			(void);

	virtual void	Update							(float dt);

	void			Play							(void);
	void			Stop							(void);
	void			Reset							(void);
	bool			IsPlaying						(void);

private:
	CShArray<ShSprite*>	m_apSprite;
	bool				m_bOn;
	CShString			m_strSpriteLibrary;
	CShString			m_strSpriteName;
	float				m_fInterFrameTime;
	int					m_iFrameCount;
	bool				m_bReversed;
	bool				m_bPlayOnlyOnce;
	float				m_fTime;
	int					m_iCurrentSprite;
	ShEntity2*			m_pEntity;
	CShVector2			m_vPivot;
protected:

private:

};

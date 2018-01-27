#include "AnimatedSpriteManager.h"

/**
* @brief Constructor
*/
/*explicit*/ AnimatedSpriteManager::AnimatedSpriteManager(void)
{

}

/**
* @brief Constructor
*/
/*explicit*/ AnimatedSpriteManager::AnimatedSpriteManager(ShEntity2* pEntity, const CShString & strSpriteLibrary, const CShString & strSpriteName, const CShVector2 & vPivot, float fInterFrameTime, int iFrameCount, bool bReversed, bool bPlayOnlyOnce)
: m_apSprite()
, m_strSpriteLibrary(strSpriteLibrary)
, m_strSpriteName(strSpriteName)
, m_fInterFrameTime(fInterFrameTime)
, m_iFrameCount(iFrameCount)
, m_bReversed(bReversed)
, m_bPlayOnlyOnce(bPlayOnlyOnce)
, m_bOn(false)
, m_iCurrentSprite(0)
, m_pEntity(pEntity)
, m_vPivot(vPivot)
{
	for (int iFrame = 0; iFrame < iFrameCount; ++iFrame)
	{
		char szEntityName[1024];
		sprintf(szEntityName, "%s_%02d", m_strSpriteName.Get(), iFrame+1);
		ShSprite* pSprite = ShSprite::Find(CShIdentifier(m_strSpriteLibrary), CShIdentifier(szEntityName));
		m_apSprite.Add(pSprite);
	}
}

/**
* @brief Destructor
*/
/*virtual*/ AnimatedSpriteManager::~AnimatedSpriteManager(void)
{

}

/**
* @brief Update
*/
/*virtual*/ void AnimatedSpriteManager::Update(float dt)
{
	shClamp(dt, 0.0f, 0.05f);

	if (m_bOn)
	{
		m_fTime += dt;

		if (m_fTime > m_fInterFrameTime)
		{
			m_iCurrentSprite++;

			if (m_iCurrentSprite == m_iFrameCount)
			{
				if (m_bPlayOnlyOnce)
				{
					m_bOn = false;
					return;
				}

				m_iCurrentSprite = 0;
			}

			ShEntity2::SetSprite(m_pEntity, m_apSprite[m_iCurrentSprite]);
			m_fTime = m_fTime - m_fInterFrameTime;
		}
	}
}

/**
* @brief Play
*/
void AnimatedSpriteManager::Play(void)
{
	Reset();
	m_bOn = true;
}

/**
* @brief Stop
*/
void AnimatedSpriteManager::Stop(void)
{
	m_bOn = false;
}

/**
* @brief Reset
*/
void AnimatedSpriteManager::Reset(void)
{
	m_fTime = 0.0f;
	m_iCurrentSprite = 1;

	if (m_bReversed)
	{
		ShEntity2::SetRotation(m_pEntity, 0.0f, 3.1415f, 0.0f);
	}
	else
	{
		ShEntity2::SetRotation(m_pEntity, 0.0f, 0.0f, 0.0f);
	}

	ShEntity2::SetSprite(m_pEntity, m_apSprite[0]);
	ShEntity2::SetPivotCustom(m_pEntity, m_vPivot);
}

/**
* @brief IsPlaying
*/
bool AnimatedSpriteManager::IsPlaying(void)
{
	return m_bOn;
}

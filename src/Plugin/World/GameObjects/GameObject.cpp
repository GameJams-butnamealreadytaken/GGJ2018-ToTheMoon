#include "GameObject.h"

/**
* @brief Constructor
*/
/*explicit*/ GameObject::GameObject(ShEntity2 * pEntity, const CShVector2 & vPosition)
: m_iState(0)
, m_fStateTime(0.0f)
, m_pEntity(pEntity)
, m_vPosition(vPosition)
, m_bAnimated(false)
, m_aSprite()
, m_iCurrentAnimationSprite(0.0f)
, m_fAnimationInterFrameTime(0.0f)
, m_fAnimationTime(0.0f)
, m_bPlayAnimationOnlyOnce(false)
, m_bAnimationEnded(false)
{
	ShEntity2::SetShow(pEntity, false);
}

/**
* @brief Destructor
*/
/*virtual*/ GameObject::~GameObject(void)
{
	// ...
}

/**
* @brief GameObject::Initialize
*/
void GameObject::Initialize(void)
{

}

/**
* @brief GameObject::Release
*/
void GameObject::Release(void)
{

}

/**
* @brief GameObject::Animate
*/
void GameObject::Animate(int iSpriteCount, char* szSpriteLibrary, char* szSpriteName, float fAnimationInterFrameTime, bool bPlayOnce /* = false */)
{
	m_bAnimated = true;
	m_fAnimationInterFrameTime = fAnimationInterFrameTime;
	m_bAnimationEnded = false;
	m_bPlayAnimationOnlyOnce = bPlayOnce;

	for (int iFrame = 0; iFrame < iSpriteCount; ++iFrame)
	{
		char szEntityName[1024];
		sprintf(szEntityName, "%s_%02d", szSpriteName, iFrame+1);
		ShSprite* pSprite = ShSprite::Find(CShIdentifier(szSpriteLibrary), CShIdentifier(szEntityName));
		m_aSprite.Add(pSprite);
	}
}

/**
* @brief GameObject::Update
*/
void GameObject::Update(float dt)
{
	m_fStateTime += dt;

	shClamp(dt, 0.0f, 0.05f);

	if (m_bAnimated && !m_bAnimationEnded)
	{
		m_fAnimationTime += dt;

		if (m_fAnimationTime > m_fAnimationInterFrameTime)
		{
			m_iCurrentAnimationSprite++;

			if (m_iCurrentAnimationSprite == m_aSprite.GetCount())
			{
				if (m_bPlayAnimationOnlyOnce)
				{
					m_bAnimationEnded = true;
				}

				m_iCurrentAnimationSprite = 0;
			}

			ShEntity2::SetSprite(m_pEntity, m_aSprite[m_iCurrentAnimationSprite]);
			m_fAnimationTime = m_fAnimationTime - m_fAnimationInterFrameTime;
		}
	}
}

/**
* @brief GameObject::SetState
*/
void GameObject::SetState(int iState)
{
	m_iState = iState;
	m_fStateTime = 0.0f;
}

/**
* @brief GameObject::SetShow
*/
void GameObject::SetShow(bool bShow)
{
	ShEntity2::SetShow(m_pEntity, bShow);
}

/**
* @brief GameObject::GetSprite
*/
ShEntity2 * GameObject::GetSprite(void)
{
	return(m_pEntity);
}

/**
* @brief GameObject::SetPosition2
*/
void GameObject::SetPosition2(const CShVector2 & vPosition)
{
	ShEntity2::SetPosition2(m_pEntity, vPosition);
}

/**
* @brief GameObject::GetPosition
*/
CShVector2 & GameObject::GetPosition2(void)
{
	return(m_vPosition);
}

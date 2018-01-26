#include "GameObject.h"

/**
* @brief Constructor
*/
/*explicit*/ GameObject::GameObject(ShEntity2 * pEntity, const CShVector2 & vPosition)
: m_bAnimated(false)
, m_aSprite()
, m_iCurrentAnimationSprite(0.0f)
, m_fAnimationInterFrameTime(0.0f)
, m_fAnimationTime(0.0f)
, m_pEntity(pEntity)
, m_vPosition(vPosition)
{
	// ...
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
void GameObject::Animate(int iSpriteCount, char* szSpriteLibrary, char* szSpriteName, float fAnimationInterFrameTime)
{
	m_bAnimated = true;
	m_fAnimationInterFrameTime = fAnimationInterFrameTime;

	for (int iFrame = 0; iFrame < iSpriteCount; ++iFrame)
	{
		char szEntityName[1024];
		sprintf(szEntityName, "%s_%04d", szSpriteName, iFrame);
		m_aSprite.Add(ShSprite::Find(CShIdentifier(szSpriteLibrary), CShIdentifier(szEntityName)));
	}
}

/**
* @brief GameObject::Update
*/
void GameObject::Update(float dt)
{
	if (m_bAnimated)
	{
		m_fAnimationTime += dt;

		if (m_fAnimationTime > m_fAnimationInterFrameTime)
		{
			m_iCurrentAnimationSprite++;

			if (m_iCurrentAnimationSprite == m_aSprite.GetCount())
			{
				m_iCurrentAnimationSprite = 0;
			}

			ShEntity2::SetSprite(m_pEntity, m_aSprite[m_iCurrentAnimationSprite]);
		}
	}
}
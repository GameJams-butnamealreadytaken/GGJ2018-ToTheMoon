#include "GameObject.h"

extern bool g_bDisableAnimations;

/**
* @brief Constructor
*/
/*explicit*/ GameObject::GameObject(ShEntity2 * pEntity, const CShVector2 & vPosition)
: m_iState(0)
, m_fStateTime(0.0f)
, m_pEntity(pEntity)
, m_vPosition(vPosition)
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
* @brief GameObject::Update
*/
void GameObject::Update(float dt)
{
	m_fStateTime += dt;
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

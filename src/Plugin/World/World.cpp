#include "World.h"

/**
* @brief Constructor
*/
/*explicit*/ World::World(void)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ World::~World(void)
{
	// ...
}

/**
* @brief World::Initialize
*/
void World::Initialize(const CShIdentifier & levelIdentifier)
{
	m_levelIdentifier = levelIdentifier;

	ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj2018"), CShIdentifier("img_01"), CShVector3(0.0f, 0.0f, 0.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
	GameObject * pObject = new GameObject(pEntity, CShVector2(0.0f, 0.0f));
	pObject->Animate(3, "ggj", "img", 0.5f);

	m_aGameObject.Add(pObject);
}

/**
* @brief World::Release
*/
void World::Release(void)
{
	
}

/**
* @brief World::Update
*/
void World::Update(float dt)
{
	m_world.update(dt);

	int iGameObject = m_aGameObject.GetCount();

	for (int iObject = 0; iObject < iGameObject; ++iObject)
	{
		GameObject * pObject = m_aGameObject[iObject];
		pObject->Update(dt);
	}
}

/**
* @brief World::OnTouchDown
*/
void World::OnTouchDown(int iTouch, float positionX, float positionY)
{

}

/**
* @brief World::OnTouchUp
*/
void World::OnTouchUp(int iTouch, float positionX, float positionY)
{

}

/**
* @brief World::OnTouchMove
*/
void World::OnTouchMove(int iTouch, float positionX, float positionY)
{

}
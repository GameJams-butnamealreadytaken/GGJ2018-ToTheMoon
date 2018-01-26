#include "World.h"

/**
* @brief Constructor
*/
/*explicit*/ World::World(void) : m_world(1000.0f, 1000.0f)
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
	Transmiter * pTransmiter = new Transmiter(pEntity, CShVector2(0.0f, 0.0f));
	pTransmiter->Animate(3, "ggj", "img", 0.5f);

	m_aTransmiter.Add(pTransmiter);
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

	//
	// Update Transmiter
	int iTransmiterCount = m_aTransmiter.GetCount();

	for (int iTransmiter = 0; iTransmiter < iTransmiterCount; ++iTransmiter)
	{
		Transmiter * pTransmiter = m_aTransmiter[iTransmiter];
		pTransmiter->Update(dt);
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

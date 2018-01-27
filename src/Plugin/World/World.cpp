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

	//
	// Create transmiter
	{
		for (int i = 0; i < POOL_TRANSMITER; ++i)
		{
			ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("transmiter"), CShVector3(0.0f, 0.0f, 0.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			Transmiter * pTransmiter = new Transmiter(pEntity, CShVector2(0.0f, 0.0f));
			m_apTransmiter[i] = pTransmiter;
		}
	}

	//
	// Create ship
	//{
	//	for (int i = 0; i < POOL_SHIP; ++i)
	//	{
	//		ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("ship"), CShVector3(0.0f, 0.0f, 0.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
	//		Ship * pShip = new Ship(pEntity, CShVector2(0.0f, 0.0f));
	//		m_apShip[i] = pShip;
	//	}
	//}
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
	for (int iTransmiter = 0; iTransmiter < POOL_TRANSMITER; ++iTransmiter)
	{
		Transmiter * pTransmiter = m_apTransmiter[iTransmiter];
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

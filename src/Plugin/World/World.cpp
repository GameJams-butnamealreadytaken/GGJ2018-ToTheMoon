#include "World.h"

/**
* @brief Constructor
*/
/*explicit*/ World::World(void) 
	: m_world(1000.0f, 1000.0f)
	, m_pShip(shNULL)
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

	m_world.init();
	//
	// Create Ship
	{
		ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("transmiter"), CShVector3(0.0f, 0.0f, 0.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
		m_pShip = new Ship(pEntity, CShVector2(0.0f,0.0f));
		m_pShip->Initialize(Ship::BASE, m_world);
	}
}

/**
* @brief World::Release
*/
void World::Release(void)
{
	m_world.release();
}

/**
* @brief World::Update
*/
void World::Update(float dt)
{
	m_world.update(dt);

	//
	// Update Transmiters

	int iTransmiterCount = m_apTransmiter.GetCount();
	for (int iTransmiter = 0; iTransmiter < iTransmiterCount; ++iTransmiter)
	{
		Transmiter * pTransmiter = m_apTransmiter[iTransmiter];
		pTransmiter->Update(dt);
	}

	//
	// Update ships
	//int iShipCount = m_apShip.GetCount();
	//for (int iShip = 0; iShip < iShipCount; ++iShip)
	//{
	//	const Ship * pShip = m_apShip[iShip];
	//	pShip->Update(dt);
	//}
}

/**
* @brief World::OnTouchDown
*/
void World::OnTouchDown(int iTouch, float positionX, float positionY)
{
	// Set new ship target
	if (shNULL != m_pShip)
	{
		m_pShip->SetTarget(positionX, positionY, 5.0f); // todo move speed on her right place
	}
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

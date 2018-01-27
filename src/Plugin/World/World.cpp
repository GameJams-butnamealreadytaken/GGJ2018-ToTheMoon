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
	// Create player's Ship
	{
		ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("transmiter"), CShVector3(0.0f, 0.0f, 100.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(10.0f, 10.0f, 1.0f));
		SH_ASSERT(shNULL != pEntity);
		m_pShip = new Ship(pEntity, CShVector2(0.0f,0.0f));
		m_pShip->Initialize(Ship::BASE, m_world);
		m_apShip.Add(m_pShip);
	}
}

/**
* @brief World::Release
*/
void World::Release(void)
{
	m_world.release();

	m_pShip = shNULL;

	int nShipCount = m_apShip.GetCount();
	for (int i = 0; i < nShipCount; ++i)
	{
		m_apShip[i]->Release();
		SH_SAFE_DELETE(m_apShip[i]);
	}
	m_apShip.Empty();
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
	// Update ship
	if (m_pShip)
	{
		m_pShip->Update(dt);
	}
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

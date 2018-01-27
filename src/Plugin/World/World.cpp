#include "World.h"

#include "GameObjects/projectile/ProjectileManager.h"

/**
* @brief Constructor
*/
/*explicit*/ World::World(void) 
	: m_levelIdentifier()
	, m_world(1000.0f, 1000.0f)
	, m_projectileManager()
	, m_apTransmiter()
	, m_apShip()
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

	m_projectileManager.Initialize(levelIdentifier);

	//
	// Create player's Ship
	{
		ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("image_white"), CShVector3(0.0f, 0.0f, 2.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(10.0f, 10.0f, 1.0f));
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
	m_pShip = shNULL;

	int nShipCount = m_apShip.GetCount();
	for (int i = 0; i < nShipCount; ++i)
	{
		m_apShip[i]->Release();
		SH_SAFE_DELETE(m_apShip[i]);
	}
	m_apShip.Empty();

	m_projectileManager.Release();

	m_world.release();
}

/**
* @brief World::Update
*/
void World::Update(float dt)
{
	m_world.update(dt);

	//
	// Update projectile manager
	m_projectileManager.Update(dt);

	
	static float x = 0.0f;
	static float y = 0.0f;
	y += dt;
	x += dt;

	if (y > 0.1f)
	{
		m_projectileManager.Start(ProjectileManager::e_projectile_bullet, CShVector2(0.0f, 0.0f), CShVector2(500.0f * cos(x), 500.0f * sin(x)), 5.0f);
		y = 0.0f;
	}

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

		ShCamera* pCamera = ShCamera::GetCamera2D();
		ShCamera::SetPosition2(pCamera, m_pShip->GetPosition2());
		ShCamera::SetTarget(pCamera, CShVector3(m_pShip->GetPosition2(), 0.0f));
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

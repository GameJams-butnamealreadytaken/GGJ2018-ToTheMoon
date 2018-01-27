#include "World.h"

#include "GameObjects/Projectile/ProjectileManager.h"

#define TEST 1

/**
* @brief Constructor
*/
/*explicit*/ World::World(void) 
	: m_levelIdentifier()
	, m_world(INFINITY, INFINITY)
	, m_explosionManager()
	, m_projectileManager()
	, m_apTransmitter()
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

	m_explosionManager.Initialize(levelIdentifier);
	m_projectileManager.Initialize(levelIdentifier);

	//
	// Create Planets
	{
		//
		// Moon
		{
			ShEntity2* pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("moon_01"), CShVector3(0.0f, 0.0f, 99.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_aPlanet[0] = new Planet(Planet::e_planet_moon, pEntity);
			m_aPlanet[0]->SetPosition2(CShVector2(-700.0f, -700.0f));
		}

		//
		// Earth
		{
			ShEntity2* pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("earth_01"), CShVector3(0.0f, 0.0f, 99.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_aPlanet[1] = new Planet(Planet::e_planet_earth, pEntity);
			m_aPlanet[1]->SetPosition2(CShVector2(700.0f, -700.0f));
		}

		//
		// Mars
		{
			ShEntity2* pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("mars_01"), CShVector3(0.0f, 0.0f, 99.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_aPlanet[2] = new Planet(Planet::e_planet_mars, pEntity);
			m_aPlanet[2]->SetPosition2(CShVector2(-700.0f, 700.0f));
		}

		//
		// Jupiter
		{
			ShEntity2* pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("jupiter_01"), CShVector3(0.0f, 0.0f, 99.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_aPlanet[3] = new Planet(Planet::e_planet_jupiter, pEntity);
			m_aPlanet[3]->SetPosition2(CShVector2(700.0f, 700.0f));
		}
	}

	//
	// Create player's Ship
	CreateShip(0.0f, 0.0f);

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
	m_explosionManager.Release();

	m_world.release();
}

/**
* @brief World::Update
*/
void World::Update(float dt)
{
	m_world.update(dt);

	//
	// Update planets
	for (int iPlanet = 0; iPlanet < 4; ++iPlanet) 
	{
		m_aPlanet[iPlanet]->Update(dt);
	}
	

	//
	// Update explosion manager
	m_explosionManager.Update(dt);

	//
	// Update projectile manager
	m_projectileManager.Update(dt);
	
#if TEST
	{
		static float x = 0.0f;
		static float y = 0.0f;

		y += dt;
		x += dt;

		if (y > 0.1f)
		{
			m_projectileManager.Start(ProjectileManager::e_projectile_bullet, CShVector2(0.0f, 0.0f), CShVector2(500.0f * cos(x), 500.0f * sin(x)), 5.0f);
			y = 0.0f;
		}
	}
#endif //TEST

	//
	// Update Transmitters
	int iTransmitterCount = m_apTransmitter.GetCount();
	for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
	{
		Transmitter * pTransmitter = m_apTransmitter[iTransmitter];
		pTransmitter->Update(dt);
	}

	//
	// Update ship
	if (m_pShip)
	{
		m_pShip->Update(dt);

		ShCamera* pCamera = ShCamera::GetCamera2D();
		CShVector2 shipPos = m_pShip->GetPosition2();
		ShCamera::SetPosition2(pCamera, shipPos);
		ShCamera::SetTarget(pCamera, CShVector3(shipPos, 0.0f));
	}
}

/**
* @brief World::OnTouchDown
*/
void World::OnTouchDown(int iTouch, float positionX, float positionY)
{
	ShCamera * pCamera = ShCamera::GetCamera2D();

	const CShVector2 & viewport = ShCamera::GetViewport(pCamera);

	CShVector2 screenPos(0.0f, 0.0f);
	screenPos.m_x = positionX + viewport.m_x * 0.5f;
	screenPos.m_y = (viewport.m_y - positionY) - viewport.m_y * 0.5f;

	CShRay3 ray = ShCamera::Unproject(pCamera, screenPos);

	CShVector3 worldPosition = ray.GetOrigin();

	// Set new ship target
	if (shNULL != m_pShip)
	{
		m_pShip->SetTarget(worldPosition.m_x, worldPosition.m_y, 5.0f); // todo move speed on her right place
	}


#if TEST
	m_explosionManager.Start(CShVector2(worldPosition.m_x, worldPosition.m_y));
	CreateTransmitter(worldPosition.m_x, worldPosition.m_y);
#endif //TEST
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

/**
* @brief World::OnShipCreated
*/
/*virtual*/ void World::OnShipCreated(Network::Ship* pShip)
{
	//m_apShip.Add(new Ship(pShip));
	//m_apShip[0]->Initialize()
}

/**
* @brief World::CreateShip
*/
void World::CreateShip(float x, float y)
{
	ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("image_white"), CShVector3(x, y, 2.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(10.0f, 10.0f, 1.0f));
	SH_ASSERT(shNULL != pEntity);
	m_pShip = new Ship(pEntity, CShVector2(x, y));
	Network::Ship * pShip = m_world.createShip(x, y);
	m_pShip->Initialize(Ship::BASE, pShip);
	m_apShip.Add(m_pShip);
}

/**
* @brief World::CreateTransmitter
*/
void World::CreateTransmitter(float x, float y)
{
	ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("transmiter"), CShVector3(x, y, 2.01f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
	SH_ASSERT(shNULL != pEntity);
	Transmitter * pTrans = new Transmitter(pEntity, CShVector2(x, y));
	pTrans->Initialize(m_world);
	m_apTransmitter.Add(pTrans);
}

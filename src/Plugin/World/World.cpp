#include "World.h"

#include "GameObjects/Transmitter/Transmitter.h"
#include "GameObjects/Ship/Ship.h"
#include "GameObjects/Planet/Planet.h"
#include "Team/Team.h"

#define TEST 0

/**
* @brief Constructor
*/
/*explicit*/ World::World(void) 
: m_levelIdentifier()
, m_world(5.0f * 2048.0f, 5.0f * 1152.0f)
, m_pMiniMap(shNULL)
, m_pUser(shNULL)
, m_explosionManager()
, m_projectileManager()
, m_apTransmitter()
, m_apShip()
, m_pShip(shNULL)
, m_aTeam()
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
	m_world.setListener(this);
	m_pMiniMap->Initialize(this);
	m_explosionManager.Initialize(levelIdentifier);
	m_projectileManager.Initialize(levelIdentifier);

	//
	// Create Planets
	{
		//
		// Moon
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_moon_01_001"));
			m_aPlanet[0] = new Planet(Planet::e_planet_moon, pEntity);
		}

		//
		// Earth
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_earth_01_001")); 
			m_aPlanet[1] = new Planet(Planet::e_planet_earth, pEntity);
		}

		//
		// Mars
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_mars_01_001"));
			m_aPlanet[2] = new Planet(Planet::e_planet_mars, pEntity);
		}

		//
		// Jupiter
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_jupiter_01_001"));
			m_aPlanet[3] = new Planet(Planet::e_planet_jupiter, pEntity);
		}
	}

	//
	// Create player's Ship
	CreateShip(0.0f, 0.0f);

	m_aTeam.Empty();
	int nTeam = 2; // get nbTeam from Network
	for (int i = 0; i < nTeam; ++i)
	{
		Team * pTeam = new Team(i);
		m_aTeam.Add(pTeam);
	}

	m_pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != m_pUser);
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

	int nTeamCount = m_aTeam.GetCount();
	for (int i = 0; i < nTeamCount; ++i)
	{
		m_aTeam[i]->Release();
	}
	m_aTeam.Empty();

	int nTransmitterCount = m_apTransmitter.GetCount();
	for (int i = 0; i < nTransmitterCount; ++i)
	{
		m_apTransmitter[i]->Release();
		SH_SAFE_DELETE(m_apTransmitter[i]);
	}
	m_apTransmitter.Empty();

	m_projectileManager.Release();
	m_explosionManager.Release();

	m_pMiniMap->Release();
	m_world.release();
}

/**
* @brief World::Update
*/
void World::Update(float dt)
{
	m_world.update(dt);
	m_pMiniMap->Update(dt);

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

	//
	// Update ships
	int iShipCount = m_apShip.GetCount();
	for (int iShip = 0; iShip < iShipCount; ++iShip)
	{
		Ship * pShip = m_apShip[iShip];
		pShip->Update(dt);

		if (pShip == m_pShip)
		{
			ShCamera* pCamera = ShCamera::GetCamera2D();
			CShVector2 shipPos = m_pShip->GetPosition2();
			ShCamera::SetPosition2(pCamera, shipPos);
			ShCamera::SetTarget(pCamera, CShVector3(shipPos, 0.0f));
		}
	}

	//
	// Update Transmitters
	int iTransmitterCount = m_apTransmitter.GetCount();
	for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
	{
		Transmitter * pTransmitter = m_apTransmitter[iTransmitter];
		pTransmitter->Update(dt);
	}

	//
	// Plugin Inputs
	if (m_pUser)
	{
		if (ShUser::HasTriggeredAction(m_pUser, CShIdentifier("beacon")))
		{
			CShVector2 & shipPos = m_pShip->GetPosition2();
			CreateTransmitter(shipPos.m_x, shipPos.m_y);
		}
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
	//m_explosionManager.Start(CShVector2(worldPosition.m_x, worldPosition.m_y));
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
* @brief World::onShipCreated
*/
/*virtual*/ void World::onShipCreated(const Network::Ship * pShip)
{
	Network::vec2 pos = pShip->getPosition();
	CreateShip(pos.x, pos.y, pShip);
}

/**
* @brief World::onTransmitterCreate
*/
/*virtual*/ void World::onTransmitterCreate(const Network::Transmitter * pTrans)
{
	Network::vec2 pos = pTrans->getPosition();
	CreateTransmitter(pos.x, pos.y, pTrans);
}

/**
* @brief World::CreateShip
*/
void World::CreateShip(float x, float y, const Network::Ship * pNetworkShip /*= shNULL*/)
{
	ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("ship"), CShVector3(x, y, 1.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(0.15f, 0.15f, 1.0f));
	SH_ASSERT(shNULL != pEntity);
	Ship * pShip = new Ship(pEntity, CShVector2(x, y));
	if (shNULL == pNetworkShip)
	{
		pNetworkShip = m_world.createShip(x, y);
		m_pShip = pShip;
	}
	pShip->Initialize(Ship::BASE, pNetworkShip, &m_projectileManager);
	m_apShip.Add(pShip);
}

/**
* @brief World::CreateTransmitter
*/
void World::CreateTransmitter(float x, float y, const Network::Transmitter * pNetworkTrans /*= shNULL*/)
{
	ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("transmitter_01"), CShVector3(x, y, 2.01f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(0.8f, 0.8f, 1.0f));
	SH_ASSERT(shNULL != pEntity);
	Transmitter * pTrans = new Transmitter(pEntity, CShVector2(x, y));
	if (shNULL == pNetworkTrans)
	{
		pNetworkTrans = m_world.createTransmitter(x, y);
	}
	m_apTransmitter.Add(pTrans);
	pTrans->Initialize(pNetworkTrans, m_apTransmitter.GetCount() - 1);
	pTrans->Start(CShVector2(x, y));
	
	int teamId = 0; // get id from network transmitter
	m_aTeam[teamId]->AddTransmitter(pTrans);
}

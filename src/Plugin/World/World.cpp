#include "World.h"

#include "Inputs/InputManager.h"
#include "MiniMap/MiniMap.h"
#include "GameObjects/Transmitter/Transmitter.h"
#include "GameObjects/Ship/Ship.h"
#include "GameObjects/Planet/Planet.h"
#include "Team/Team.h"
#include "Camera/CameraPlugin.h"

#define HALF_SIZE_X 5.0f * 2048.0f
#define HALF_SIZE_Y 5.0f * 1152.0f
#define TEST 0

#define DEFAULT_TRANSMITTER_LIFE 10
#define DEFAULT_SHIP_LIFE 10

ExplosionManager g_explosionManager;

/**
* @brief Constructor
*/
/*explicit*/ World::World(void) 
: m_levelIdentifier()
, m_world(HALF_SIZE_X, HALF_SIZE_Y)
, m_pMiniMap(shNULL)
, m_pUser(shNULL)
, m_pInputs(shNULL)
, m_projectileManager()
, m_apTransmitter()
, m_apShip()
, m_pShip(shNULL)
, m_aTeam()
, m_pBoundRect(shNULL)
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
	// Create world delimiters
	{
		m_pBoundRect = ShPrimitiveRect::Create(m_levelIdentifier, GID(NULL), CShVector2(-HALF_SIZE_X, HALF_SIZE_Y), CShVector2(HALF_SIZE_X, -HALF_SIZE_Y), CShRGBAf(1.0f, 1.0f, 0.0f, 1.0f));
		ShPrimitiveRect::Set2d(m_pBoundRect, true);
	}

	m_world.init();
	m_world.setListener(this);

	g_explosionManager.Initialize(levelIdentifier);
	m_projectileManager.Initialize(levelIdentifier);

	//
	// Create Planets
	{
		//
		// Moon
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_moon_01_001"));
			m_aPlanet.Add(new Planet(Planet::e_planet_moon, pEntity));
		}

		//
		// Earth
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_earth_01_001")); 
			m_aPlanet.Add(new Planet(Planet::e_planet_earth, pEntity));
		}

		//
		// Mars
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_mars_01_001"));
			m_aPlanet.Add(new Planet(Planet::e_planet_mars, pEntity));
		}

		//
		// Jupiter
		{
			ShEntity2* pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_jupiter_01_001"));
			m_aPlanet.Add(new Planet(Planet::e_planet_jupiter, pEntity));
		}
	}

	m_aTeam.Empty();
	for (int i = 0; i < 2; ++i)
	{
		Team * pTeam = new Team(i);
		pTeam->Initialize(m_levelIdentifier, m_aPlanet[i]->GetPosition2(), m_aPlanet[i + 2]->GetPosition2());
		m_aTeam.Add(pTeam);
	}

	m_pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != m_pUser);

	m_pInputs = new PluginInputs();
	m_pInputs->Initialize(m_pUser);

	m_pMiniMap = new MiniMap();
	m_pMiniMap->Initialize(levelIdentifier, this);

	m_pCamera = new CameraPlugin(CShVector2(HALF_SIZE_X, HALF_SIZE_Y));
	m_pCamera->Initialize(m_pInputs);
}

/**
* @brief World::Release
*/
void World::Release(void)
{
	m_pMiniMap->Release();

	m_world.destroyShip(m_pShip->GetNetworkShip());
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
	g_explosionManager.Release();

	m_pInputs->Release();
	SH_SAFE_DELETE(m_pInputs);

	m_pCamera->Release();
	SH_SAFE_DELETE(m_pCamera);

	m_world.release();

	ShPrimitiveRect::Destroy(m_pBoundRect);
}

/**
* @brief World::Update
*/
void World::Update(float dt)
{
	m_world.update(dt);

	m_pInputs->Update();
	
	if (m_pShip)
	{
		m_pCamera->Update(dt, m_pShip->GetPosition2());

		//
		// Plugin Inputs
		if (m_pInputs->LaunchedBeacon())
		{

			CShVector2 & shipPos = m_pShip->GetPosition2();
			Network::Transmitter * pNetworkTrans = m_world.createTransmitter(m_pShip->GetTeam(), DEFAULT_TRANSMITTER_LIFE, shipPos.m_x, shipPos.m_y);
			CreateTransmitter(shipPos.m_x, shipPos.m_y, pNetworkTrans);

		}

	}

	//
	// Update planets
	for (int iPlanet = 0; iPlanet < 4; ++iPlanet) 
	{
		m_aPlanet[iPlanet]->Update(dt);
	}

	//
	// Update explosion manager
	g_explosionManager.Update(dt);

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
	}

	//
	// Update Transmitters
	int iTransmitterCount = m_apTransmitter.GetCount();
	for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
	{
		Transmitter * pTransmitter = m_apTransmitter[iTransmitter];
		pTransmitter->Update(dt);
	}

	m_pMiniMap->Update(dt);
}

/**
* @brief World::GetShipCount
*/
int	World::GetShipCount(void)
{
	return(m_apShip.GetCount());
}

/**
* @brief World::GetShip
*/
Ship * World::GetShip(int iShip)
{
	return(m_apShip[iShip]);
}

/**
* @brief World::GetMyShip
*/
Ship * World::GetMyShip(void)
{
	return(m_pShip);
}

/**
* @brief World::GetTransmitterCount
*/
int	World::GetTransmitterCount(void)
{
	return(m_apTransmitter.GetCount());
}

/**
* @brief World::GetTransmitter
*/
Transmitter * World::GetTransmitter(int iTransmitter)
{
	return(m_apTransmitter[iTransmitter]);
}

/**
* @brief World::GetPlanetCount
*/
int	World::GetPlanetCount(void)
{
	return(m_aPlanet.GetCount());
}

/**
* @brief World::GetPlanet
*/
Planet * World::GetPlanet(int iPlanet)
{
	return(m_aPlanet[iPlanet]);
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
		// Check target type
		int iShipCount = m_apShip.GetCount();
		for (int iShip = 0; iShip < iShipCount; ++iShip)
		{
			Ship * pShip = m_apShip[iShip];
			if (pShip != m_pShip)
			{
				if (m_pShip->GetTeam() != pShip->GetTeam())
				{
					if (ShEntity2::Includes(pShip->GetSprite(), CShVector2(worldPosition.m_x, worldPosition.m_y)))
					{
						m_pShip->SetTarget(worldPosition.m_x, worldPosition.m_y, pShip); // todo move speed on her right place
						return;
					}
				}
			}
		}

		//
		// Update Transmitters
		int iTransmitterCount = m_apTransmitter.GetCount();
		for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
		{
			Transmitter * pTransmitter = m_apTransmitter[iTransmitter];
			if (m_pShip->GetTeam() != pTransmitter->GetTeam())
			{
				CShVector2 transPos = ShEntity2::GetWorldPosition2(pTransmitter->GetSprite());
				if (75.0f > ComputeVecteurNorme(transPos.m_x, transPos.m_y, worldPosition.m_x, worldPosition.m_y))
				{
					m_pShip->SetTarget(worldPosition.m_x, worldPosition.m_y, pTransmitter); // todo move speed on her right place
					return;
				}
			}
		}

		m_pShip->SetVoidTarget(worldPosition.m_x, worldPosition.m_y); // todo move speed on her right place
	}

#if TEST
	//m_explosionManager.Start(CShVector2(worldPosition.m_x, worldPosition.m_y));
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
* @brief World::ComputeVecteurNorme
*/
float World::ComputeVecteurNorme(float Ax, float Ay, float Bx, float By)
{
	return sqrt(((Bx - Ax)*(Bx - Ax)) + ((By - Ay)*(By - Ay)));
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
 * @brief World::onShipDestroyed
 */
/*virtual*/ void World::onShipDestroyed(const Network::Ship * pShip)
{
	int nShipCount = m_apShip.GetCount();
	for (int i = 0; i < nShipCount; ++i)
	{
		if (pShip == m_apShip[i]->GetNetworkShip())
		{
			m_apShip[i]->Release();
			SH_SAFE_DELETE(m_apShip[i]);
			m_apShip.Remove(i);
			break;
		}
	}
}

/**
 * @brief World::onShipStateChanged
 */
/*virtual*/ void World::onShipStateChanged(const Network::Ship * pNetworkShip)
{
	int iShipCount = m_apShip.GetCount();
	for (int iShip = 0; iShip < iShipCount; ++iShip)
	{
		Ship * pShip = m_apShip[iShip];
		if (pShip->GetNetworkShip() == pNetworkShip)
		{
			const Network::vec2 & shipPos = pNetworkShip->getPosition();
			const Network::vec2 & targetPos = pNetworkShip->getTarget();

			float direction = atan2(targetPos.x - shipPos.x, targetPos.y - shipPos.y) * 180 / SHC_PI;
			float fAngle = (-direction + 90)*SHC_DEG2RAD;

			pShip->SetAngle(fAngle);
		}
	}
}

/**
 * @brief World::onShipShooted
 */
/*virtual*/ void World::onShipShooted(const Network::Ship * pShip, const Network::Ship * pShooterShip)
{
	m_projectileManager.Start(ProjectileManager::e_projectile_bullet, CShVector2(pShooterShip->getPosition().x, pShooterShip->getPosition().y), CShVector2(pShip->getPosition().x, pShip->getPosition().y), 4.0f);
}

/**
* @brief World::onTransmitterCreate
*/
/*virtual*/ void World::onTransmitterCreated(const Network::Transmitter * pTrans)
{
	Network::vec2 pos = pTrans->getPosition();
	CreateTransmitter(pos.x, pos.y, pTrans);
}

/**
 * @brief World::onTransmitterDestroyed
 */
/*virtual*/ void World::onTransmitterDestroyed(const Network::Transmitter * pTrans)
{
	int nTransCount = m_apTransmitter.GetCount();
	for (int i = 0; i < nTransCount; ++i)
	{
		if (pTrans == m_apTransmitter[i]->GetNetworkTrans())
		{
			Transmitter * pTransmitter = m_apTransmitter[i];
			int nTeamCount = m_aTeam.GetCount();
			for (int j = 0; j < nTeamCount; ++j)
			{
				m_aTeam[j]->RemoveTransmitter(m_apTransmitter[i]);
			}
			
			m_apTransmitter.RemoveAll(m_apTransmitter[i]);
			
			SH_SAFE_DELETE(pTransmitter);
			break;
		}
	}
}

/**
 * @brief World::onTransmitterStateChanged
 */
/*virtual*/ void World::onTransmitterStateChanged(const Network::Transmitter * pTrans)
{
	// TODO
}

/**
 * @brief World::onTransmitterShooted
 */
/*virtual*/ void World::onTransmitterShooted(const Network::Transmitter * pTrans, const Network::Ship * pShooterShip)
{
	m_projectileManager.Start(ProjectileManager::e_projectile_bullet, CShVector2(pShooterShip->getPosition().x, pShooterShip->getPosition().y), CShVector2(pTrans->getPosition().x, pTrans->getPosition().y), 4.0f);
}

/**
* @brief World::Start
*/
void World::Start(unsigned int team, unsigned int eShipType)
{
	//
	// Create player's Ship
	Network::Ship * pNetworkShip = m_world.createShip(team, DEFAULT_SHIP_LIFE, eShipType, 0.0f, 0.0f);
	m_pShip = CreateShip(0.0f, 0.0f, pNetworkShip);

	if (m_pShip->GetTeam() == 0)
	{
		ShEntity2::SetColor(m_pShip->GetSprite(), CShRGBAf(0.0f, 0.0f, 1.0f, 1.0f));
	}
	else if (m_pShip->GetTeam() == 1)
	{
		ShEntity2::SetColor(m_pShip->GetSprite(), CShRGBAf(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		SH_ASSERT_ALWAYS();
	}

	m_pMiniMap->SetShip(m_pShip);
}

/**
* @brief World::CreateShip
*/
Ship * World::CreateShip(float x, float y, const Network::Ship * pNetworkShip)
{
	ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier(CShString("ship_") + CShString::FromInt(pNetworkShip->getType())), CShVector3(x, y, 1.1f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(0.15f, 0.15f, 1.0f));
	SH_ASSERT(shNULL != pEntity);
	Ship * pShip = new Ship(pEntity, CShVector2(x, y));
	pShip->Initialize((Ship::EShipType)(pNetworkShip->getType()), pNetworkShip, &m_projectileManager);

	if (pShip->GetTeam() == 0)
	{
		ShEntity2::SetColor(pEntity, CShRGBAf(0.0f, 0.0f, 1.0f, 1.0f));
	}
	else if (pShip->GetTeam() == 1)
	{
		ShEntity2::SetColor(pEntity, CShRGBAf(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		SH_ASSERT_ALWAYS();
	}

	m_apShip.Add(pShip);

	return(pShip);
}

/**
* @brief World::CreateTransmitter
*/
Transmitter * World::CreateTransmitter(float x, float y, const Network::Transmitter * pNetworkTrans)
{
	ShEntity2* pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("transmitter_01"), CShVector3(x, y, 2.01f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(0.8f, 0.8f, 1.0f));
	SH_ASSERT(shNULL != pEntity);
	Transmitter * pTrans = new Transmitter(pEntity, CShVector2(x, y));
	pTrans->Initialize(pNetworkTrans, m_apTransmitter.GetCount() - 1);
	pTrans->Start(CShVector2(x, y));
	m_apTransmitter.Add(pTrans);
	
	const int teamId = pNetworkTrans->getTeam();
	m_aTeam[teamId]->AddTransmitter(pTrans);

	return(pTrans);
}

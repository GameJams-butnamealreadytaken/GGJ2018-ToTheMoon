#include "MiniMap.h"

#include "../GameObjects/Planet/Planet.h"
#include "../GameObjects/Ship/Ship.h"
#include "../GameObjects/Transmitter/Transmitter.h"

#define POSITION_OFFSET_X 76.8f
#define POSITION_OFFSET_Y 43.2f

/**
 * @brief Constructor
 */
MiniMap::MiniMap(void)
: m_levelIdentifier()
, m_pWorld(shNULL)
, m_pEntityBackground(shNULL)
, m_fWidth(0.0f)
, m_fHeight(0.0f)
, m_fRatio(0.0f)
, m_vPosition()
, m_pShip(shNULL)
, m_apShip()
, m_apTransmitter()
, m_iShipCount(0)
, m_iTransmitterCount(0)
{

}

/**
 * @brief Destructor
 */
MiniMap::~MiniMap(void)
{
	// ...
}

/**
* @brief Initialize
*/
void MiniMap::Initialize(const CShIdentifier & levelIdentifier, World * pWorld)
{
	m_levelIdentifier = levelIdentifier;
	m_pWorld = pWorld;
	m_fWidth = 2048.0f * 5.0f / 10.0f;
	m_fHeight = 1152.0f * 5.0f / 10.0f;
	m_fRatio = 0.1f;

	m_pEntityBackground = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("minimap_background"), CShVector3(0.0f, 0.0f, 100.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
	SH_ASSERT(shNULL != m_pEntityBackground);
	ShEntity2::SetAlpha(m_pEntityBackground, 0.8f);

	ShEntity2::SetWorldPosition2(m_pEntityBackground, CShVector2(ShDisplay::GetWidth() * 0.5f - ShEntity2::GetWidth(m_pEntityBackground) * 0.5f - POSITION_OFFSET_X,-ShDisplay::GetHeight() * 0.5f + ShEntity2::GetWidth(m_pEntityBackground) * 0.5f + POSITION_OFFSET_Y));

	m_vPosition = ShEntity2::GetPosition2(m_pEntityBackground);

	//
	// Planets
	int iPlanetCount = m_pWorld->GetPlanetCount();
	for (int iPlanet = 0; iPlanet < iPlanetCount; ++iPlanet)
	{
		Planet * pPlanet = m_pWorld->GetPlanet(iPlanet);

		ShEntity2* pEntityPlanet = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("planet"), CShVector3(0.0f, 0.0f, 101.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
		m_apPlanet.Add(pEntityPlanet);
		ShEntity2::Link(m_pEntityBackground, pEntityPlanet);

		switch (pPlanet->GetPlanet())
		{
			case Planet::e_planet_earth:	{ ShEntity2::SetColor(pEntityPlanet, CShRGBAf(0.184f,0.752f, 0.937f, 1.0f)); }	break;
			case Planet::e_planet_jupiter:	{ ShEntity2::SetColor(pEntityPlanet, CShRGBAf(0.843f,0.517f, 0.0f, 1.0f)); }	break;
			case Planet::e_planet_mars:		{ ShEntity2::SetColor(pEntityPlanet, CShRGBAf(1.0f, 0.219f, 0.392f, 1.0f)); }	break;
			case Planet::e_planet_moon:		{ ShEntity2::SetColor(pEntityPlanet, CShRGBAf(0.44f, 0.439f, 0.439f, 1.0f)); }	break;
		}

		ShEntity2::SetPosition2(pEntityPlanet, pPlanet->GetPosition2() * m_fRatio * 0.5f);
	}

	//
	// Ships
	m_pShip = m_pWorld->GetMyShip();
	
	int iShipCount = m_pWorld->GetShipCount();
	for (int iShip = 0; iShip < iShipCount; ++iShip)
	{
		char szSpriteIdentifier[1024];	
		Ship * pShip = m_pWorld->GetShip(iShip);

		//if (pShip == m_pShip)
		//{
		//	sprintf(szSpriteIdentifier, "minimap_ship_main");
		//}
		//else
		{
			if (pShip->GetTeam() == 0)
			{
				sprintf(szSpriteIdentifier, "minimap_ship_blue");
			}
			else if (pShip->GetTeam() == 1)
			{
				sprintf(szSpriteIdentifier, "minimap_ship_red");
			}
			else
			{
				SH_ASSERT_ALWAYS();
			}
		}

		ShEntity2* pEntityShip = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier(szSpriteIdentifier), CShVector3(0.0f, 0.0f, 103.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
		m_apShip.Add(pEntityShip);
		ShEntity2::Link(m_pEntityBackground, pEntityShip);
		m_iShipCount++;
	}

	//
	// Transmitters
	int iTransmitterCount = m_pWorld->GetTransmitterCount();
	for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
	{
		char szSpriteIdentifier[1024];
		Transmitter * pTransmitter = m_pWorld->GetTransmitter(iTransmitter);

		if (pTransmitter->GetTeam() == 0)
		{
			sprintf(szSpriteIdentifier, "minimap_transmitter_blue");
		}
		else if (pTransmitter->GetTeam() == 1)
		{
			sprintf(szSpriteIdentifier, "minimap_transmitter_red");
		}
		else
		{
			SH_ASSERT_ALWAYS();
		}

		ShEntity2* pEntityTransmitter = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier(szSpriteIdentifier), CShVector3(0.0f, 0.0f, 102.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
		m_apTransmitter.Add(pEntityTransmitter);
		ShEntity2::Link(m_pEntityBackground, pEntityTransmitter);
		m_iTransmitterCount++;
	}
}

/**
* @brief Release
*/
void MiniMap::Release(void)
{
	m_apShip.Empty();
	m_apTransmitter.Empty();
	m_apPlanet.Empty();
}

/**
* @brief Update
*/
void MiniMap::Update(float dt)
{
	ShCamera* pCamera = ShCamera::GetCamera2D();
	ShEntity2::SetWorldPosition2(m_pEntityBackground, ShCamera::GetPosition2(pCamera) + CShVector2(ShCamera::GetViewport(pCamera).m_x * 0.5f - ShEntity2::GetWidth(m_pEntityBackground) * ShEntity2::GetScale(m_pEntityBackground).m_x * 0.5f - POSITION_OFFSET_X, -ShCamera::GetViewport(pCamera).m_y * 0.5f + ShEntity2::GetHeight(m_pEntityBackground)  * ShEntity2::GetScale(m_pEntityBackground).m_y * 0.5f + POSITION_OFFSET_Y));
	m_vPosition = ShEntity2::GetPosition2(m_pEntityBackground);

	//
	// Ships
	int iShipCount = m_pWorld->GetShipCount();
	for (int iShip = 0; iShip < iShipCount; ++iShip)
	{
		if (iShip > m_iShipCount - 1)
		{
			char szSpriteIdentifier[1024];
			Ship * pShip = m_pWorld->GetShip(iShip);

			if (pShip->GetTeam() == 0)
			{
				sprintf(szSpriteIdentifier, "minimap_ship_blue");
			}
			else if (pShip->GetTeam() == 1)
			{
				sprintf(szSpriteIdentifier, "minimap_ship_red");
			}
			else
			{
				SH_ASSERT_ALWAYS();
			}

			ShEntity2* pEntityShip = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier(szSpriteIdentifier), CShVector3(0.0f, 0.0f, 103.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_apShip.Add(pEntityShip);
			ShEntity2::Link(m_pEntityBackground, pEntityShip);
			m_iShipCount++;
		}
	
		Ship * pShip = m_pWorld->GetShip(iShip);
		ShEntity2::SetWorldPosition2(m_apShip[iShip], m_vPosition + pShip->GetPosition2() * CShVector2(m_fRatio, m_fRatio) * 0.5f);
		ShEntity2::SetRotation(m_apShip[iShip], pShip->GetRotation());
	}

	//
	// Transmitters
	int iTransmitterCount = m_pWorld->GetTransmitterCount();
	for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
	{
		if (iTransmitter > m_iTransmitterCount - 1)
		{
			char szSpriteIdentifier[1024];
			Transmitter * pTransmitter = m_pWorld->GetTransmitter(iTransmitter);

			if (pTransmitter->GetTeam() == 0)
			{
				sprintf(szSpriteIdentifier, "minimap_transmitter_blue");
			}
			else if (pTransmitter->GetTeam() == 1)
			{
				sprintf(szSpriteIdentifier, "minimap_transmitter_red");
			}
			else
			{
				SH_ASSERT_ALWAYS();
			}

			ShEntity2* pEntityTransmitter = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier(szSpriteIdentifier), CShVector3(0.0f, 0.0f, 102.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_apTransmitter.Add(pEntityTransmitter);
			ShEntity2::Link(m_pEntityBackground, pEntityTransmitter);
			m_iTransmitterCount++;
		}

		Transmitter * pTransmitter = m_pWorld->GetTransmitter(iTransmitter);
		ShEntity2::SetWorldPosition2(m_apTransmitter[iTransmitter], m_vPosition + pTransmitter->GetPosition2() * CShVector2(m_fRatio, m_fRatio) * 0.5f);
	}
}

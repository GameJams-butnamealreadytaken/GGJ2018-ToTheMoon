#include "MiniMap.h"

#include "../GameObjects/Ship/Ship.h"
#include "../GameObjects/Transmitter/Transmitter.h"

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

	m_pEntityBackground = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("minimap_background"), CShVector3(0.0f, 0.0f, 100.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(m_fWidth / 10.0f, m_fHeight / 10.0f, 1.0f));
	SH_ASSERT(shNULL != m_pEntityBackground);

	ShEntity2::SetWorldPosition2(m_pEntityBackground, CShVector2(ShDisplay::GetWidth() * 0.5f - ShEntity2::GetWidth(m_pEntityBackground) * 0.5f,-ShDisplay::GetHeight() * 0.5f + ShEntity2::GetWidth(m_pEntityBackground) * 0.5f));

	m_vPosition = ShEntity2::GetPosition2(m_pEntityBackground);

	//
	// Ships
	int iShipCount = m_pWorld->GetShipCount();
	for (int iShip = 0; iShip < iShipCount; ++iShip)
	{
		ShEntity2* pEntityShip = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("minimap_ship"), CShVector3(0.0f, 0.0f, 101.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
		m_apShip.Add(pEntityShip);
		ShEntity2::Link(m_pEntityBackground, pEntityShip);
	}

	//
	// Transmitters
	int iTransmitterCount = m_pWorld->GetTransmitterCount();
	for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
	{
		ShEntity2* pEntityTransmitter = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("minimap_transmitter"), CShVector3(0.0f, 0.0f, 101.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
		m_apTransmitter.Add(pEntityTransmitter);
		ShEntity2::Link(m_pEntityBackground, pEntityTransmitter);
	}
}

/**
* @brief Release
*/
void MiniMap::Release(void)
{

}

/**
* @brief Update
*/
void MiniMap::Update(float dt)
{
	ShCamera* pCamera = ShCamera::GetCamera2D();
	ShEntity2::SetWorldPosition2(m_pEntityBackground, ShCamera::GetPosition2(pCamera) + CShVector2(ShCamera::GetViewport(pCamera).m_x * 0.5f - ShEntity2::GetWidth(m_pEntityBackground) * ShEntity2::GetScale(m_pEntityBackground).m_x * 0.5f, -ShCamera::GetViewport(pCamera).m_y * 0.5f + ShEntity2::GetHeight(m_pEntityBackground)  * ShEntity2::GetScale(m_pEntityBackground).m_y * 0.5f));
	m_vPosition = ShEntity2::GetPosition2(m_pEntityBackground);

	//
	// Ships
	int iShipCount = m_pWorld->GetShipCount();
	for (int iShip = 0; iShip < iShipCount; ++iShip)
	{
		if (iShip > m_iShipCount - 1)
		{
			ShEntity2* pEntityShip = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("minimap_ship"), CShVector3(0.0f, 0.0f, 101.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_apShip.Add(pEntityShip);
			ShEntity2::Link(m_pEntityBackground, pEntityShip);
			m_iShipCount++;
		}

		Ship * pShip = m_pWorld->GetShip(iShip);
		ShEntity2::SetWorldPosition2(m_apShip[iShip], m_vPosition + pShip->GetPosition2() * CShVector2(m_fRatio, m_fRatio) * 0.5f);
	}

	//
	// Transmitters
	int iTransmitterCount = m_pWorld->GetTransmitterCount();
	for (int iTransmitter = 0; iTransmitter < iTransmitterCount; ++iTransmitter)
	{
		if (iTransmitter > m_iTransmitterCount - 1)
		{
			ShEntity2* pEntityTransmitter = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj"), CShIdentifier("minimap_transmitter"), CShVector3(0.0f, 0.0f, 101.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			m_apTransmitter.Add(pEntityTransmitter);
			ShEntity2::Link(m_pEntityBackground, pEntityTransmitter);
			m_iTransmitterCount++;
		}

		Transmitter * pTransmitter = m_pWorld->GetTransmitter(iTransmitter);
		ShEntity2::SetWorldPosition2(m_apTransmitter[iTransmitter], m_vPosition + pTransmitter->GetPosition2() * CShVector2(m_fRatio, m_fRatio) * 0.5f);
	}
}

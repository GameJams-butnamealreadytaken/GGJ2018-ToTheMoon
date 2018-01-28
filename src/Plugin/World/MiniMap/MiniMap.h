#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../World.h"

class MiniMap 
{
public:
	explicit								MiniMap				(void);
	virtual									~MiniMap			(void);

	void									Initialize			(const CShIdentifier & levelIdentifier, World * pWorld);
	void									Release				(void);

	void									Update				(float dt);

	void									SetShip				(Ship * pShip);

private:
	void									CreateShip			(Ship * pShip);
	void									CreateTransmitter	(Transmitter * pTransmitter);

protected:
	CShIdentifier	m_levelIdentifier;
	World *			m_pWorld;

	ShEntity2*	m_pEntityBackground;

	float	m_fWidth;
	float	m_fHeight;
	float   m_fRatio;
	
	CShVector2 m_vPosition;

	Ship*					m_pShip;
	CShArray<ShEntity2*>	m_apShip;
	CShArray<ShEntity2*>	m_apTransmitter;
	CShArray<ShEntity2*>	m_apPlanet;

	int						m_iShipCount;
	int						m_iTransmitterCount;
};

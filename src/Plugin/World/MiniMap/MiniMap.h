#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "../World.h"

class World;

class MiniMap 
{
public:
	explicit								MiniMap				(void);
	virtual									~MiniMap			(void);

	void									Initialize			(World * pWorld);
	void									Release				(void);

	void									Update				(float dt);

protected:
	World * m_pWorld;
	float	m_fRatio;
};

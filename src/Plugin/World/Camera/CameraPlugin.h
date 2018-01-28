#pragma once

#include "ShSDK/ShSDK.h"

struct ShCamera;
class PluginInputs;

class CameraPlugin
{
public:
	explicit	 CameraPlugin		(CShVector2 halfSize);
	virtual		~CameraPlugin		(void);

	void		Initialize			(PluginInputs * pInputs);
	void		Release				(void);

	void		Update				(float dt, const CShVector2 & shipPos);

private:
	void		ClampPosition		(void);

private:

	ShCamera *		m_pCamera;
	PluginInputs *	m_pInputs;

	CShVector2		m_halfSize;

	bool			m_bLocked;
};

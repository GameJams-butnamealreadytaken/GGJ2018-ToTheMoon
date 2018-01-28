#pragma once

#include "ShSDK/ShSDK.h"

struct ShCamera;
class PluginInputs;

class CameraPlugin
{
public:
	explicit	 CameraPlugin		(void);
	virtual		~CameraPlugin		(void);

	void		Initialize			(PluginInputs * pInputs);
	void		Release				(void);

	void		Update				(float dt, const CShVector2 & shipPos);

private:

	ShCamera *		m_pCamera;
	PluginInputs *	m_pInputs;
	bool			m_bLocked;
};

#pragma once

struct ShUser;

class PluginInputs
{
public:
	explicit	 PluginInputs		(void);
	virtual		~PluginInputs		(void);

	void		Initialize			(ShUser * pUser);
	void		Release				(void);

	void		Update				(void);

	bool		LaunchedBeacon		(void);
	bool		CameraModeChanged	(void);
private:

	ShUser *	m_pUser;

	bool		m_bLaunchBeacon;
	bool		m_bCameraType;
};


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

	bool		IsCameraUp			(void);
	bool		IsCameraDown		(void);
	bool		IsCameraLeft		(void);
	bool		IsCameraRight		(void);



private:

	ShUser *	m_pUser;

	bool		m_bLaunchBeacon;
	bool		m_bCameraType;
	bool		m_bCameraUp;
	bool		m_bCameraDown;
	bool		m_bCameraLeft;
	bool		m_bCameraRight;
};


#include "InputManager.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
PluginInputs::PluginInputs(void)
	: m_pUser(shNULL)
	, m_bLaunchBeacon(false)
	, m_bCameraType(false)
	, m_bCameraUp(false)
	, m_bCameraDown(false)
	, m_bCameraLeft(false)
	, m_bCameraRight(false)
{
	// ...
}

/**
 * @brief Destructor
 */
PluginInputs::~PluginInputs(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void PluginInputs::Initialize(ShUser * pUser)
{
	SH_ASSERT(shNULL != pUser);
	m_pUser = pUser;
}

/**
 * @brief Release
 */
void PluginInputs::Release(void)
{
	// ...
}

/**
 * @brief Inputs::Update
 */
void PluginInputs::Update(void)
{
	if (shNULL != m_pUser)
	{
		m_bLaunchBeacon = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("beacon"));
		m_bCameraType = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("camera_mode"));

		m_bCameraUp = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("up"));
		m_bCameraDown = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("down"));
		m_bCameraLeft = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("left"));
		m_bCameraRight = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("right"));
	}
}

bool PluginInputs::LaunchedBeacon(void)
{
	return(m_bLaunchBeacon);
}

bool PluginInputs::CameraModeChanged(void)
{
	return(m_bCameraType);
}

bool PluginInputs::IsCameraUp(void)
{
	return(m_bCameraUp);
}

bool PluginInputs::IsCameraDown(void)
{
	return(m_bCameraDown);
}

bool PluginInputs::IsCameraLeft(void)
{
	return(m_bCameraLeft);
}

bool PluginInputs::IsCameraRight(void)
{
	return(m_bCameraRight);
}

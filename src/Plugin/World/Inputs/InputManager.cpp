#include "InputManager.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
PluginInputs::PluginInputs(void)
	: m_pUser(shNULL)
	, m_bLaunchBeacon(false)
	, m_bCameraType(false)
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

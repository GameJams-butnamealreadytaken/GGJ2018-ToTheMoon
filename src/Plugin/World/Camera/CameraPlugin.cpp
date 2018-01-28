#include "CameraPlugin.h"

#include "ShSDK/ShSDK.h"

#include "../Inputs/InputManager.h"

/**
 * @brief Constructor
 */
CameraPlugin::CameraPlugin(void)
	: m_pCamera(shNULL)
	, m_bLocked(true)
{
	// ...
}

/**
 * @brief Destructor
 */
CameraPlugin::~CameraPlugin(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void CameraPlugin::Initialize(PluginInputs * pInputs)
{
	m_pCamera = ShCamera::GetCamera2D();
	SH_ASSERT(m_pCamera);

	SH_ASSERT(shNULL != pInputs);
	m_pInputs = pInputs;
}

/**
 * @brief Release
 */
void CameraPlugin::Release(void)
{
	// ...
}

/**
 * @brief CameraPlugin::Update
 */
void CameraPlugin::Update(float dt, const CShVector2 & shipPos)
{
	m_pCamera = ShCamera::GetCamera2D();
	SH_ASSERT(m_pCamera);

	if (m_pInputs->CameraModeChanged())
	{
		m_bLocked = !m_bLocked;
	}

	if (m_bLocked)
	{
		ShCamera::SetPosition2(m_pCamera, shipPos);
		ShCamera::SetTarget(m_pCamera, CShVector3(shipPos, 0.0f));
	}
	else
	{
		if (m_pInputs->IsCameraUp())
		{
			ShCamera::Translate(m_pCamera, CShVector3(0.0f, 50.0f, 0.0f));
		}
		else if (m_pInputs->IsCameraDown())
		{
			ShCamera::Translate(m_pCamera, CShVector3(0.0f, -50.0f, 0.0f));
		}

		if (m_pInputs->IsCameraRight())
		{
			ShCamera::Translate(m_pCamera, CShVector3(50.0f, 0.0f, 0.0f));
		}
		else if (m_pInputs->IsCameraLeft())
		{
			ShCamera::Translate(m_pCamera, CShVector3(-50.0f, 0.0f, 0.0f));
		}

		ShCamera::SetTarget(m_pCamera, CShVector3(ShCamera::GetWorldPosition2(m_pCamera), 0.0f));
	}
}

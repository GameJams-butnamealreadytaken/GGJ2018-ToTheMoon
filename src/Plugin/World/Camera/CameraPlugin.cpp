#include "CameraPlugin.h"

#include "ShSDK/ShSDK.h"

#include "../Inputs/InputManager.h"

/**
 * @brief Constructor
 */
CameraPlugin::CameraPlugin(CShVector2 halfSize)
	: m_pCamera(shNULL)
	, m_halfSize(halfSize)
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
		float speed = 50.0f * 60.0f * dt;
		if (m_pInputs->IsCameraUp())
		{
			ShCamera::Translate(m_pCamera, CShVector3(0.0f, speed, 0.0f));
		}
		else if (m_pInputs->IsCameraDown())
		{
			ShCamera::Translate(m_pCamera, CShVector3(0.0f, -speed, 0.0f));
		}

		if (m_pInputs->IsCameraRight())
		{
			ShCamera::Translate(m_pCamera, CShVector3(speed, 0.0f, 0.0f));
		}
		else if (m_pInputs->IsCameraLeft())
		{
			ShCamera::Translate(m_pCamera, CShVector3(-speed, 0.0f, 0.0f));
		}

		ClampPosition();
	}
}

void CameraPlugin::ClampPosition(void)
{
	CShVector2 camPos = ShCamera::GetWorldPosition2(m_pCamera);

	// Clamp X
	if (camPos.m_x > m_halfSize.m_x)
	{
		camPos.m_x = m_halfSize.m_x;
	}
	else if (camPos.m_x < -m_halfSize.m_x)
	{
		camPos.m_x = -m_halfSize.m_x;
	}

	// Clamp Y
	if (camPos.m_y > m_halfSize.m_y)
	{
		camPos.m_y = m_halfSize.m_y;
	}
	else if (camPos.m_y < -m_halfSize.m_y)
	{
		camPos.m_y = -m_halfSize.m_y;
	}

	ShCamera::SetWorldPosition2(m_pCamera, camPos);
	ShCamera::SetTarget(m_pCamera, CShVector3(camPos, 0.0f));
}

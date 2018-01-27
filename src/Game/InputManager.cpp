#include "InputManager.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
Inputs::Inputs(void) : m_pUser(shNULL), m_isRestarting(false), m_isPressEnter(false), m_isPressEscape(false)
{
	// ...
}

/**
 * @brief Destructor
 */
Inputs::~Inputs(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void Inputs::Initialize(ShUser * pUser)
{
	m_pUser = pUser;
}

/**
 * @brief Release
 */
void Inputs::Release(void)
{
	// ...
}

/**
 * @brief Inputs::Update
 */
void Inputs::Update(void)
{
	if (shNULL != m_pUser)
	{
		m_isPressEnter = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("validate"));
		m_isRestarting = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("reset"));
		m_isPressEscape = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("pause"));
	}
}

/**
 * @brief Inputs::IsRestarting
 * @return
 */
bool Inputs::IsRestarting(void)
{
	return(m_isRestarting);
}

/**
 * @brief Inputs::IsPressEnter
 * @return
 */
bool Inputs::IsPressEnter(void)
{
	return(m_isPressEnter);
}

/**
* @brief Inputs::IsPressEscape
* @return
*/
bool Inputs::IsPressEscape(void)
{
	return(m_isPressEscape);
}

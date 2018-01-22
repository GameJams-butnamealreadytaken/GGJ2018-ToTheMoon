#include "Plugin.h"

const CShIdentifier plugin_identifier("PluginGGJ2018");

/**
 * @brief Constructor
 */
PluginGGJ2018::PluginGGJ2018(void)
: CShPlugin(plugin_identifier)
{
	// ...
}

/**
 * @brief Destructor
 */
PluginGGJ2018::~PluginGGJ2018(void)
{
	// ...
}

/**
 * @brief OnPlayStart
 * @param levelIdentifier
 */
void PluginGGJ2018::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	ShCamera * pCurrentCamera = ShCamera::GetCamera2D();
	const CShVector2 & viewport = ShCamera::GetViewport(pCurrentCamera);

	m_levelIdentifier = levelIdentifier;
}

/**
 * @brief OnPlayStop
 * @param levelIdentifier
 */
void PluginGGJ2018::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	m_levelIdentifier = GID(NULL);
}

/**
 * @brief OnPreUpdate
 */
void PluginGGJ2018::OnPreUpdate(float dt)
{

}

/**
* @brief OnPostUpdate
* @param dt
*/
void PluginGGJ2018::OnPostUpdate(float dt)
{
	
}

/**
 * @brief PluginGGJ2018::OnTouchDown
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchDown(int iTouch, float positionX, float positionY)
{
	// ...
}


/**
 * @brief PluginGGJ2018::OnTouchUp
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchUp(int iTouch, float positionX, float positionY)
{
	
}

/**
 * @brief PluginGGJ2018::OnTouchMove
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchMove(int iTouch, float positionX, float positionY)
{
	// ...
}

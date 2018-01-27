#include "Plugin.h"
#include "Sound/SoundManager.h"

extern SoundManager g_soundManager;
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

	g_soundManager.Initialize();
	g_soundManager.PlayMusic(SoundManager::e_sound_music_game);
	m_world.Initialize(m_levelIdentifier);
}

/**
 * @brief OnPlayStop
 * @param levelIdentifier
 */
void PluginGGJ2018::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	m_world.Release();
	g_soundManager.Release();

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
	m_world.Update(dt);
}

/**
 * @brief PluginGGJ2018::OnTouchDown
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchDown(int iTouch, float positionX, float positionY)
{
	m_world.OnTouchDown(iTouch, positionX, positionY);
}


/**
 * @brief PluginGGJ2018::OnTouchUp
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchUp(int iTouch, float positionX, float positionY)
{
	m_world.OnTouchUp(iTouch, positionX, positionY);
}

/**
 * @brief PluginGGJ2018::OnTouchMove
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchMove(int iTouch, float positionX, float positionY)
{
	m_world.OnTouchMove(iTouch, positionX, positionY);
}

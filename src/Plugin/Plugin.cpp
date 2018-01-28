#include "Plugin.h"
#include "Sound/SoundManager.h"

extern SoundManager g_soundManager;
const CShIdentifier plugin_identifier("PluginGGJ2018");

bool g_bDisableAnimations = false;

/**
 * @brief Constructor
 */
PluginGGJ2018::PluginGGJ2018(void)
: CShPlugin(plugin_identifier)
, m_fTouchRatio(3.0f)
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
	m_levelIdentifier = levelIdentifier;

	const CShVector2 & viewport = ShCamera::GetViewport(ShCamera::GetCamera2D());
	float ratio_x = viewport.m_x / ShDisplay::GetWidth();
	float ratio_y = viewport.m_y / ShDisplay::GetHeight();
	
	m_fTouchRatio = shMax(ratio_x, ratio_y, 2.0f);

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
	m_world.OnTouchDown(iTouch, positionX * m_fTouchRatio, positionY * m_fTouchRatio);
}

/**
 * @brief PluginGGJ2018::OnTouchUp
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchUp(int iTouch, float positionX, float positionY)
{
	m_world.OnTouchUp(iTouch, positionX * m_fTouchRatio, positionY * m_fTouchRatio);
}

/**
 * @brief PluginGGJ2018::OnTouchMove
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2018::OnTouchMove(int iTouch, float positionX, float positionY)
{
	m_world.OnTouchMove(iTouch, positionX * m_fTouchRatio, positionY * m_fTouchRatio);
}

/**
 * @brief PluginGGJ2018::Start
 * @param team
 */
void PluginGGJ2018::Start(int team, unsigned int eShipType)
{
	m_world.Start(team, eShipType);
}

/**
 * @brief PluginGGJ2018::GetWorld
 */
World * PluginGGJ2018::GetWorld(void)
{
	return(&m_world);
}

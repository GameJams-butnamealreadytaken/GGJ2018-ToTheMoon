#include "PluginFactory.h"

#include "Plugin.h"

static PluginGGJ2018 * g_pInstance = shNULL;

extern "C"
{

/**
 * @brief RegisterGGJ2018Plugin
 */
PLUGIN_FACTORY_EXPORT void RegisterGGJ2018Plugin(void)
{
	if (!g_pInstance)
	{
		g_pInstance = new PluginGGJ2018();
	}

	ShApplication::RegisterPlugin(g_pInstance);
}

/**
 * @brief UnRegisterGGJ2018Plugin
 */
PLUGIN_FACTORY_EXPORT void UnRegisterGGJ2018Plugin(void)
{
	ShApplication::UnRegisterPlugin(g_pInstance);
}

/**
 * @brief GetGGJ2018Plugin
 * @return
 */
PLUGIN_FACTORY_EXPORT PluginGGJ2018 * GetGGJ2018Plugin(void)
{
	return(g_pInstance);
}

/**
 * @brief TouchDownGGJ2018Plugin
 * @param iTouch
 * @param positionX
 * @param positionY
 */
PLUGIN_FACTORY_EXPORT void TouchDownGGJ2018Plugin(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchDown(iTouch, positionX, positionY);
}

/**
 * @brief TouchUpGGJ2018Plugin
 * @param iTouch
 * @param positionX
 * @param positionY
 */
PLUGIN_FACTORY_EXPORT void TouchUpGGJ2018Plugin(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchUp(iTouch, positionX, positionY);
}

/**
 * @brief TouchMoveGGJ2018Plugin
 * @param iTouch
 * @param positionX
 * @param positionY
 */
PLUGIN_FACTORY_EXPORT void TouchMoveGGJ2018Plugin(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchMove(iTouch, positionX, positionY);
}

}

#pragma once

#if defined(_WIN32)
#	if defined(Plugin_Editor_EXPORTS)
#		define PLUGIN_FACTORY_EXPORT __declspec(dllexport)
#	else
#		define PLUGIN_FACTORY_EXPORT //__declspec(dllimport)
#	endif // Plugin_Editor_EXPORTS
#else // defined(_WIN32)
#	define PLUGIN_FACTORY_EXPORT
#endif

class PluginGGJ2018;

extern "C"
{
	PLUGIN_FACTORY_EXPORT void					RegisterGGJ2018Plugin		(void);
	PLUGIN_FACTORY_EXPORT void					UnRegisterGGJ2018Plugin		(void);
	PLUGIN_FACTORY_EXPORT PluginGGJ2018 *		GetGGJ2018Plugin			(void);

	PLUGIN_FACTORY_EXPORT void					TouchDownGGJ2018Plugin		(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchUpGGJ2018Plugin		(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchMoveGGJ2018Plugin		(int iTouch, float positionX, float positionY);
}

#include "Extension.h"

#include "ShSDK/ShSDK.h"

#include "PluginFactory.h"
#include "Plugin.h"

typedef void (*register_fn)(void);
typedef void (*unregister_fn)(void);
typedef PluginGGJ2018 * (*get_instance_fn)(void);

static register_fn pRegister			= shNULL;
static unregister_fn pUnRegister		= shNULL;
static get_instance_fn pGetInstance		= shNULL;

static FuncOnTouchDownPtr pOnTouchDown	= shNULL;
static FuncOnTouchUpPtr pOnTouchUp		= shNULL;
static FuncOnTouchMovePtr pOnTouchMove	= shNULL;

#ifdef PLUGIN_PATH
static const CShString strPluginFilePath(PLUGIN_PATH);
#else
#	error "Plugin path not defined"
#endif

static CShDynamicLibrary plugin_library(strPluginFilePath);

bool g_bDisableAnimations = false;

extern "C"
{

EXTENSION_EXPORT void ExtensionInitialize(void)
{
	// ...
}

EXTENSION_EXPORT void ExtensionRelease(void)
{
	// ...
}

EXTENSION_EXPORT void ExtensionOnPluginStarted(const CShIdentifier & levelIdentifier)
{
	//
	// Load Library
	bool bInit = plugin_library.Initialize();

	//
	// Get Functions
	if (bInit)
	{
		pRegister = (register_fn)plugin_library.GetFunctionAddress(CShString("RegisterGGJ2018Plugin"));
		SH_ASSERT(shNULL != pRegister);

		pUnRegister = (register_fn)plugin_library.GetFunctionAddress(CShString("UnRegisterGGJ2018Plugin"));
		SH_ASSERT(shNULL != pUnRegister);

		pGetInstance = (get_instance_fn)plugin_library.GetFunctionAddress(CShString("GetGGJ2018Plugin"));
		SH_ASSERT(shNULL != pGetInstance);

		pOnTouchDown = (FuncOnTouchDownPtr)plugin_library.GetFunctionAddress(CShString("TouchDownGGJ2018Plugin"));
		SH_ASSERT(shNULL != pOnTouchDown);

		pOnTouchUp = (FuncOnTouchUpPtr)plugin_library.GetFunctionAddress(CShString("TouchUpGGJ2018Plugin"));
		SH_ASSERT(shNULL != pOnTouchUp);

		pOnTouchMove = (FuncOnTouchMovePtr)plugin_library.GetFunctionAddress(CShString("TouchMoveGGJ2018Plugin"));
		SH_ASSERT(shNULL != pOnTouchMove);
	}

	//
	// Call factory (auto-register)
	if (shNULL != pRegister)
	{
		pRegister();

		ShInput::AddOnTouchDown(pOnTouchDown);
		ShInput::AddOnTouchUp(pOnTouchUp);
		ShInput::AddOnTouchMove(pOnTouchMove);
	}
}

EXTENSION_EXPORT void ExtensionOnPluginStopped(const CShIdentifier & levelIdentifier)
{
	//
	// Call factory (auto-unregister)
	if (shNULL != pUnRegister)
	{
		ShInput::RemoveOnTouchDown(pOnTouchDown);
		ShInput::RemoveOnTouchUp(pOnTouchUp);
		ShInput::RemoveOnTouchMove(pOnTouchMove);

		pUnRegister();
	}

	//
	// Reset function pointers
	{
		pGetInstance = shNULL;
		pUnRegister = shNULL;
		pRegister = shNULL;
	}

	//
	// Unload Library
	plugin_library.Release();
}

}

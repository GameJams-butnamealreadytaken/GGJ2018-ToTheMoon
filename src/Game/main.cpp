#include "ShSDK/ShSDK.h"

#include "application.h"

extern bool g_bDisableAnimations;

#if SH_PC

#include <shellapi.h>

void ParseArgumentsWindows(void)
{
	int nArgs = 0;
	LPWSTR * szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

	if (nullptr != szArglist)
	{
		for (int i = 0; i < nArgs; ++i)
		{
			if (!wcscmp(szArglist[i], L"--disable-animations"))
			{
				g_bDisableAnimations = true;
			}
		}

		// Free memory allocated for CommandLineToArgvW arguments.
		LocalFree(szArglist);
	}
}
#else
void ParseArguments(int argc, char ** argv)
{
	for (int i = 0; i < argc; ++i)
	{
		if (!strcmp(argv[i], "--disable-animations"))
		{
			g_bDisableAnimations = true;
		}
	}
}
#endif // SH_LINUX

#if SH_PC
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	ParseArgumentsWindows();
#else
int main(int argc, char ** argv)
{
	ParseArguments(argc, argv);
#endif

	ShApplication::SetOnPreInitialize(OnPreInitialize);
	ShApplication::SetOnPostInitialize(OnPostInitialize);
	ShApplication::SetOnPreUpdate(OnPreUpdate);
	ShApplication::SetOnPostUpdate(OnPostUpdate);
	ShApplication::SetOnPreRelease(OnPreRelease);
	ShApplication::SetOnPostRelease(OnPostRelease);

	ShDisplayProperties displayProperties;

	displayProperties.m_bLandscape = true;
	displayProperties.m_width = 1280;
	displayProperties.m_height = 720;

	displayProperties.m_bEnable3d = false;
	displayProperties.m_bEnableZ = false;
	displayProperties.m_bUseSpecular = false;
	displayProperties.m_bUsePointLights = false;
	displayProperties.m_bUseShadows = false;

#if SH_PC
	return(ShMain((void*)&hInstance, displayProperties));
#else
	return(ShMain(argc, argv, displayProperties));
#endif
}

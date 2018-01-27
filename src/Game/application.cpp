#include "application.h"
#include "Game.h"
#include "inputs.h"

#include "PluginFactory.h"

#if SH_PC
#	include <winsock2.h>
#	include <ws2tcpip.h>
#endif // SH_PC

extern "C"
{

/**
 * @brief OnPreInitialize
 */
void OnPreInitialize(void)
{
#if SH_PC
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		SH_TRACE(">>> Error initializing Winsock 2.2");
		WSACleanup();
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		SH_TRACE(">>> Winsock 2.2 not available");
		WSACleanup();
		return;
	}

	SH_TRACE("\nWinsock 2.2 initialized via wsa2_32.dll");
#endif // SH_PC

	ShInput::AddOnTouchDown(OnTouchDown);
	ShInput::AddOnTouchUp(OnTouchUp);
	ShInput::AddOnTouchMove(OnTouchMove);

	ShUser::RegisterLoginCallback(OnLogin);
	ShUser::RegisterLogoutCallback(OnLogout);
}

/**
 * @brief OnPostInitialize
 */
void OnPostInitialize(void)
{
	RegisterGGJ2018Plugin();

	Game & game = Game::instance();
	game.initialize();
}

/**
 * @brief OnPreUpdate
 * @param dt
 */
void OnPreUpdate(float dt)
{
	Game & game = Game::instance();
	game.update(dt);
}

/**
 * @brief OnPostUpdate
 * @param dt
 */
void OnPostUpdate(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief OnPreRelease
 */
void OnPreRelease(void)
{
	Game & game = Game::instance();
	game.release();

	UnRegisterGGJ2018Plugin();
}

/**
 * @brief OnPostRelease
 */
void OnPostRelease(void)
{
#if WIN32
	WSACleanup();
#endif
}

/**
 * @brief OnActivate
 */
void OnActivate(void)
{
	// ...
}

/**
 * @brief OnDeactivate
 * @param bAllowBackgroundUpdates
 * @param bAllowBackgroundInputs
 */
void OnDeactivate(bool & bAllowBackgroundUpdates, bool & bAllowBackgroundInputs)
{
	bAllowBackgroundUpdates = false;
	bAllowBackgroundInputs = false;
}

/**
* @brief OnLogin
* @param pUser
*/
void OnLogin(ShUser * pUser)
{
	Game::instance().login(pUser);
}

/**
* @brief OnLogout
* @param pUser
*/
void OnLogout(ShUser * pUser)
{
	Game::instance().logout(pUser);
}

}

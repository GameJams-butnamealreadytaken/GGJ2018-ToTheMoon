#include "application.h"
#include "Game.h"
#include "inputs.h"

#include "Plugin/PluginFactory.h"

extern "C"
{

/**
 * @brief OnPreInitialize
 */
void OnPreInitialize(void)
{
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
	// ...
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

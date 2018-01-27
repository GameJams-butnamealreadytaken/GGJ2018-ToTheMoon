#include "GameStateGame.h"

#include "../Game.h"

#include "Plugin.h"
#include "PluginFactory.h"

/**
* @brief GameStateGame::Constructor
*/
GameStateGame::GameStateGame(void)
{
	// ...
}

/**
* @brief GameStateGame::Destructor
*/
GameStateGame::~GameStateGame(void)
{
	// ...
}

/**
* @brief GameStateGame::Initialize
*/
void GameStateGame::init(void)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::release(void)
{
	// ...
}

/**
* @brief GameStateGame::entered
*/
void GameStateGame::entered(void)
{
	load();
}

/**
* @brief GameStateGame::exiting
*/
void GameStateGame::exiting(void)
{
	unload();
}

/**
* @brief GameStateGame::obscuring
*/
void GameStateGame::obscuring(void)
{
	// ...
}

/**
* @brief GameStateGame::revealed
*/
void GameStateGame::revealed(void)
{
	unload();
	load();
}

/**
 * @brief GameStateGame::load
 */
void GameStateGame::load(void)
{
	Game & game = Game::instance();

	CShIdentifier levelIdentifier("game_level");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);
}

/**
 * @brief GameStateGame::unload
 */
void GameStateGame::unload(void)
{
	ShLevel::Release();
}

/**
* @brief GameStateGame::update
*/
void GameStateGame::update(float dt)
{
	PluginGGJ2018 * pGGJ2018Instance = GetGGJ2018Plugin();
	SH_ASSERT(shNULL != pGGJ2018Instance);
}

/**
 * @brief GameStateGame::touchBegin
 */
void GameStateGame::touchBegin(const CShVector2 & pos_, float ratio)
{
	TouchDownGGJ2018Plugin(0, pos_.m_x, pos_.m_y);
}

/**
 * @brief GameStateGame::touchEnd
 */
void GameStateGame::touchEnd(const CShVector2 & pos_, float ratio)
{
	TouchUpGGJ2018Plugin(0, pos_.m_x, pos_.m_y);
}

/**
 * @brief GameStateGame::touchMove
 */
void GameStateGame::touchMove(const CShVector2 & pos_, float ratio)
{
	TouchMoveGGJ2018Plugin(0, pos_.m_x, pos_.m_y);
}

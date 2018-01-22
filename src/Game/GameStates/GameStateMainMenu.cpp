#include "GameStateMainMenu.h"

#include "../Game.h"

/**
 * @brief Constructor
 */
GameStateMainMenu::GameStateMainMenu(void)
: m_eCurrentState(IDLE)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateMainMenu::~GameStateMainMenu(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void GameStateMainMenu::init(void)
{
	CShIdentifier levelIdentifier("main_menu");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	Game & game = Game::instance();

	setState(ANIM_INTRO_ENTERED);
}

/**
 * @brief Release
 */
void GameStateMainMenu::release(void)
{
	ShLevel::Release();
}

/**
 * @brief entered
 */
void GameStateMainMenu::entered(void)
{
	Game & game = Game::instance();
}

/**
 * @brief exiting
 */
void GameStateMainMenu::exiting(void)
{
	// ...
}

/**
 * @brief obscuring
 */
void GameStateMainMenu::obscuring(void)
{
	// ...
}

/**
 * @brief revealed
 */
void GameStateMainMenu::revealed(void)
{
	Game & game = Game::instance();
}

/**
 * @brief update
 */
void GameStateMainMenu::update(float dt)
{
	switch (m_eCurrentState)
	{
		case ANIM_INTRO_ENTERED:
		{
			setState(IDLE);
		}
		break;

		case IDLE:
		{
			Game & game = Game::instance();

			if (game.GetInputManager().IsPressEnter())
			{
				game.push(Game::GAME_LEVEL);
			}
		}
		break;

		case ANIM_OUTRO_THEME:
		{
			Game & game = Game::instance();
			//game.push(Game::TRUC);
		}
		break;

		default:
		{
			// ...
		}
		break;
	}
}

/**
 * @brief Unload level
 * @return
 */
void GameStateMainMenu::setState(GameStateMainMenu::EState eState)
{
	m_eCurrentState = eState;
	switch (m_eCurrentState)
	{
		case ANIM_INTRO_ENTERED:
		{
			// ...
		}
		break;

		case IDLE:
		{
			// ...
		}
		break;

		case ANIM_OUTRO_THEME:
		{
			// ...
		}
		break;

		default:
		{
			SH_ASSERT_ALWAYS();
		}
		break;
	}
}

/**
 * @brief GameStateMainMenu::prepareAnim
 * @param pParent
 */
void GameStateMainMenu::prepareAnim(ShObject * pParent)
{
	setState(IDLE);
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchBegin(const CShVector2 & pos_, float ratio)
{
	// ...
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchEnd(const CShVector2 & pos_, float ratio)
{
	// ...
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchMove(const CShVector2 & pos_, float ratio)
{
	// ...
}

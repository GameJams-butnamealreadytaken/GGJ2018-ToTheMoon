#include "GameState.h"

int GameState::m_currentLevel = 1;
int GameState::m_currentTheme = 1;

/**
 * @brief Constructor
 */
GameState::GameState(void)
{
	// ...
}

/**
 * @brief Destructor
 */
GameState::~GameState(void)
{
	// ...
}

/**
 * @brief State::GetCurrentLevel
 */
int GameState::GetCurrentLevel(void)
{
	return(m_currentLevel);
}

/**
 * @brief State::SetCurrentLevel
 * @param level
 */
void GameState::SetCurrentLevel(int level)
{
	m_currentLevel = level;
}

/**
 * @brief State::GetCurrentTheme
 */
int GameState::GetCurrentTheme(void)
{
	return(m_currentTheme);
}

/**
 * @brief State::SetCurrentTheme
 * @param theme
 */
void GameState::SetCurrentTheme(int theme)
{
	m_currentTheme = theme;
}

/**
 * @brief State::touchBegin
 * @param pos
 */
void GameState::touchBegin(const CShVector2 & pos, float ratio)
{
	// ...
}

/**
 * @brief State::touchEnd
 * @param pos
 */
void GameState::touchEnd(const CShVector2 & pos, float ratio)
{
	// ...
}

/**
 * @brief State::touchMove
 * @param pos
 */
void GameState::touchMove(const CShVector2 & pos, float ratio)
{
	// ...
}

#include "inputs.h"

#include "Game.h"

/**
 * @brief OnTouchDown
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchDown(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::instance();
		game.touchBegin(pos);
	}
}

/**
 * @brief OnTouchUp
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchUp(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::instance();
		game.touchEnd(pos);
	}
}

/**
 * @brief OnTouchMove
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchMove(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::instance();
		game.touchMove(pos);
	}
}

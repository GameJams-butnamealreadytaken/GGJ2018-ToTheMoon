#include "GameStateMainMenu.h"

#include "../Game.h"

/**
 * @brief Constructor
 */
GameStateMainMenu::GameStateMainMenu(void)
: m_eCurrentState(IDLE)
, m_pControlBackground(shNULL)
, m_pControlMainMenu(shNULL)
, m_pControlMainMenuContent1(shNULL)
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
	
	//
	// GUI
	{
		m_pControlBackground		= ShGUI::LoadGUIAndSSS(CShIdentifier("background"), shNULL);
		SH_ASSERT(shNULL != m_pControlBackground);
		m_pControlMainMenu			= ShGUI::LoadGUIAndSSS(CShIdentifier("main_menu_background"), m_pControlBackground);
		SH_ASSERT(shNULL != m_pControlMainMenu);

		ShGUIControl * pControlMainMenuContent = ShGUIControl::GetElementById(CShIdentifier("panel_main_menu_content"), m_pControlMainMenu);
		SH_ASSERT(shNULL != pControlMainMenuContent);
		m_pControlMainMenuContent1	= ShGUI::LoadGUIAndSSS(CShIdentifier("main_menu_content_1"), pControlMainMenuContent);
		SH_ASSERT(shNULL != m_pControlMainMenuContent1);
		
		ShGUIControlButton * pButtonExit = (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_main_menu_quit"), m_pControlMainMenu);
		SH_ASSERT(shNULL != pButtonExit);
		ShGUIControlButton::AddSlotFctPtrClick(pButtonExit, (pSlotSDKButtonClick)OnButtonExitClicked);
		ShGUIControlButton * pButtonPlay = (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_main_menu_1_play"), m_pControlMainMenuContent1);
		SH_ASSERT(shNULL != pButtonPlay);
		ShGUIControlButton::AddSlotFctPtrClick(pButtonPlay, (pSlotSDKButtonClick)OnButtonPlayClicked);
		ShGUIControlButton * pButtonSettings = (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_main_menu_1_settings"), m_pControlMainMenuContent1);
		SH_ASSERT(shNULL != pButtonSettings);
		ShGUIControlButton::AddSlotFctPtrClick(pButtonSettings, (pSlotSDKButtonClick)OnButtonSettingsClicked);
	}

	setState(ANIM_INTRO_ENTERED);
}

/**
 * @brief Release
 */
void GameStateMainMenu::release(void)
{
	ShLevel::Release();
	
	//
	// GUI
	ShGUIControl::RemoveFromParent(m_pControlMainMenuContent1);
	ShGUIControl::RemoveFromParent(m_pControlMainMenu);
	ShGUIControl::RemoveFromParent(m_pControlBackground);
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

	//
	// GUI
	ShGUIControl::Show(m_pControlBackground, false);
	ShGUIControl::Show(m_pControlMainMenu, false);
	ShGUIControl::Show(m_pControlMainMenuContent1, false);
}

/**
 * @brief revealed
 */
void GameStateMainMenu::revealed(void)
{
	Game & game = Game::instance();

	//
	// GUI
	ShGUIControl::Show(m_pControlMainMenuContent1, true);
	ShGUIControl::Show(m_pControlMainMenu, true);
	ShGUIControl::Show(m_pControlBackground, true);
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
 * @brief GameStateMainMenu::OnButtonPlayClicked	
 * @param pButton
 */
/*static*/ bool GameStateMainMenu::OnButtonPlayClicked(ShGUIControlButton * pButton)
{
	//
	// TODO FIXME : launch the game !
	SH_TRACE("Game launched");

	return(true);
}

/**
 * @brief GameStateMainMenu::OnButtonSettingsClicked
 * @param pButton
 */
/*static*/ bool GameStateMainMenu::OnButtonSettingsClicked(ShGUIControlButton * pButton)
{
	//
	// TODO FIXME : launch the settings !
	SH_TRACE("Settings opened");

	return(true);
}

/**
 * @brief GameStateMainMenu::OnButtonExitClicked
 * @param pButton
 */
/*static*/ bool GameStateMainMenu::OnButtonExitClicked(ShGUIControlButton * pButton)
{
	//
	// Quits the game
	ShApplication::RequestQuit();

	return(true);
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

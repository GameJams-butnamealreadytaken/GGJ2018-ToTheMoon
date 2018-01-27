#include "GameStateGame.h"

#include "../Game.h"

#include "Plugin.h"
#include "PluginFactory.h"

/**
* @brief GameStateGame::Constructor
*/
GameStateGame::GameStateGame(void)
: m_pQuitDialog(shNULL)
, m_pControlHUD(shNULL)
, m_pControlNotif(shNULL)
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
	//
	// GUI Dialog
	m_pQuitDialog					= ShGUIModalDialog::Create(CShIdentifier("ingame_quit_dialog"));
	ShGUIControl * pDialogRoot		= ShGUIModalDialog::GetRootControl(m_pQuitDialog);
	SH_ASSERT(shNULL != pDialogRoot);
	ShGUIControlButton * pButtonYes	= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ingame_quit_dialog_main_panel_yes"), pDialogRoot);
	ShGUIControlButton * pButtonNo	= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ingame_quit_dialog_main_panel_no"), pDialogRoot);
	
	SH_ASSERT(shNULL != pButtonYes);
	SH_ASSERT(shNULL != pButtonNo);
	ShGUIControlButton::AddSlotFctPtrClick(pButtonYes, (pSlotSDKButtonClick)OnButtonClickedYes);
	ShGUIControlButton::AddSlotFctPtrClick(pButtonNo, (pSlotSDKButtonClick)OnButtonClickedNo);

	//
	// GUI
	m_pControlHUD	= ShGUI::LoadGUIAndSSS(CShIdentifier("ingame_hud"));
	SH_ASSERT(shNULL != m_pControlHUD);
	m_pControlNotif	= ShGUIControl::GetElementById(CShIdentifier("text_ingame_hud_notifications"), m_pControlHUD);
	SH_ASSERT(shNULL != m_pControlNotif);
	ShGUIControl::Hide(m_pControlHUD, true);
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::release(void)
{
	//
	// GUI Dialog
	if (ShGUI::IsModalDialogRunning())
	{
		//
		// Pops current dialog
		ShGUI::PopModalDialog();
	}
	ShGUIModalDialog::Destroy(m_pQuitDialog);

	//
	// GUI
	ShGUIControl::RemoveFromParent(m_pControlHUD);
}

/**
* @brief GameStateGame::entered
*/
void GameStateGame::entered(void)
{
	//
	// GUI showing
	ShGUIControl::Show(m_pControlHUD, true);
	//ShGUIControl::Hide(m_pControlNotif);

	load();
}

/**
* @brief GameStateGame::exiting
*/
void GameStateGame::exiting(void)
{
	//
	// GUI hiding
	ShGUIControl::Hide(m_pControlHUD, true);

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
	//
	// Level
	unload();
	load();
}

/**
 * @brief GameStateGame::load
 */
void GameStateGame::load(void)
{
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
* @brief GameStateGame::OnButtonClickedYes
*/
/*static*/ bool GameStateGame::OnButtonClickedYes(ShGUIControlButton * pButton)
{
	//
	// Pops current level
	Game & game = Game::instance();
	game.pop();
	
	//
	// Pops current dialog
	ShGUI::PopModalDialog();

	return(true);
}

/**
* @brief GameStateGame::OnButtonClickedNo
*/
/*static*/ bool GameStateGame::OnButtonClickedNo(ShGUIControlButton * pButton)
{
	//
	// Pops current dialog
	ShGUI::PopModalDialog();
	
	return(true);
}

/**
* @brief GameStateGame::update
*/
void GameStateGame::update(float dt)
{
	PluginGGJ2018 * pGGJ2018Instance = GetGGJ2018Plugin();
	SH_ASSERT(shNULL != pGGJ2018Instance);
	
	Game & game = Game::instance();
	if (game.GetInputManager().IsPressEscape())
	{
		if (!ShGUI::IsModalDialogRunning())
		{
			//
			// Pushes current dialog
			GameStateGame * pGameState = static_cast<GameStateGame*>(game.get(Game::GAME_LEVEL));
			ShGUI::PushModalDialog(pGameState->m_pQuitDialog);
		}
		else
		{
			//
			// Pops current dialog
			ShGUI::PopModalDialog();
		}
	}
}

/**
 * @brief GameStateGame::touchBegin
 */
void GameStateGame::touchBegin(const CShVector2 & pos_, float ratio)
{
	if (!ShGUI::IsModalDialogRunning())
	{
		TouchDownGGJ2018Plugin(0, pos_.m_x, pos_.m_y);
	}
}

/**
 * @brief GameStateGame::touchEnd
 */
void GameStateGame::touchEnd(const CShVector2 & pos_, float ratio)
{
	if (!ShGUI::IsModalDialogRunning())
	{
		TouchUpGGJ2018Plugin(0, pos_.m_x, pos_.m_y);
	}
}

/**
 * @brief GameStateGame::touchMove
 */
void GameStateGame::touchMove(const CShVector2 & pos_, float ratio)
{
	if (!ShGUI::IsModalDialogRunning())
	{
		TouchMoveGGJ2018Plugin(0, pos_.m_x, pos_.m_y);
	}
}

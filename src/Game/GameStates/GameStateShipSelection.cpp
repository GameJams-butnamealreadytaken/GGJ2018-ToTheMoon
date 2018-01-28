#include "GameStateShipSelection.h"

#include "../Game.h"

/**
 * @brief Constructor
 */
GameStateShipSelection::GameStateShipSelection(void)
: m_eCurrentState(IDLE)
, m_pPanelBackground(shNULL)
, m_pImageListShips(shNULL)
, m_pImageStats(shNULL)
, m_pButtonStatsExit(shNULL)
, m_pButtonPrevious(shNULL)
, m_pButtonNext(shNULL)
, m_pButtonBack(shNULL)
, m_pButtonValidate(shNULL)
, m_pButtonStats(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateShipSelection::~GameStateShipSelection(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void GameStateShipSelection::init(void)
{
	CShIdentifier levelIdentifier("main_menu");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	Game & game = Game::instance();
	
	//
	// GUI
	{
		m_pPanelBackground	= ShGUI::LoadGUIAndSSS(CShIdentifier("menu_ship_selection"), shNULL);
		SH_ASSERT(shNULL != m_pPanelBackground);

		m_pImageListShips	= (ShGUIControlImageList*)ShGUIControl::GetElementById(CShIdentifier("imagelist_ship_selection_selectable_ships"), m_pPanelBackground);
		m_pImageStats		= ShGUIControl::GetElementById(CShIdentifier("image_ship_selection_stats"), m_pPanelBackground);
		m_pButtonStatsExit	= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ship_selection_stats_exit"), m_pPanelBackground);
		m_pButtonPrevious	= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ship_selection_select_previous_ship"), m_pPanelBackground);
		m_pButtonNext		= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ship_selection_select_next_ship"), m_pPanelBackground);
		m_pButtonBack		= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ship_selection_go_back_main_menu"), m_pPanelBackground);
		m_pButtonValidate	= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ship_selection_validate"), m_pPanelBackground);
		m_pButtonStats		= (ShGUIControlButton*)ShGUIControl::GetElementById(CShIdentifier("button_ship_selection_stats"), m_pPanelBackground);
		SH_ASSERT(shNULL != m_pImageListShips);
		SH_ASSERT(shNULL != m_pImageStats);
		SH_ASSERT(shNULL != m_pButtonStatsExit);
		SH_ASSERT(shNULL != m_pButtonPrevious);
		SH_ASSERT(shNULL != m_pButtonNext);
		SH_ASSERT(shNULL != m_pButtonBack);
		SH_ASSERT(shNULL != m_pButtonValidate);
		SH_ASSERT(shNULL != m_pButtonStats);
		
		//
		// Slots
		ShGUIControlButton::AddSlotFctPtrClick(m_pButtonStatsExit,	(pSlotSDKButtonClick)OnButtonClickedStatsExit);
		ShGUIControlButton::AddSlotFctPtrClick(m_pButtonPrevious,	(pSlotSDKButtonClick)OnButtonClickedPrevious);
		ShGUIControlButton::AddSlotFctPtrClick(m_pButtonNext,		(pSlotSDKButtonClick)OnButtonClickedNext);
		ShGUIControlButton::AddSlotFctPtrClick(m_pButtonBack,		(pSlotSDKButtonClick)OnButtonClickedBack);
		ShGUIControlButton::AddSlotFctPtrClick(m_pButtonValidate,	(pSlotSDKButtonClick)OnButtonClickedValidate);
		ShGUIControlButton::AddSlotFctPtrClick(m_pButtonStats,		(pSlotSDKButtonClick)OnButtonClickedStats);

		//
		// ImageList
		float fWidth	= ShGUIControl::GetWidth(m_pImageListShips);
		float fHeight	= ShGUIControl::GetHeight(m_pImageListShips);
		for (int iShipTypeIndex = 0; iShipTypeIndex < GameStateShipSelection::e_ship_type_max; ++iShipTypeIndex)
		{
			ShSprite * pSprite = ShSprite::Find(CShIdentifier("ggj_ui"), CShIdentifier(CShString("ship_preview_") + CShString::FromInt(iShipTypeIndex)));
			float fOriginalWidth	= ShSprite::GetWidth(pSprite);
			float fOriginalHeight	= ShSprite::GetHeight(pSprite);
			float fRatio			= fOriginalWidth / fOriginalHeight;
			float fNewHeight		= fWidth / fRatio;
			ShGUIControl * pImageShip = ShGUIControlImage::Create(CShIdentifier(CShString("image_ship_selection_ship_") + CShString::FromInt(iShipTypeIndex)), 0.0f, 0.0f, fWidth, fNewHeight, pSprite, m_pImageListShips);
		}

		ShGUIControl::Hide(m_pPanelBackground, true);	
	}

	setState(ANIM_INTRO_ENTERED);
}

/**
 * @brief Release
 */
void GameStateShipSelection::release(void)
{
	ShLevel::Release();
	
	//
	// GUI
	ShGUIControl::RemoveFromParent(m_pPanelBackground);
}

/**
 * @brief entered
 */
void GameStateShipSelection::entered(void)
{
	Game & game = Game::instance();
	GameStateShipSelection * pGameState = static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));
	
	ShGUIControl::Show(pGameState->m_pPanelBackground, true);
	ShGUIControl::Hide(pGameState->m_pImageStats);
	ShGUIControl::Hide(pGameState->m_pButtonStatsExit);
	ShGUIControl::Hide(pGameState->m_pButtonPrevious);
	if (ShGUIControl::GetChildrenCount(pGameState->m_pImageListShips) > 0)
	{
		ShGUIControlImageList::SetCurrentImageIndex(pGameState->m_pImageListShips, 0);
	}
}

/**
 * @brief exiting
 */
void GameStateShipSelection::exiting(void)
{
	Game & game = Game::instance();
	GameStateShipSelection * pGameState = static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));
	
	ShGUIControl::Hide(pGameState->m_pPanelBackground, true);
}

/**
 * @brief obscuring
 */
void GameStateShipSelection::obscuring(void)
{
	// ...
}

/**
 * @brief revealed
 */
void GameStateShipSelection::revealed(void)
{
	// ...
}

/**
 * @brief update
 */
void GameStateShipSelection::update(float dt)
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
void GameStateShipSelection::setState(GameStateShipSelection::EState eState)
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
 * @brief GameStateShipSelection::OnButtonClickedStatsExit
 * @param pButton
 */
/*static*/ bool GameStateShipSelection::OnButtonClickedStatsExit(ShGUIControlButton * pButton)
{
	Game & game = Game::instance();
	GameStateShipSelection * pGameState = static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));
	SH_ASSERT(shNULL != pGameState);
	
	ShGUIControl::Hide(pGameState->m_pImageStats);
	ShGUIControl::Hide(pGameState->m_pButtonStatsExit);

	return(true);
}

/**
 * @brief GameStateShipSelection::OnButtonClickedNext	
 * @param pButton
 */
/*static*/ bool GameStateShipSelection::OnButtonClickedNext(ShGUIControlButton * pButton)
{
	Game & game					= Game::instance();
	GameStateShipSelection * pGameState		= static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));
	SH_ASSERT(shNULL != pGameState);
	ShGUIControlImageList * pImageList		= pGameState->m_pImageListShips;
	ShGUIControlButton * pButtonNext		= pGameState->m_pButtonNext;
	ShGUIControlButton * pButtonPrevious	= pGameState->m_pButtonPrevious;

	int iIndex = shMin(ShGUIControlImageList::GetCurrentImageIndex(pImageList) + 1, ShGUIControl::GetChildrenCount(pImageList) - 1);
	ShGUIControlImageList::SetCurrentImageIndex(pImageList, iIndex);

	if (iIndex == ShGUIControl::GetChildrenCount(pImageList) - 1)	{	ShGUIControl::Hide(pButtonNext);		}
	else															{	ShGUIControl::Show(pButtonPrevious);	}

	return(true);
}

/**
 * @brief GameStateShipSelection::OnButtonClickedPrevious	
 * @param pButton
 */
/*static*/ bool GameStateShipSelection::OnButtonClickedPrevious(ShGUIControlButton * pButton)
{
	Game & game						= Game::instance();
	GameStateShipSelection * pGameState		= static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));
	SH_ASSERT(shNULL != pGameState);
	ShGUIControlImageList * pImageList		= pGameState->m_pImageListShips;
	ShGUIControlButton * pButtonPrevious	= pGameState->m_pButtonPrevious;
	ShGUIControlButton * pButtonNext		= pGameState->m_pButtonNext;

	int iIndex = shMax(ShGUIControlImageList::GetCurrentImageIndex(pImageList) - 1, 0);
	ShGUIControlImageList::SetCurrentImageIndex(pImageList, iIndex);

	if (iIndex == 0)	{	ShGUIControl::Hide(pButtonPrevious);	}
	else				{	ShGUIControl::Show(pButtonNext);		}

	return(true);
}

/**
 * @brief GameStateShipSelection::OnButtonClickedBack	
 * @param pButton
 */
/*static*/ bool GameStateShipSelection::OnButtonClickedBack(ShGUIControlButton * pButton)
{
	Game & game = Game::instance();
	GameStateShipSelection * pGameState		= static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));
	SH_ASSERT(shNULL != pGameState);

	ShGUIControl::Hide(pGameState->m_pPanelBackground, true);

	game.pop();

	return(true);
}

/**
 * @brief GameStateShipSelection::OnButtonClickedValidate	
 * @param pButton
 */
/*static*/ bool GameStateShipSelection::OnButtonClickedValidate(ShGUIControlButton * pButton)
{
	Game & game = Game::instance();
	GameStateShipSelection * pGameState		= static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));
	SH_ASSERT(shNULL != pGameState);

	ShGUIControl::Hide(pGameState->m_pPanelBackground, true);

	game.push(Game::GAME_LEVEL);

	return(true);
}

/**
 * @brief GameStateShipSelection::OnButtonClickedStats	
 * @param pButton
 */
/*static*/ bool GameStateShipSelection::OnButtonClickedStats(ShGUIControlButton * pButton)
{
	Game & game = Game::instance();
	GameStateShipSelection * pGameState = static_cast<GameStateShipSelection*>(game.get(Game::SHIP_SELECTION));

	//
	// Show stats
	ShGUIControl::Show(pGameState->m_pImageStats);

	return(true);
}


/**
 * @brief GameStateShipSelection::prepareAnim
 * @param pParent
 */
void GameStateShipSelection::prepareAnim(ShObject * pParent)
{
	setState(IDLE);
}

/**
 * @brief GameStateShipSelection::Release
 */
void GameStateShipSelection::touchBegin(const CShVector2 & pos_, float ratio)
{
	// ...
}

/**
 * @brief GameStateShipSelection::Release
 */
void GameStateShipSelection::touchEnd(const CShVector2 & pos_, float ratio)
{
	// ...
}

/**
 * @brief GameStateShipSelection::Release
 */
void GameStateShipSelection::touchMove(const CShVector2 & pos_, float ratio)
{
	// ...
}

#pragma once

#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateShipSelection.h"
#include "GameStates/GameStateGame.h"

#include "InputManager.h"
#include "PersistentData.h"

#define ORIGINAL_VIEWPORT_X 3840.0f
#define ORIGINAL_VIEWPORT_Y 2160.0f

class Game
{

public:

	enum EState
	{
		MAIN_MENU,
		SHIP_SELECTION,
		GAME_LEVEL,

		MAX_GAME_STATES
	};

	static Game & instance (void)
	{
		if (shNULL == instance_)
		{
			instance_ = new Game();
		}

		return(*instance_);
	}

	void		initialize			(void);
	void		release				(void);

	void		update				(float dt);

	//
	// Events
	void		touchBegin			(const CShVector2 & pos);
	void		touchEnd			(const CShVector2 & pos);
	void		touchMove			(const CShVector2 & pos);

	void		login				(ShUser * pUser);
	void		logout				(ShUser * pUser);

	//
	// States
	void		push				(EState state);
	void		pop					(void);
	GameState *	get					(EState state);

	//
	//
	PersistentData &	GetPersistentData	(void);
	Inputs &			GetInputManager		(void);

private:

	Game					(void);

	static Game *			instance_;

	GameState *				m_aStates [MAX_GAME_STATES];
	int						m_iCurrentState;
	
	GameStateMainMenu		m_stateMainMenu;
	GameStateShipSelection	m_stateShipSelection;
	GameStateGame			m_stateGame;

	float					m_fRatio;
	ShCamera *				m_pCamera;
	ShUser *				m_pCurrentUser;

	Inputs					m_Inputs;
	PersistentData			m_PersistentData;
};

#include "Game.inl"

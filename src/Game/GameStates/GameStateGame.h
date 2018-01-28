#pragma once

#include "GameStateShipSelection.h"

class GameStateGame : public GameState
{

public:

	explicit			GameStateGame			(void);
	virtual				~GameStateGame			(void);

	void				init					(void) SH_ATTRIBUTE_OVERRIDE;
	void				release					(void) SH_ATTRIBUTE_OVERRIDE;

	void				entered					(void) SH_ATTRIBUTE_OVERRIDE;
	void				exiting					(void) SH_ATTRIBUTE_OVERRIDE;

	void				obscuring				(void) SH_ATTRIBUTE_OVERRIDE;
	void				revealed				(void) SH_ATTRIBUTE_OVERRIDE;

	void				update					(float dt) SH_ATTRIBUTE_OVERRIDE;

	void				touchBegin				(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;
	void				touchEnd				(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;
	void				touchMove				(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;

	//
	// Setters
	void				SetShipType				(GameStateShipSelection::EShipType eShipType);

protected:

	void				load					(void);
	void				unload					(void);

	//
	// GUI Slots
	static bool			OnButtonClickedTeamBlue	(ShGUIControlButton * pButton);
	static bool			OnButtonClickedTeamRed	(ShGUIControlButton * pButton);

	static bool			OnButtonClickedYes		(ShGUIControlButton * pButton);
	static bool			OnButtonClickedNo		(ShGUIControlButton * pButton);
	
private:

	enum EState
	{
		INIT,
		CONNECTING,
		PLAYING,
	};

	//
	// State
	EState				m_eState;
	float				m_ConnectTimer;

	//
	// GUI
	ShGUIModalDialog *	m_pConnectDialog;
	ShGUIModalDialog *	m_pTeamChoiceDialog;
	ShGUIModalDialog *	m_pQuitDialog;
	ShGUIControl *		m_pControlHUD;
	ShGUIControl *		m_pControlNotif;

	//
	// Properties
	GameStateShipSelection::EShipType m_eShipType;

};

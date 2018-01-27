#pragma once

#include "GameState.h"

class GameStateGame : public GameState
{

public:

	explicit			GameStateGame		(void);
	virtual				~GameStateGame		(void);

	void				init				(void) SH_ATTRIBUTE_OVERRIDE;
	void				release				(void) SH_ATTRIBUTE_OVERRIDE;

	void				entered				(void) SH_ATTRIBUTE_OVERRIDE;
	void				exiting				(void) SH_ATTRIBUTE_OVERRIDE;

	void				obscuring			(void) SH_ATTRIBUTE_OVERRIDE;
	void				revealed			(void) SH_ATTRIBUTE_OVERRIDE;

	void				update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	void				touchBegin			(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;
	void				touchEnd			(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;
	void				touchMove			(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;

protected:

	void				load				(void);
	void				unload				(void);

	//
	// GUI Slots
	static bool			OnButtonClickedYes	(ShGUIControlButton * pButton);
	static bool			OnButtonClickedNo	(ShGUIControlButton * pButton);
	
private:

	//
	// GUI
	ShGUIModalDialog *	m_pQuitDialog;
	ShGUIControl *		m_pControlHUD;
	ShGUIControl *		m_pControlNotif;
};

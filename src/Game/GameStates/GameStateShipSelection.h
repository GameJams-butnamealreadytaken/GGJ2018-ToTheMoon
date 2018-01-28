#pragma once

#include "GameState.h"

class GameStateShipSelection : public GameState
{
public:

	//
	// BEWARE ! This enum must match Plugin/World/GameObject/Ship/Ship::EShipType
	enum EShipType
	{
		e_ship_type_base,
		e_ship_type_tank,
		e_ship_type_trorapide,
		e_ship_type_pere_nowel,

		e_ship_type_max
	};

	enum EState
	{
		ANIM_INTRO_ENTERED,
		IDLE,
		ANIM_OUTRO_THEME,
	};

	explicit					GameStateShipSelection	(void);
	virtual						~GameStateShipSelection	(void);

	void						init					(void) SH_ATTRIBUTE_OVERRIDE;
	void						release					(void) SH_ATTRIBUTE_OVERRIDE;

	void						entered					(void) SH_ATTRIBUTE_OVERRIDE;
	void						exiting					(void) SH_ATTRIBUTE_OVERRIDE;

	void						obscuring				(void) SH_ATTRIBUTE_OVERRIDE;
	void						revealed				(void) SH_ATTRIBUTE_OVERRIDE;

	void						update					(float dt) SH_ATTRIBUTE_OVERRIDE;

	void						touchBegin				(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;
	void						touchEnd				(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;
	void						touchMove				(const CShVector2 & pos, float ratio) SH_ATTRIBUTE_OVERRIDE;

	void						prepareAnim				(ShObject * pParent);

protected:

	void						setState				(EState eState);
	
	static bool					OnButtonClickedStatsExit(ShGUIControlButton * pButton);
	static bool					OnButtonClickedNext		(ShGUIControlButton * pButton);
	static bool					OnButtonClickedPrevious	(ShGUIControlButton * pButton);
	static bool					OnButtonClickedBack		(ShGUIControlButton * pButton);
	static bool					OnButtonClickedValidate	(ShGUIControlButton * pButton);
	static bool					OnButtonClickedStats	(ShGUIControlButton * pButton);

private:

	EState						m_eCurrentState;
	
	ShGUIControl *				m_pPanelBackground;

	ShGUIControlImageList *		m_pImageListShips;

	ShGUIControl *				m_pPanelStats;
	ShGUIControlButton *		m_pButtonStatsExit;

	ShGUIControlButton *		m_pButtonPrevious;
	ShGUIControlButton *		m_pButtonNext;

	ShGUIControlButton *		m_pButtonBack;
	ShGUIControlButton *		m_pButtonValidate;
	ShGUIControlButton *		m_pButtonStats;
};

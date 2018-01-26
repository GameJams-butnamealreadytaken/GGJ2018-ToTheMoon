#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "World\World.h"

class PluginGGJ2018 : public CShPlugin
{
public:

	//
	// Constructor / Destructor
							PluginGGJ2018	(void);
	virtual					~PluginGGJ2018	(void);

	//
	// Play/Stop
	virtual	void			OnPlayStart			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPlayStop			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;

	//
	// Update
	virtual	void			OnPreUpdate			(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPostUpdate		(float dt) SH_ATTRIBUTE_OVERRIDE;

	//
	// Touch Events
	void					OnTouchDown			(int iTouch, float positionX, float positionY);
	void					OnTouchUp			(int iTouch, float positionX, float positionY);
	void					OnTouchMove			(int iTouch, float positionX, float positionY);

private:

	CShIdentifier m_levelIdentifier;

	World		  m_world;
};

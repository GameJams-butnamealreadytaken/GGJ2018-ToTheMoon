#pragma once

#include "ShSDK/ShSDK.h"

class PersistentData
{

public:

	//
	// Constructor / Destructor
				PersistentData			(void);
				~PersistentData			(void);

	//
	// Reset
	void		Reset					(void);

	//
	// Dirty flag
	bool		IsDirty					(void);
	void		ResetDirtyFlag			(void);

	void *		GetData					(unsigned int & size);

	void		SetMute					(bool mute);
	bool		ToggleMute				(void);
	bool		IsMuted					(void) const;

private:

	struct Data
	{
		Data(void)
		{
			mute = false;
		}

		bool			mute;
	};

	bool m_bDirty;

	Data m_data;
};

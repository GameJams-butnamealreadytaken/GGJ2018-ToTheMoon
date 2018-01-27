#pragma once

#include "ShSDK/ShSDK.h"

class SoundManager
{
public:

	enum ESoundMusic
	{
		e_sound_music_game,
		e_sound_music_max
	};

	enum ESoundFX
	{
		e_sound_fx_none,
		e_sound_fx_max

	};

	//
	// Construction / Destruction
	explicit					SoundManager			(void);
	virtual						~SoundManager			(void);

	void						Initialize				(void);
	void						Release					(void);

	void						PlaySFX					(ESoundFX eSound);
	void						PlayMusic				(ESoundMusic eSound);

protected:

private:
	
public:

protected:

private:
	ShSoundResource *					m_aSoundFXResource		[e_sound_fx_max];
	ShSoundResource *					m_aSoundMusicResource	[e_sound_music_max];
};
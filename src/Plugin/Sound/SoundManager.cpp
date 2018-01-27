#include "SoundManager.h"

SoundManager g_soundManager;

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
SoundManager::SoundManager(void)
{
	for (int eSound = 0; eSound < e_sound_fx_max; ++eSound)
	{
		m_aSoundFXResource[eSound] = shNULL;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ SoundManager::~SoundManager(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void SoundManager::Initialize(void)
{
	m_aSoundMusicResource[e_sound_music_game]							= ShSoundResource::Find(CShIdentifier("music_game"));

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void SoundManager::Release(void)
{
	for (int eSound = 0; eSound < e_sound_fx_max; ++eSound)
	{
		m_aSoundFXResource[eSound] = shNULL;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void SoundManager::PlaySFX(ESoundFX eSound)
{
	ShSoundResource * pSoundResource = m_aSoundFXResource[eSound];

	if (shNULL != pSoundResource)
	{
		ShSound::Handle soundInstanceHandle;
		ShSound::PlaySFX(pSoundResource, soundInstanceHandle, false);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void SoundManager::PlayMusic(ESoundMusic eSound)
{
	ShSoundResource * pSoundResource = m_aSoundMusicResource[eSound];
	if (shNULL != pSoundResource)
	{
		ShSound::Handle soundInstanceHandle;
		ShSound::PlayMusic(pSoundResource, soundInstanceHandle);
	}
}
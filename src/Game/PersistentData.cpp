#include "PersistentData.h"

/**
 * @brief Constructor
 */
PersistentData::PersistentData(void) : m_bDirty(false)
{
	// ...
}

/**
 * @brief Destructor
 */
PersistentData::~PersistentData(void)
{
	// ...
}

/**
 * @brief Reset
 */
void PersistentData::Reset(void)
{
	m_data = Data();

	m_bDirty = true;
}

/**
 * @brief PersistentData::IsDirty
 * @return
 */
bool PersistentData::IsDirty(void)
{
	return(m_bDirty);
}

/**
 * @brief PersistentData::ResetDirtyFlag
 */
void PersistentData::ResetDirtyFlag(void)
{
	 m_bDirty = false;
}

/**
 * @brief PersistentData::GetData
 * @return
 */
void * PersistentData::GetData(unsigned int & size)
{
	size = sizeof(Data);
	return(&m_data);
}

/**
 * @brief SetMute
 * @param mute
 */
void PersistentData::SetMute(bool mute)
{
	m_data.mute = mute;

	m_bDirty = true;
}

/**
 * @brief PersistentData::ToggleMute
 * @return
 */
bool PersistentData::ToggleMute(void)
{
	m_data.mute = !m_data.mute;

	if (m_data.mute)
	{
		ShSound::SetGlobalVolume(0.0f);
	}
	else
	{
		ShSound::SetGlobalVolume(1.0f);
	}

	m_bDirty = true;

	return(m_data.mute);
}

/**
 * @brief IsMuted
 */
bool PersistentData::IsMuted(void) const
{
	return(m_data.mute);
}

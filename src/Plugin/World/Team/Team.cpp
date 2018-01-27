#include "Team.h"

#include "../GameObjects/Transmitter/Transmitter.h"

/**
* @brief Constructor
*/
/*explicit*/ Team::Team(int teamId)
	:m_iTeamId(teamId)
{

}

/**
* @brief Destructor
*/
/*virtual*/ Team::~Team(void)
{
	// ...
}

/**
* @brief Team::Initialize
*/
void Team::Initialize(void)
{

}

/**
* @brief Team::Release
*/
void Team::Release(void)
{
	m_apTransmitter.Empty();
}

/**
* @brief Team::Update
*/
void Team::Update(float dt)
{

}

void Team::AddTransmitter(Transmitter * pTransmitter)
{
	SH_ASSERT(shNULL != pTransmitter);
	m_apTransmitter.Add(pTransmitter);
}

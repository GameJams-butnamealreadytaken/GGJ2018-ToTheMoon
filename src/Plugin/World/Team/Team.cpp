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

/**
* @brief Team::AddTransmitter
*/
void Team::AddTransmitter(Transmitter * pTransmitter)
{
	SH_ASSERT(shNULL != pTransmitter);

	// Check if has neighbour
	int nTransCount = m_apTransmitter.GetCount();
	for (int i = 0; i < nTransCount; ++i)
	{

	}

	m_apTransmitter.Add(pTransmitter);

	if (GetVictoryCondition())
	{
		// warn the world
	}
}

/**
* @brief Team::GetVictoryCondition
*/
bool Team::GetVictoryCondition(void)
{
	return(false);
}

/**
* @brief Team::ComputeVecteurNorme
*/
float Team::ComputeVecteurNorme(float Ax, float Ay, float Bx, float By)
{
	return sqrt(((Bx - Ax)*(Bx - Ax)) + ((By - Ay)*(By - Ay)));
}


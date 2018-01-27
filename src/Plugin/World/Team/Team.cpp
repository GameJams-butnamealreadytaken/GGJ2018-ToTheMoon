#include "Team.h"

#include "../GameObjects/Transmitter/Transmitter.h"

/**
* @brief Constructor
*/
/*explicit*/ Team::Team(int teamId)
	:m_iTeamId(teamId)
	, m_apTransmitter()
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
void Team::Initialize(const CShVector2 & startPoint, const CShVector2 & endPoint)
{
	m_startPoint = startPoint;
	m_endPoint = endPoint;
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
	{
		CShVector2 & newPos = pTransmitter->GetPosition2();
		int nTransCount = m_apTransmitter.GetCount();
		for (int i = 0; i < nTransCount; ++i)
		{
			CShVector2 & transPos = m_apTransmitter[i]->GetPosition2();
			if (10.0f < ComputeVecteurNorme(newPos.m_x, newPos.m_y, transPos.m_x, transPos.m_y))
			{
				pTransmitter->AddNeighbour(m_apTransmitter[i]);
			}
		}
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
	CShArray<int> transList_done;

	int nTransCount = m_apTransmitter.GetCount();
	for (int i = 0; i < nTransCount; ++i)
	{
		Transmitter * pTrans = m_apTransmitter[i];
		CShVector2 & newPos = pTrans->GetPosition2();
		// Linked to start point
		if (20 < ComputeVecteurNorme(newPos.m_x, newPos.m_y, m_startPoint.m_x, m_startPoint.m_y))
		{
			if (CheckNeighboorList(pTrans, transList_done))
			{
				return(true);
			}
		}
	}

	return(false);
}

/**
* @brief Team::CheckNeighboorList
*/
bool Team::CheckNeighboorList(Transmitter * pTrans, CShArray<int> & transList_done)
{
	if (!transList_done.Find(pTrans->GetId()))
	{
		transList_done.Add(pTrans->GetId());
		CShVector2 & newPos = pTrans->GetPosition2();
		if (20 < ComputeVecteurNorme(newPos.m_x, newPos.m_y, m_endPoint.m_x, m_endPoint.m_y))
		{
			return(true);
		}

		int nNeighbourCount = pTrans->GetNeighbourCount();
		for (int j = 0; j < nNeighbourCount; ++j)
		{
			if (CheckNeighboorList(pTrans, transList_done))
			{
				return(true);
			}
		}
	}

	return(false);
}

/**
* @brief Team::ComputeVecteurNorme
*/
float Team::ComputeVecteurNorme(float Ax, float Ay, float Bx, float By)
{
	return sqrt(((Bx - Ax)*(Bx - Ax)) + ((By - Ay)*(By - Ay)));
}


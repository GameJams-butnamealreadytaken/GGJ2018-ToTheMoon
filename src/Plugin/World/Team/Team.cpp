#include "Team.h"

#include "../GameObjects/Transmitter/Transmitter.h"

/**
* @brief Constructor
*/
/*explicit*/ Team::Team(int teamId)
	: m_iTeamId(teamId)
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
void Team::Initialize(const CShIdentifier & levelIdentifier, const CShVector2 & startPoint, const CShVector2 & endPoint)
{
	m_levelIdentifier = levelIdentifier;
	m_startPoint = startPoint;
	m_endPoint = endPoint;
}

/**
* @brief Team::Release
*/
void Team::Release(void)
{
	int nTransCount = m_apTransmitter.GetCount();
	for (int i = 0; i < nTransCount; ++i)
	{
		m_apTransmitter[i]->Release();
	}
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
			if (1500.0f > ComputeVecteurNorme(newPos.m_x, newPos.m_y, transPos.m_x, transPos.m_y))
			{
				AddNeighbour(pTransmitter, m_apTransmitter[i]);
			}
		}
	}

	m_apTransmitter.Add(pTransmitter);

	if (GetVictoryCondition())
	{
		// warn the world
		SH_TRACE("ntm");
	}
}

/**
* @brief Team::RemoveTransmitter
*/
void Team::RemoveTransmitter(Transmitter * pTransmitter)
{
	m_apTransmitter.RemoveAll(pTransmitter);
	pTransmitter->Release();
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
		if (700.0f > ComputeVecteurNorme(newPos.m_x, newPos.m_y, m_startPoint.m_x, m_startPoint.m_y))
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
	if (-1 == transList_done.Find(pTrans->GetId()))
	{
		transList_done.Add(pTrans->GetId());
		CShVector2 & newPos = pTrans->GetPosition2();
		// Linked to end point
		if (700.0f > ComputeVecteurNorme(newPos.m_x, newPos.m_y, m_endPoint.m_x, m_endPoint.m_y))
		{
			return(true);
		}

		int nNeighbourCount = pTrans->GetNeighbourCount();
		for (int j = 0; j < nNeighbourCount; ++j)
		{
			if (CheckNeighboorList(pTrans->GetNeighbour(j), transList_done))
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

/**
* @brief Team::AddNeighbour
*/
void Team::AddNeighbour(Transmitter * pTransmitterFrom, Transmitter * pTransmitterTo)
{
	ShPrimitiveSegment * pSegment = ShPrimitiveSegment::Create(m_levelIdentifier, CShIdentifier("Transpalette"), CShVector3(pTransmitterFrom->GetPosition2(), 5.0f), CShVector3(pTransmitterTo->GetPosition2(), 5.0f), CShRGBAf());
	
	if (m_iTeamId == 0)
	{
		ShPrimitiveSegment::SetColor(pSegment, CShRGBAf(0.0f, 0.0f, 1.0f, 1.0f));
	}
	else if (m_iTeamId == 1)
	{
		ShPrimitiveSegment::SetColor(pSegment, CShRGBAf(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		SH_ASSERT_ALWAYS();
	}

	ShPrimitiveSegment::Set2d(pSegment, true);

	pTransmitterFrom->AddNeighbour(pTransmitterTo, pSegment);
	pTransmitterTo->AddNeighbour(pTransmitterFrom, pSegment);
}

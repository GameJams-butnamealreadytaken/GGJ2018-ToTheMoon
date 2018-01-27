#pragma once

#include "ShSDK/ShSDK.h"

class Transmitter;

class Team
{
public:


	explicit		Team				(int teamId);
	virtual			~Team				(void);

	virtual void	Initialize			(const CShVector2 & startPoint, const CShVector2 & endPoint);
	virtual void	Release				(void);

	virtual void	Update				(float dt);

	void			AddTransmitter		(Transmitter * pTransmitter);
	void			RemoveTransmitter	(Transmitter * pTransmitter);

private:
	bool			GetVictoryCondition	(void);
	float			ComputeVecteurNorme	(float Ax, float Ay, float Bx, float By);
	void			AddNeighbour		(Transmitter * pTransmitter1, Transmitter * pTransmitter2);
	bool			CheckNeighboorList	(Transmitter * pTrans, CShArray<int> & transList_done);
private:

	int								m_iTeamId;

	CShVector2						m_startPoint;
	CShVector2						m_endPoint;

	CShArray<Transmitter *>			m_apTransmitter;
};

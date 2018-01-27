#pragma once

#include "ShSDK/ShSDK.h"

class Transmitter;

class Team
{
public:

	explicit		Team				(int teamId);
	virtual			~Team				(void);

	virtual void	Initialize			(void);
	virtual void	Release				(void);

	virtual void	Update				(float dt);

	void			AddTransmitter		(Transmitter * pTransmitter);

private:
	bool			GetVictoryCondition	(void);
	float			ComputeVecteurNorme	(float Ax, float Ay, float Bx, float By);

private:

	int							m_iTeamId;
	CShArray<Transmitter *>		m_apTransmitter;

};

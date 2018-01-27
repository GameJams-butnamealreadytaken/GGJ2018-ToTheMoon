#pragma once

struct ShUser;

class Inputs
{
public:
	explicit	 Inputs(void);
	virtual		~Inputs(void);

	void		Initialize		(ShUser * pUser);
	void		Release			(void);

	void		Update			(void);

	bool		IsRestarting	(void);
	bool		IsPressEnter	(void);
	bool		IsPressEscape	(void);

private:

	ShUser *	m_pUser;

	bool		m_isRestarting;
	bool		m_isPressEnter;
	bool		m_isPressEscape;
};


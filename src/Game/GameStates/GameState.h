#pragma once

#include "ShSDK/ShSDK.h"

inline float BounceEase(float t)
{
	if (t < (1.0f / 2.75f))
	{
		return (7.5625f * t * t);
	}
	else if (t < (2.0f / 2.75f))
	{
		t -= 1.5f / 2.75f;
		return (7.5625f * t * t + 0.75f);
	}
	else if (t < (2.5f / 2.75f))
	{
		t -= 2.25f / 2.75f;
		return (7.5625f * t * t + 0.9375f);
	}
	else
	{
		t -= 2.625f / 2.75f;
		return (7.5625f * t * t + 0.984375f);
	}

	SH_ASSERT_ALWAYS();
	return(0.0f);
}

inline float ComputeVectorNorm(const CShVector2 & A, const CShVector2 & B) 
{
	return(shSqrtf(shPow(B.m_x - A.m_x, 2) + shPow(B.m_y - A.m_y, 2)));
}

class GameState
{

protected:

	GameState(void);
	virtual ~GameState(void);

	static int	GetCurrentLevel	(void);
	static void SetCurrentLevel	(int level);

	static int	GetCurrentTheme	(void);
	static void SetCurrentTheme	(int theme);

public:

	virtual void init		(void) = 0;
	virtual void release	(void) = 0;

	virtual void entered	(void) = 0;
	virtual void exiting	(void) = 0;

	virtual void obscuring	(void) = 0;
	virtual void revealed	(void) = 0;

	virtual void update		(float dt) = 0;

	virtual void touchBegin	(const CShVector2 & pos, float ratio);
	virtual void touchEnd	(const CShVector2 & pos, float ratio);
	virtual void touchMove	(const CShVector2 & pos, float ratio);

protected:

	static int m_currentLevel;
	static int m_currentTheme;
};

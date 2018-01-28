#include "Game.h"

#include "ShSDK/ShSDK.h"

Game * Game::instance_ = shNULL;

/**
 * @brief Game::Game
 */
Game::Game(void) : m_iCurrentState(-1), m_fRatio(1.0f), m_pCamera(shNULL), m_pCurrentUser(shNULL)
{
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		m_aStates[i] = shNULL;
	}
}

/**
 * @brief Initialize
 */
void Game::initialize(void)
{
	//
	// Create Camera
	m_pCamera = ShCamera::Create(GID(global), CShIdentifier("camera"), false);
	SH_ASSERT(shNULL != m_pCamera);

	int display_width = ShDisplay::GetWidth();
	int display_height = ShDisplay::GetHeight();

	float ratio_x = ORIGINAL_VIEWPORT_X / display_width;
	float ratio_y = ORIGINAL_VIEWPORT_Y / display_height;

	m_fRatio = shMax(ratio_x, ratio_y, 2.0f);

	ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 200.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetUp(m_pCamera, CShVector3(0.0f, 1.0f, 0.0f));
	ShCamera::SetProjectionOrtho(m_pCamera);
	ShCamera::SetFarPlaneDistance(m_pCamera, 250.0f);
	ShCamera::SetNearPlaneDistance(m_pCamera, 1.0f);
	ShCamera::SetViewport(m_pCamera, ORIGINAL_VIEWPORT_X, ORIGINAL_VIEWPORT_Y);

	ShCamera::SetCurrent2D(m_pCamera);

	//
	// Initialize states
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		get(EState(i))->init();
	}

	//
	// push Main Menu
	push(MAIN_MENU);
}

/**
 * @brief Release
 */
void Game::release(void)
{
	//
	// pop Main Menu
	pop();

	//
	// Release states
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		get(EState(i))->release();
	}

	//
	// Release background level
	ShLevel::Release();

	//
	// Destroy camera
	ShCamera::Destroy(m_pCamera);
	m_pCamera = shNULL;

	// ...
	m_pCurrentUser = shNULL;
}

/**
 * @brief Game::update
 */
void Game::update(float dt)
{
	if (m_PersistentData.IsDirty())
	{
		unsigned int size = 0;
		void * pData = m_PersistentData.GetData(size);

		bool bSaved = ShUser::Save(m_pCurrentUser, "GGJ2018", pData, size);

		if (bSaved)
		{
			m_PersistentData.ResetDirtyFlag(); // reset only if save succeeded
		}
	}

	m_Inputs.Update();

	m_aStates[m_iCurrentState]->update(dt);
}

/**
 * @brief Game::touchBegin
 */
void Game::touchBegin(const CShVector2 & pos)
{
	m_aStates[m_iCurrentState]->touchBegin(pos, m_fRatio);
}

/**
 * @brief Game::touchEnd
 */
void Game::touchEnd(const CShVector2 & pos)
{
	m_aStates[m_iCurrentState]->touchEnd(pos, m_fRatio);
}

/**
 * @brief Game::touchMove
 */
void Game::touchMove(const CShVector2 & pos)
{
	m_aStates[m_iCurrentState]->touchMove(pos, m_fRatio);
}

/**
 * @brief Game::login
 * @param pUser
 */
void Game::login(ShUser * pUser)
{
	if (shNULL == m_pCurrentUser)
	{
		m_pCurrentUser = pUser;

		m_Inputs.Initialize(pUser);

		//
		// Load Persistent Data
		unsigned int size = 0;
		void * pData = m_PersistentData.GetData(size);

		bool bLoaded = ShUser::Load(m_pCurrentUser, "GGJ2018", pData, size);

		if (!bLoaded)
		{
			m_PersistentData.Reset();
			SH_TRACE("Load failed !");
		}
	}
}

/**
 * @brief Game::logout
 * @param pUser
 */
void Game::logout(ShUser * pUser)
{
	if (pUser == m_pCurrentUser)
	{
		m_Inputs.Release();

		m_pCurrentUser = shNULL;
	}
}

/**
 * @brief Game::push
 * @param state
 */
void Game::push(EState state)
{
	SH_ASSERT(m_iCurrentState < MAX_GAME_STATES);

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->obscuring();
	}

	++m_iCurrentState;

	m_aStates[m_iCurrentState] = get(state);

	m_aStates[m_iCurrentState]->entered();
}

/**
 * @brief Game::pop
 */
void Game::pop(void)
{
	SH_ASSERT(m_iCurrentState >= 0);

	m_aStates[m_iCurrentState]->exiting();

#if SH_DEBUG
	m_aStates[m_iCurrentState] = nullptr;
#endif

	--m_iCurrentState;

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->revealed();
	}
}

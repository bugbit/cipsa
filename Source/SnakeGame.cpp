#include "SnakeGame.h"
#include "InputManager.h"

#define MOVE_TIME 0.1f
#define BODY_SIZE 10.f

CSnakeGame::CSnakeGame()
: m_bIsEnd(false) 
, m_fGrowTime(5.f)
{
	SPlayer p1;
	p1.m_snake = new CSnake(400,400);
	p1.m_PlayerInput = new CKeyboardPlayerInput();
	m_Players.push_back(p1);

	/*
	SPlayer p2;
	p2.m_snake = new CSnake(200,400);
	p2.m_PlayerInput.SetSnake(p2.m_snake);
	p2.m_PlayerInput.SetMoveUp("teclaW");
	p2.m_PlayerInput.SetMoveDown("teclaS");
	p2.m_PlayerInput.SetMoveRight("teclaD");
	p2.m_PlayerInput.SetMoveLeft("teclaA");
	m_Players.push_back(p2);

	SPlayer p3;
	p3.m_snake = new CSnake(500,400);
	p3.m_PlayerInput.SetSnake(p3.m_snake);
	m_Players.push_back(p3);

	
	SPlayer p3;
	p3.m_snake = new CSnake(500,400);
	CKeyboardInput ip = new CKeyboardInput();

	ip.SetMoveUp();
	ó
	ip->SetMoveUp();

	p3.m_PlayerInput = ip;
	m_Players.push_back(p3);
	*/

}

CSnakeGame::~CSnakeGame()
{	

}

void CSnakeGame::Render		(CDebugPrintText2D& printText2d)
{
	if (m_bIsEnd)
	{
		int dy = 400;
		dy += printText2d.PrintText(400,dy,0xffffffff,"GAME OVER");	
	}
	else
	{
		for(int cont = 0; cont < m_Players.size(); cont ++)
		{
			m_Players[cont].m_snake->Render(printText2d);
		}
	}
}

void CSnakeGame::Update		(float dt)
{

	for(int cont = 0; cont < m_Players.size(); cont ++)
	{
		m_Players[cont].m_snake->Update(dt);
		m_Players[cont].m_PlayerInput->UpdateInputAction(dt);
	}
	

	for(int cont = 0; cont < m_Players.size(); cont ++)
	{
		SBody headSnake = m_Players[cont].m_snake->GetBodyHead();

		if (	headSnake.m_fPosX > 800 || headSnake.m_fPosX < 0 ||
				headSnake.m_fPosY > 600 || headSnake.m_fPosY < 0 )
		{
			m_bIsEnd = true;
		}
	}

	//Update Logic Game:
	m_fGrowTime -= dt;
	if (m_fGrowTime <= 0)
	{
		m_fGrowTime = 5.f;
		for(int cont = 0; cont < m_Players.size(); cont ++)
		{
			m_Players[cont].m_snake->Grow();
		}
	}
}


void CSnakeGame::UpdateInputActions( float dt )
{
	
}
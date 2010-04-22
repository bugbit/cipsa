#include "SnakeGame.h"
#include "InputManager.h"

#define MOVE_TIME 0.1f
#define BODY_SIZE 10.f

CSnakeGame::CSnakeGame()
: m_bIsEnd(false) 
, m_fGrowTime(5.f)
, m_Snake1(400,400)
, m_Snake2(200,400)
{
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
		m_Snake1.Render(printText2d);
		m_Snake2.Render(printText2d);
	}
}

void CSnakeGame::Update		(float dt)
{

	UpdateInputActions( dt );
	m_Snake1.Update(dt);
	m_Snake2.Update(dt);

	SBody headSnake = m_Snake1.GetHeadPosition();

	if (	headSnake.m_fPosX > 800 || headSnake.m_fPosX < 0 ||
				headSnake.m_fPosY > 600 || headSnake.m_fPosY < 0 )
	{
		m_bIsEnd = true;
	}

	//Update Logic Game:
	m_fGrowTime -= dt;
	if (m_fGrowTime <= 0)
	{
		m_fGrowTime = 5.f;
		m_Snake1.Grow();
		m_Snake2.Grow();
	}
}


void CSnakeGame::UpdateInputActions( float dt )
{
	CInputManager * input = CInputManager::GetInstance();

	//Update Snake 1:
	if( input->DoAction("tecla_Down") )
	{
		m_Snake1.SetDirection( DIR_DOWN );
	}
	else if( input->DoAction("tecla_Up") )
	{
		m_Snake1.SetDirection( DIR_UP );
	}
	else if( input->DoAction("tecla_Right") )
	{
		m_Snake1.SetDirection( DIR_RIGHT );
	}
	else if( input->DoAction("tecla_Left") )
	{
		m_Snake1.SetDirection( DIR_LEFT );
	}


	//Update Snake 2:
	if( input->DoAction("teclaS") )
	{
		m_Snake2.SetDirection( DIR_DOWN );
	}
	else if( input->DoAction("teclaW") )
	{
		m_Snake2.SetDirection( DIR_UP );
	}
	else if( input->DoAction("teclaD") )
	{
		m_Snake2.SetDirection( DIR_RIGHT );
	}
	else if( input->DoAction("teclaA") )
	{
		m_Snake2.SetDirection( DIR_LEFT );
	}
}
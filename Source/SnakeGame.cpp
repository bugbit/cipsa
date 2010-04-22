#include "SnakeGame.h"
#include "InputManager.h"

#define MOVE_TIME 0.1f
#define BODY_SIZE 10.f

CSnakeGame::CSnakeGame()
: m_bIsEnd(false) 
, m_fMoveTime(MOVE_TIME)
, m_bMove(false)
, m_fSpeed(100.f)
, m_Direction(DIR_RIGHT)
, m_fGrowTime(5.f)
, m_bGrow(false)
{
	SBody body;
	body.m_fPosX = 400;
	body.m_fPosY = 400;
	m_Snake.push_back(body);
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
		for(int cont = 0; cont < m_Snake.size(); cont++)
		{
			printText2d.PrintText(m_Snake[cont].m_fPosX,m_Snake[cont].m_fPosY,0xffffffff,"X");	
		}
	}
}

void CSnakeGame::Update		(float dt)
{

	UpdateInputActions( dt );


	if (	m_Snake[0].m_fPosX > 800 || m_Snake[0].m_fPosX < 0 ||
				m_Snake[0].m_fPosY > 600 || m_Snake[0].m_fPosY < 0 )
	{
		m_bIsEnd = true;
	}

	//Update Logic Game:
	m_fGrowTime -= dt;
	if (m_fGrowTime <= 0)
	{
		m_fGrowTime = 5.f;
		m_bGrow = true;
	}


	m_fMoveTime -= dt;
	if (m_fMoveTime <= 0 )
	{
		m_bMove = true;
		m_fMoveTime = MOVE_TIME;
	}

	if (m_bMove)
	{
		m_bMove = false;

		if (m_bGrow)
		{
			m_bGrow = false;
			m_Snake.push_back(m_Snake[0]);
		}

		for( int cont = m_Snake.size()-1; cont > 0; cont--)
		{
			m_Snake[cont] = m_Snake[cont-1];
		}
		switch (m_Direction)
		{
		case DIR_RIGHT:
			m_Snake[0].m_fPosX += BODY_SIZE;
			break;

		case DIR_LEFT:
			m_Snake[0].m_fPosX -= BODY_SIZE;
			break;

		case DIR_UP:
			m_Snake[0].m_fPosY -= BODY_SIZE;
			break;

		case DIR_DOWN:
			m_Snake[0].m_fPosY += BODY_SIZE;
			break;

		default:
			break;
			//ERROR!!!
		}

		
	}
	


}


void CSnakeGame::UpdateInputActions( float dt )
{
	CInputManager * input = CInputManager::GetInstance();

	if( input->DoAction("tecla_Down") )
	{
		m_Direction = DIR_DOWN;
	}
	else if( input->DoAction("tecla_Up") )
	{
		m_Direction = DIR_UP;
	}
	else if( input->DoAction("tecla_Right") )
	{
		m_Direction = DIR_RIGHT;
	}
	else if( input->DoAction("tecla_Left") )
	{
		m_Direction = DIR_LEFT;
	}
}
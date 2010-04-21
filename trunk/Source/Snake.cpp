#include "Snake.h"
#include "InputManager.h"


CSnake::CSnake()
: m_bIsEnd(false) 
{
	SBody body;
	body.m_fPosX = 400;
	body.m_fPosY = 400;
	m_Snake.push_back(body);
	m_Direction = DIR_RIGHT;
	m_fSpeed = 100.f;
}

CSnake::~CSnake()
{	

}

void CSnake::Render		(CDebugPrintText2D& printText2d)
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

void CSnake::Update		(float dt)
{

	UpdateInputActions( dt );


	if (	m_Snake[0].m_fPosX > 800 || m_Snake[0].m_fPosX < 0 ||
				m_Snake[0].m_fPosY > 600 || m_Snake[0].m_fPosY < 0 )
	{
		m_bIsEnd = true;
	}

	//Update Logic Game:
	switch (m_Direction)
	{
	case DIR_RIGHT:
		m_Snake[0].m_fPosX += dt*m_fSpeed;
		break;

	case DIR_LEFT:
		m_Snake[0].m_fPosX -= dt*m_fSpeed;
		break;

	case DIR_UP:
		m_Snake[0].m_fPosY -= dt*m_fSpeed;
		break;

	case DIR_DOWN:
		m_Snake[0].m_fPosY += dt*m_fSpeed;
		break;

	default:
		break;
		//ERROR!!!
	}


}


void CSnake::UpdateInputActions( float dt )
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
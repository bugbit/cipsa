#include "Snake.h"
#include "InputManager.h"


CSnake::CSnake()
{
	SBody body;
	body.m_fPosX = 0.f;
	body.m_fPosY = 0.f;
	m_Snake.push_back(body);
	m_fSpeed = 100.f;
}

CSnake::CSnake(float x, float y)
{
	SBody body;
	body.m_fPosX = x;
	body.m_fPosY = y;
	m_Snake.push_back(body);
	m_fSpeed = 100.f;
}

CSnake::~CSnake()
{	

}

void CSnake::Render		(CDebugPrintText2D& printText2d)
{
}

void CSnake::Update		(float dt)
{
	//Snake's size
	int size = (int) m_Snake.size();

	//Update Logic Game:
	switch (m_Direction)
	{
	case DIR_RIGHT:
		m_Snake[0].m_fPosX += dt*m_fSpeed;
		for(int cont = (size - 1); cont > 0; cont--)
		{
			m_Snake[cont] = m_Snake[cont - 1];
		}
		break;

	case DIR_LEFT:
		m_Snake[0].m_fPosX -= dt*m_fSpeed;
		for(int cont = (size - 1); cont > 0; cont--)
		{
			m_Snake[cont] = m_Snake[cont - 1];
		}
		break;

	case DIR_UP:
		m_Snake[0].m_fPosY -= dt*m_fSpeed;
		for(int cont = (size - 1); cont > 0; cont--)
		{
			m_Snake[cont] = m_Snake[cont - 1];
		}
		break;

	case DIR_DOWN:
		m_Snake[0].m_fPosY += dt*m_fSpeed;
		for(int cont = (size - 1); cont > 0; cont--)
		{
			m_Snake[cont] = m_Snake[cont - 1];
		}
		break;

	default:
		break;
		//ERROR!!!
	}
}

void CSnake::Grow ( )
{
	//Creo un nuevo cuerpo y lo añado al vector
	SBody eat;

	/*eat.m_fPosX = m_Snake[m_Snake.size()-1].m_fPosX;
	eat.m_fPosY = m_Snake[m_Snake.size()-1].m_fPosY;*/

	//Tendría que guardar la última posición del último cuerpo y añadirlo después, pero se añadiria en la misma posición
	//o visualmente sólo un poco más abajo (1 pxl???)

	m_Snake.push_back(eat);
}

SBody CSnake::GetHeadPosition ( )
{
	SBody head;

	head.m_fPosX = m_Snake[0].m_fPosX;
	head.m_fPosY = m_Snake[0].m_fPosY;

	return head;
}

void CSnake::SetDirection (Direction d)
{
	CInputManager * input = CInputManager::GetInstance();

	if( d == DIR_DOWN )
	{
		input->DoAction("tecla_Down");
	}
	else if( d == DIR_UP )
	{
		input->DoAction("tecla_Up");
	}
	else if( d == DIR_RIGHT )
	{
		input->DoAction("tecla_Right");
	}
	else if( d == DIR_LEFT )
	{
		input->DoAction("tecla_Left");
	}
}
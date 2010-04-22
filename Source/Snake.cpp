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
	//Inicializo el timer para "comer"
	m_fTimer = 0.f;
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

	UpdateInputActions( dt );	//Según la tecla que me aprietes, iré en una dirección o en otra
	Eat ( dt );


	if (	m_Snake[0].m_fPosX > 800 || m_Snake[0].m_fPosX < 0 ||
				m_Snake[0].m_fPosY > 600 || m_Snake[0].m_fPosY < 0 )	//Si la cabeza pasa de los límites de la pantalla
	{
		m_bIsEnd = true;	//Se acaba el juego
	}

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

void CSnake::Eat ( float dt )
{
	m_fTimer += dt;

	if(m_fTimer > 5)
	{
		//Creo un nuevo cuerpo y lo añado al vector
		SBody eat;
		eat.m_fPosX = m_Snake[m_Snake.size() - 1].m_fPosX-(dt*m_fSpeed);
		eat.m_fPosY = m_Snake[m_Snake.size() - 1].m_fPosY-(dt*m_fSpeed);

		//Tendría que guardar la última posición del último cuerpo y añadirlo después
		m_Snake.push_back(eat);
		m_fTimer = 0;	//Lo reinicio parra que vuelva a contar desde el principio
	}
}
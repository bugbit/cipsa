#include "Snake.h"
#include "InputManager.h"
#include "time.h"

#define BODY_SIZE 10.f

CInputManager * enter = CInputManager::GetInstance();

CSnake::CSnake()
{
	srand(unsigned(time(0)));
	m_State				= LOOPSTATE_STARTGAME;
	m_Direction			= DIRECTION_RIGHT;
	m_fPoint			= 0;
	m_bMove				= false;
	m_fTimeMove			= 0;
	m_bGrow				= false;
	m_fSpeedDifficulty	= 0;

	m_fGeneratedX		=0;
	m_fGeneratedY		=0;


	SBodySnake Snake;
	Snake.m_fCoordX	= 400;
	Snake.m_fCoordY	= 320;
	m_Snake.push_back(Snake);

	Generate();	
}

CSnake::~CSnake()
{	

}

EDirection CSnake::GetDirection()							
{
	return m_Direction;
}

void CSnake::SetDirection(EDirection NewDirection)			
{
	m_Direction = NewDirection;
}

ELoopStates CSnake::GetState()
{
	return m_State;
}

void CSnake::SetState(ELoopStates NewState)
{
	m_State = NewState;
}


void CSnake::Print( CDebugPrintText2D& printText2d)				//Imprime pantalla
{
	printText2d.PrintText(0, 0, 0xFFFF0000, "PUNTUACION: %.f", m_fPoint);

	printText2d.PrintText(30,50, 0xFFFF0000, "____________");
	printText2d.PrintText(130,50, 0xFFFF0000,"____________");
	printText2d.PrintText(230,50, 0xFFFF0000,"____________");
	printText2d.PrintText(330,50, 0xFFFF0000,"____________");
	printText2d.PrintText(430,50, 0xFFFF0000,"____________");
	printText2d.PrintText(530,50, 0xFFFF0000,"____________");
	printText2d.PrintText(630,50, 0xFFFF0000,"____________");


	for(int cont =0; cont < m_Snake.size(); cont++)
	{
		if(cont==0)
		{
			printText2d.PrintText(m_Snake[cont].m_fCoordX, m_Snake[cont].m_fCoordY, 0xFF00FF00, "Ö");
		}
		else
		{
		printText2d.PrintText(m_Snake[cont].m_fCoordX, m_Snake[cont].m_fCoordY, 0xFF00FF00, "O");
		}
	}
		
	printText2d.PrintText(m_fGeneratedX, m_fGeneratedY, 0xFFFF0000, "*");
}

void CSnake::Generate()									//Genera X e Y en de la ficha ( * ) a "comer"
{
	m_fGeneratedX = (float)(rand() % 790);
	m_fGeneratedY = (float)(rand() % 630);
	if(m_fGeneratedY<65)
		m_fGeneratedY=65;
	if(m_fGeneratedX<10)
		m_fGeneratedX=10;

//	if (m_fGeneratedX >790 || m_fGeneratedY> 630)
//	{
//		int jorls = 0;
//	}


}

void CSnake::Render		(CDebugPrintText2D& printText2d)
{
	switch (GetState()) {
		case LOOPSTATE_STARTGAME:							//Inicia el juego

			m_fPoint = 0;

				printText2d.PrintText(200, 150, 0xFFFFFFFF,"¡SNAKE!");
				printText2d.PrintText(200, 200, 0xFFFFFFFF,"Introduzca el nivel de dificultad");
				printText2d.PrintText(250, 250, 0xFFFFFFFF,"	a-Facil");
				printText2d.PrintText(250, 300, 0xFFFFFFFF,"	b-Normal");
				printText2d.PrintText(250, 350, 0xFFFFFFFF,"	c-Dificl");
			
			break;


		case LOOPSTATE_LIVE:								//Mientras esta "viva" la "serpiente" se ejecuta este estado
			
			if( m_Snake[0].m_fCoordX<1 || m_Snake[0].m_fCoordX>787 ||		//Si "choca" contra las paredes...
				m_Snake[0].m_fCoordY<50 || m_Snake[0].m_fCoordY>594)
			{

				SetState(LOOPSTATE_END);					//...la "serpiente muere"
			}

			for(int cont =2; cont < m_Snake.size(); cont++)
			{
				if(m_Snake.size()>2)
				{
					if(m_Snake[0].m_fCoordX == m_Snake[cont].m_fCoordX &&
						m_Snake[0].m_fCoordY == m_Snake[cont].m_fCoordY)
					{
						SetState(LOOPSTATE_END);
					}
				}
			}

			if((m_Snake[0].m_fCoordX >= m_fGeneratedX-5 && m_Snake[0].m_fCoordX <= m_fGeneratedX+5) && //Si "come" un *...
			(m_Snake[0].m_fCoordY >= m_fGeneratedY-5 && m_Snake[0].m_fCoordY <= m_fGeneratedY+5))
			{					
				m_bGrow = true;

				m_fPoint++;									//Ganas un punto...
				Generate();							//...y se genera otra posicion de *
				if((int)m_fPoint%5==0)
				{
					m_fSpeedDifficulty-=0.01;
				}

			}

			Print(printText2d);

			break;


		case LOOPSTATE_END:

			printText2d.PrintText(200, 150, 0xFFFF0000, "SNAKE? SNAKE?! SNAAAAKE!");
			printText2d.PrintText(200, 200, 0xFFFF0000, "PUNTUACION: %.f", m_fPoint);
			printText2d.PrintText(200, 250, 0xFFFF0000, "Presione la tecla F para continuar");
			
			break;
	}
	
	
}

void CSnake::Update		(float dt)
{
	switch (GetState()) {
		case LOOPSTATE_STARTGAME:

			if(m_fSpeedDifficulty==0){					//Define la velocidad del juego
				if (enter->DoAction("teclaA")) {
					m_fSpeedDifficulty = 0.3;
				}
				if (enter->DoAction("teclaB")) {
					m_fSpeedDifficulty = 0.2;
				}
				if (enter->DoAction("teclaC")){
					m_fSpeedDifficulty = 0.1;
				}
			}
			else
			{
				m_bMove = m_fSpeedDifficulty;
				SetState(LOOPSTATE_LIVE);
			}
			break;


		case LOOPSTATE_LIVE:

			
			if (enter->DoAction("move_right")) {		//Al presinoar (en este caso) 'D' la serpiente se mueve a la derecha
				if(GetDirection() != DIRECTION_LEFT)
				{
					SetDirection(DIRECTION_RIGHT);
				}
			}
			if (enter->DoAction("move_left")) {
				if(GetDirection() != DIRECTION_RIGHT)
				{
					SetDirection(DIRECTION_LEFT);
				}
			}
			if (enter->DoAction("move_up")) {
				if(GetDirection() != DIRECTION_DOWN)
				{
					SetDirection(DIRECTION_UP);
				}
			}
			if (enter->DoAction("move_down")) {
				if(GetDirection() != DIRECTION_UP)
				{
					SetDirection(DIRECTION_DOWN);
				}
			}

			m_fTimeMove -= dt;
			if(m_fTimeMove <= 0)
			{
				m_bMove = true;
				m_fTimeMove = m_fSpeedDifficulty;

			}

			if(m_bMove)
			{

				m_bMove = false;

				if(m_bGrow)
				{
					m_bGrow = false;
					if(m_Snake.size()==1)
					{
						m_Snake.push_back(m_Snake[0]);
					}
					else
					{
						m_Snake.push_back(m_Snake[1]);
					}

				}

				for(int cont=m_Snake.size()-1;cont>0;cont--)
				{
					m_Snake[cont] = m_Snake[cont-1];
				}

				switch (GetDirection()) {
				case DIRECTION_RIGHT:						//Va sumando pixeles a la derecha(en este caso)
					m_Snake[0].m_fCoordX += BODY_SIZE;			
					break;

				case DIRECTION_LEFT:
					m_Snake[0].m_fCoordX -= BODY_SIZE;
					break;

				case DIRECTION_UP:
					m_Snake[0].m_fCoordY -= BODY_SIZE;
					break;

				case DIRECTION_DOWN:
					m_Snake[0].m_fCoordY += BODY_SIZE;
					break;
				}

			}
			break;

		case LOOPSTATE_END:

			if (enter->DoAction("teclaF")) {			//Espera a que presionen 'F' para volver al inicio
				SetState(LOOPSTATE_STARTGAME);
			}
			
			break;

	}

	
}
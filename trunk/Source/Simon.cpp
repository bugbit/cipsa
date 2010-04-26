#include "Simon.h"
#include "time.h"
#include "InputManager.h"

CInputManager *input = CInputManager::GetInstance();

CSimon::CSimon()
{
	srand(unsigned(time(0)));
	m_fTime = -2;
	m_hasBeep = false;
	m_Points = 0;
	m_DifficultyTime = 0;

}

CSimon::~CSimon()
{	

}

void CSimon::Render		(CDebugPrintText2D& printText2d)
{
	switch (m_board.GetEstado()) {
		case LOOPSTATE_START:
			
			m_hasBeep = true;
			m_Points = 0;

			if(m_DifficultyTime==0){
			printText2d.PrintText(200, 150, 0xFFFFFFFF,"¡SIMON!");
			printText2d.PrintText(200, 200, 0xFFFFFFFF,"Introduzca el nivel de dificultad");
			printText2d.PrintText(250, 250, 0xFFFFFFFF,"	a-Facil");
			printText2d.PrintText(250, 300, 0xFFFFFFFF,"	b-Normal");
			printText2d.PrintText(250, 350, 0xFFFFFFFF,"	c-Dificl");
			}
			break;

		case LOOPSTATE_SHOW:
			printText2d.PrintText(0, 0, 0xFFFFFFFF, "REPITE LA SIGUIENTE SECUENCIA:");
			Print(printText2d, m_board.Show());
			break;

		case LOOPSTATE_CHECK:
			if (m_tecla != SYMBOL_LAST) {
				if (m_fTime < -0.5) m_fTime = -0.5;				//recorta el tiempo de espera
				Print(printText2d, m_tecla);					//muestra la pulsacion
				if (m_fTime > 0) {								//espera a que termine el tiempo
					if (m_board.Check(m_tecla)) {				//verifica la pulsacion
						if (!m_board.Increase()) {				//si ha terminado la secuencia
							m_Points++;							//suma un punti
							m_board.SetEstado(LOOPSTATE_START); //repite el bucle creando un nuevo item
						}
						m_fTime = m_DifficultyTime;
						m_tecla = SYMBOL_LAST;
					} else {
						m_fTime = m_DifficultyTime;
						m_board.SetEstado(LOOPSTATE_ENDGAME);
					}
					m_hasBeep = false;
				}
			} else if (m_fTime > 0) {
				m_fTime = -2;
				m_hasBeep = false;
				m_board.SetEstado(LOOPSTATE_ENDGAME);
			} else {
				printText2d.PrintText(0, 0, 0xFFFFFFFF, "TIEMPO RESTANTE: %.2lf", -m_fTime);
			}
			break;

		case LOOPSTATE_ENDGAME:		
			printText2d.PrintText(400, 300, 0xFF0000C0, "ERROR");
			printText2d.PrintText(375, 350, 0xFFFF0000, "PUNTUACION: %.f", m_Points);
			if (!m_hasBeep && m_fTime > m_DifficultyTime) {
				Beep(1500, 100);
				Beep(500, 500);
				m_hasBeep = true;
			}
			break;
	}
}
void CSimon::Update		(float dt)
{
	m_fTime += dt;
	if (m_fTime > 60) m_fTime = 0;

	switch (m_board.GetEstado()) {
		case LOOPSTATE_START:

			if(m_DifficultyTime==0){
				if (input->DoAction("teclaA")) {
					m_DifficultyTime=-4;
				}
				if (input->DoAction("teclaB")) {
					m_DifficultyTime=-2;
				}
				if (input->DoAction("teclaC")){
					m_DifficultyTime=-1.5;
				}
			}

			if(m_DifficultyTime!=0) {
				m_board.Generate();
				m_board.SetEstado(LOOPSTATE_SHOW);
				m_hasBeep = false;
				m_fTime = m_DifficultyTime;
			}
			break;

		case LOOPSTATE_SHOW:
			if (m_fTime > 0) {
				m_hasBeep = false;
				m_fTime = m_DifficultyTime;
				if (!m_board.Increase()) {
					m_tecla = SYMBOL_LAST;
					m_board.SetEstado(LOOPSTATE_CHECK);
				}
			}
			break;

		case LOOPSTATE_CHECK:
			if (m_tecla == SYMBOL_LAST) {
				if (input->DoAction("teclaW")) {
					m_tecla = SYMBOL_A;
				} else if (input->DoAction("teclaD")) {
					m_tecla = SYMBOL_B;
				} else if (input->DoAction("teclaS")) {
					m_tecla = SYMBOL_C;
				} else if (input->DoAction("teclaA")) {
					m_tecla = SYMBOL_D;
				}
			}
			_flushall();
			break;

		case LOOPSTATE_ENDGAME:
			if (m_fTime > 0) {
				m_board.Reiniciar();
				m_board.SetEstado(LOOPSTATE_START);
				m_hasBeep = false;
				m_fTime = -10;
			}
			break;
	}

}

void CSimon::Print(CDebugPrintText2D& pt2d, ESymbols e) {
	int iFreq = 0;

	switch (e) {
		case SYMBOL_A:
			pt2d.PrintText(400, 160, 0xFF0000FF, "W");
			iFreq = 1500;
			break;

		case SYMBOL_B:
			pt2d.PrintText(600, 320, 0xFFFF0000, "D");
			iFreq = 1000;
			break;

		case SYMBOL_C:
			pt2d.PrintText(400, 480, 0xFF00FFFF, "S");
			iFreq = 2000;
			break;

		case SYMBOL_D:
			pt2d.PrintText(200, 320, 0xFF00FF00, "A");
			iFreq = 500;
			break;
	}
	if (!m_hasBeep && iFreq > 0) {
		Beep(iFreq, 200);
		m_hasBeep = true;
	}
}
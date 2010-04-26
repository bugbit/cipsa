#ifndef _SNAKE_H
#define _SNAKE_H

#include "DebugPrintText2D.h"
#include "BaseGame.h"
#include <vector>

typedef enum ELoopStates {LOOPSTATE_LIVE, LOOPSTATE_END, LOOPSTATE_STARTGAME };

typedef enum EDirection {DIRECTION_UP,DIRECTION_DOWN,DIRECTION_LEFT,DIRECTION_RIGHT};

typedef struct SBodySnake
		{
			float m_fCoordX;
			float m_fCoordY;
		};


class CSnake : public CBaseGame
{
public:
	CSnake();
	~CSnake();

	void		Generate		();

	void		SetState		(ELoopStates);
	ELoopStates	GetState		();

	void		SetDirection	(EDirection);
	EDirection	GetDirection	();


	void		Render			(CDebugPrintText2D& printText2d);
	void		Update			(float dt);

	void		Print			(CDebugPrintText2D& printText2d);

	void		Init		(){};
	void		DeInit		(){};

private:
	float				m_fPoint;
	ELoopStates			m_State;
	EDirection			m_Direction;
	

	float				m_fGeneratedX;
	float				m_fGeneratedY;

	float				m_fSpeedDifficulty;
	bool				m_bMove;
	float				m_fTimeMove;
	bool				m_bGrow;


	std::vector<SBodySnake>	m_Snake;


};

#endif //_SNAKE_H
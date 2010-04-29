#ifndef _PLAYER_INPUT_H
#define _PLAYER_INPUT_H

#include <vector>

#include "DebugPrintText2D.h"
#include "Snake.h"

class CPlayerInput
{
public:
	CPlayerInput();
	~CPlayerInput();

	virtual void	UpdateInputAction		(float dt) = 0;
	void			SetSnake				(CSnake* snake) {m_Snake = snake;}
	CSnake*			GetSnake				();

private:

	CSnake*	m_Snake;
	
};

#endif //_PLAYER_INPUT_H

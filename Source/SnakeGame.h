#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

#include "BaseGame.h"
#include "Snake.h"
#include <vector>


class CSnakeGame: public CBaseGame
{
public:
	CSnakeGame();
	~CSnakeGame();

	void		Render							(CDebugPrintText2D& printText2d);
	void		Update							(float dt);

	void		Init								(){};
	void		DeInit							(){};

private:
	void		UpdateInputActions	(float dt);
private:

	CSnake		m_Snake1;
	CSnake		m_Snake2;
	bool			m_bIsEnd;
	float			m_fGrowTime;

};

#endif //_SNAKE_GAME_H
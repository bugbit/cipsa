#ifndef _SNAKE_H
#define _SNAKE_H

#include "BaseGame.h"
#include <vector>

struct SBody
{
	float	m_fPosX;
	float	m_fPosY;
};

typedef enum Direction {DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_NOTHING};


class CSnake: public CBaseGame
{
public:
	CSnake();
	CSnake(float x, float y);
	~CSnake();

	void		Render							(CDebugPrintText2D& printText2d);
	void		Update							(float dt);

	void		Init								(){};
	void		DeInit							(){};

	void		Grow	();
	SBody		GetHeadPosition	();
	void		SetDirection	( Direction d );

private:

	std::vector<SBody>	m_Snake;
	Direction			m_Direction;
	float				m_fSpeed;

};

#endif //_SNAKE_H
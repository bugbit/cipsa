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
	~CSnake();

	void		Render							(CDebugPrintText2D& printText2d);
	void		Update							(float dt);

	void		Init								(){};
	void		DeInit							(){};

private:
	void		UpdateInputActions	(float dt);
	void		Eat	(float dt);
private:

	std::vector<SBody>	m_Snake;
	bool							m_bIsEnd;
	Direction						m_Direction;
	float							m_fSpeed;
	float							m_fTimer;
};

#endif //_SNAKE_H
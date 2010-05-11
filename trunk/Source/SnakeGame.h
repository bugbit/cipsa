#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

#include "BaseGame.h"
#include "Snake.h"
#include "PlayerInput.h"
#include "Item.h"
#include <vector>

struct SPlayer
{
	CSnake	*			m_snake;
	CPlayerInput	m_PlayerInput;
};

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

	std::vector<SPlayer>	m_Players;
	std::vector<CItem*>		m_Items;
	bool									m_bIsEnd;
	float									m_fGrowTime;

};

#endif //_SNAKE_GAME_H
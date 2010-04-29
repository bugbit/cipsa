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

	void	SetSnake					(CSnake* snake) {m_Snake = snake;}
	void	UpdateInputAction	(float dt);
	void	SetMoveUp					(std::string MoveUp)		{m_sMoveUp=MoveUp;}
	void	SetMoveDown				(std::string MoveDown)	{m_sMoveDown=MoveDown;}
	void	SetMoveRight			(std::string MoveRight) {m_sMoveRight=MoveRight;}
	void	SetMoveLeft				(std::string MoveLeft)	{m_sMoveLeft=MoveLeft;}

private:

	CSnake*	m_Snake;

	std::string m_sMoveUp;
	std::string m_sMoveDown;
	std::string m_sMoveRight;
	std::string m_sMoveLeft;
	
};

#endif //_PLAYER_INPUT_H

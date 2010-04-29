#ifndef _CKEYBOARD_PLAYER_INPUT_H
#define _CKEYBOARD_PLAYER_INPUT_H

#include <vector>

#include "DebugPrintText2D.h"
#include "Snake.h"
#include "PlayerInput.h"

class CKeyboardPlayerInput : public CPlayerInput
{
public:
	CKeyboardPlayerInput();
	~CKeyboardPlayerInput();

	void			SetSnake				() {m_Snake = GetSnake();}
	virtual void	UpdateInputAction		(float dt);
	void	SetMoveUp					(std::string MoveUp)	{m_sMoveUp=MoveUp;}
	void	SetMoveDown					(std::string MoveDown)	{m_sMoveDown=MoveDown;}
	void	SetMoveRight				(std::string MoveRight) {m_sMoveRight=MoveRight;}
	void	SetMoveLeft					(std::string MoveLeft)	{m_sMoveLeft=MoveLeft;}

private:

	CSnake*	m_Snake;

	std::string m_sMoveUp;
	std::string m_sMoveDown;
	std::string m_sMoveRight;
	std::string m_sMoveLeft;
	
};

#endif //_CKEYBOARD_PLAYER_INPUT_H

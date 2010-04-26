#ifndef _SIMON_H
#define _SIMON_H

#include "BaseGame.h"
#include "Board.h"

class CSimon: public CBaseGame
{
public:
	CSimon();
	~CSimon();

	void		Render		(CDebugPrintText2D& printText2d);
	void		Update		(float dt);

	void		Init		(){};
	void		DeInit		(){};

private:
	void		Print(CDebugPrintText2D&, ESymbols);
	CBoard		m_board;
	float		m_fTime;
	bool		m_hasBeep;
	ESymbols	m_tecla;
	float		m_Points;
	float		m_DifficultyTime;

};

#endif //_SIMON_H
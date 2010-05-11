#ifndef _INPUT_H
#define _INPUT_H
#include "DebugPrintText2D.h"

class CItem
{
public:
	CItem();
	~CItem();

	void		Render			(CDebugPrintText2D& printText2d);
	void		Update			(float dt);

	float		GetPosX			() {return m_fPosX;}
	float		GetPosY			() {return m_fPosY;}

	void		SetPosX			(float x) {m_fPosX = x;}
	void		SetPosY			(float y) {m_fPosY = y;}

	void		SetActive		(bool flag)	{m_bIsActived = flag;}
	void		SetVisible	(bool flag)	{m_bIsVisible = flag;}
	

private:

	float	m_fPosX;
	float	m_fPosY;
	bool	m_bIsActived;
	bool	m_bIsVisible;



};

#endif //_INPUT_H
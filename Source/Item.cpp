#include "Item.h"

CItem::CItem()
:m_fPosX(0.f)
,m_fPosY(0.f)
,m_bIsActived(true)
,m_bIsVisible(true)
{}

CItem::~CItem(){}

void CItem::Render		(CDebugPrintText2D& printText2d)
{
	if (m_bIsVisible)
	{
		printText2d.PrintText(m_fPosX,m_fPosY,0xffffffff,"O");
	}
}
void CItem::Update		(float dt)
{
	if (m_bIsActived)
	{
		//blablabla...
	}
}

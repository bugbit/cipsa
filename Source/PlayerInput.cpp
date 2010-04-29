#include "PlayerInput.h"
#include "InputManager.h"

CPlayerInput::CPlayerInput()
{
 m_sMoveUp = "tecla_Up";
 m_sMoveDown= "tecla_Down";
 m_sMoveRight= "tecla_Right";
 m_sMoveLeft= "tecla_Left";

}

CPlayerInput::~CPlayerInput()
{

}

void	CPlayerInput::UpdateInputAction(float dt)
{
	CInputManager * input = CInputManager::GetInstance();

	//Update Snake 1:
	if( input->DoAction(m_sMoveDown) )
	{
		m_Snake->SetDirection( DIR_DOWN );
	}
	else if( input->DoAction(m_sMoveUp) )
	{
		m_Snake->SetDirection( DIR_UP );
	}
	else if( input->DoAction(m_sMoveRight) )
	{
		m_Snake->SetDirection( DIR_RIGHT );
	}
	else if( input->DoAction(m_sMoveLeft) )
	{
		m_Snake->SetDirection( DIR_LEFT );
	}
}
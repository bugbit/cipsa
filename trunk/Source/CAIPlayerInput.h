#ifndef _CAI_PLAYER_INPUT_H
#define _CAI_PLAYER_INPUT_H

#include <vector>

#include "DebugPrintText2D.h"
#include "Snake.h"
#include "PlayerInput.h"

class CAIPlayerInput : public CPlayerInput
{
public:
	CAIPlayerInput();
	~CAIPlayerInput();

	virtual void	UpdateInputAction	(float dt);

private:

	
};

#endif //_CAI_PLAYER_INPUT_H

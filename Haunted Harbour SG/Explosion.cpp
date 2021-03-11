#include "stdafx.h"
#include "Explosion.h"


Explosion::Explosion(void):GraphicsObject(0, 0, 196, 196)
{
	fired = true;
	width = hitWidth = 196;
	height = hitHeight = 196;
	picY = 0;
	picX = 0;
	loopCells = false;
	endCell = 6;
	curCell = startCell = 0;
	damage = 100;
}


Explosion::~Explosion(void)
{
}


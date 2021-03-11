#include "stdafx.h"
#include "PurpleBullet.h"


PurpleBullet::PurpleBullet(void)
{
	hitHeight = height = 12;
	hitWidth = width = 12;
	type = BulletType::pbullet;
}


PurpleBullet::~PurpleBullet(void)
{
}

void PurpleBullet::explode(){
	picY = 12;
	picX = 0;
	width = 32;
	height = 32;
	x -= 12;
	y -= 12;
	loopCells = false;
	endCell = 2;
	curCell = 0;
	exploding = true;
}
#include "stdafx.h"
#include "GreenBullet.h"


GreenBullet::GreenBullet(void)
{
	hitHeight = height = 7;
	hitWidth = width = 7;
	type = BulletType::gbullet;
}


GreenBullet::~GreenBullet(void)
{
}

void GreenBullet::explode(){
	picY = 8;
	picX = 0;
	width = 15;
	height = 15;
	x -= 8;
	y -= 8;
	loopCells = false;
	endCell = 2;
	curCell = 0;
	exploding = true;
}
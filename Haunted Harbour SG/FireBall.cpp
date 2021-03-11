#include "stdafx.h"
#include "FireBall.h"


FireBall::FireBall(void)
{
	hitHeight = height = 26;
	hitWidth = width = 41;
	maxdistance = 1000;
    type = fball;
	damage = 30;
	picY = 26;
	picX = 0;
	loopCells = true;
	endCell = 3;
	curCell = 0;
	startCell = 0;
	xdis = 115;
}


FireBall::~FireBall(void)
{
	
}

void FireBall::explode()
{
	picY = 49;
	width = 45;
	height = 29;
	x -= 12;
	y -= 12;
	loopCells = false;
	endCell = 0;
	curCell = 0;
	exploding = true;
	xdis = 32;
	picX = width*curCell + xdis;

}
#include "stdafx.h"
#include "PlayerObject.h"


PlayerObject::PlayerObject(void):WeaponsObject("../Pics/ViktorTesla.bmp", 100, 100)
{
	xspeed= 0;
	yspeed= 0;
	stopright = true;
	stopleft =true;
	setStandRight();
	hitWidth = 54;
	hitHeight = 42;
	bullettype = BulletType::pbullet;
	maxhealth = curhealth = 100;
	startx = 100;
	starty = 100;
	isdead = false;
	shoottimer = 0;
	canjump = false;
	godmode = false;
	facing = true;
}


PlayerObject::~PlayerObject(void)
{
}

void PlayerObject::move(void)
{
	invincible -= 1;
	prevx = x;
	prevy = y;
	x += xspeed;
	y += yspeed;

	if (y > GROUND - height)
	{
		if (state == JUMPRIGHT){
			if(stopright){
				setStandRight();
			}else{setMoveRight();}
		}else if (state == JUMPLEFT){
			if(stopleft){
				setStandLeft();
			}else{setMoveLeft();}
		}
		yspeed = 0;
		canjump = true;
		y = GROUND - height;
	}
	else
		yspeed += GRAVITY;
	if (x - mapPosition < 100 && xspeed < 0 || x - mapPosition > 350 && xspeed > 0)
	{
		mapPosition += xspeed;
	}

	if (yspeed > GRAVITY){
		canjump = false;
	}
}

void PlayerObject::setMoveRight()
{
	width = 54;
	height = 42;
	picY=0;
	endCell = 9;
	loopCells = true;
	startCell = 1;
	xspeed=10;
	picX = 60;
	facing = true;
	state = MOVERIGHT;

}
void PlayerObject::setMoveLeft()
{
	width = 54;
	height=42;
	picY= 42;
	endCell = 9;
	loopCells=true;
	startCell = 1;
	xspeed = -10;
	facing = false;
	state = MOVELEFT;
}
void PlayerObject::setJumpRight()
{
	if (canjump){
		width = 48;
		height = 56;
		picY = 86;
		endCell = 5;
		loopCells=false;
		curCell= 0;
		yspeed= -30;
		state = JUMPRIGHT;
		facing = true;
	    m_sound->PlayWaveFile(Sounds::jump);
	}
}
void PlayerObject::setJumpLeft()
{
	if (canjump){
		width =48;
		height = 56;
		picY= 146;
		endCell=5;
		loopCells = false;
		state =JUMPLEFT;
		curCell = 0;
		yspeed= -30;
		facing = false;
	    m_sound->PlayWaveFile(Sounds::jump);
	}
}
void PlayerObject::setShootRight()
{
	width = 60;
	height = 38;
	picY = 199;
	endCell= 0;
	loopCells = false;
	startCell = 0;
	xspeed = 0;
	state =SHOOTRIGHT;
	curCell = 0;
	facing = true;

}
void PlayerObject::setShootLeft()
{
	width = 60;
	height = 38;
	picY = 237;
	endCell= 0;
	loopCells = false;
	startCell = 0;
	xspeed = 0;
	state =SHOOTLEFT;
	curCell = 0;
	facing = false;

}
void PlayerObject::setStandRight()
{
	curCell = 0;
	width =54;
	height = 42;
	picY=0;
	endCell = 0;
	startCell = 0;
	loopCells = false;
	xspeed = 0;
	picX = 0;
	facing = true;
	state = STANDRIGHT;
}
void PlayerObject::setStandLeft()
{
	curCell = 0;
	width =54;
	height = 42;
	picY=42;
	endCell = 0;
	startCell = 0;
	loopCells = false;
	xspeed = 0;
	picX = 0;
	facing = false;
	state = STANDLEFT;
}
bool PlayerObject::isJumping(){
	return state == JUMPRIGHT || state == JUMPLEFT;
}
void PlayerObject::checkCollisionWithBlock(HitObject* object)
{
	if(hitTest(object)){
		if (prevx + hitWidth <= object->x)
			x = object -> x - hitWidth - 1;
		else if(prevx >= object -> x + object -> hitWidth)
			x = object->x + object->hitWidth + 1;
		else if (prevy + hitHeight <= object->y){		
			if (state==JUMPLEFT && stopleft == true )
				setStandLeft();
			else if (state == JUMPRIGHT && stopright == true)
				setStandRight();
			else if(state == JUMPLEFT && stopleft == false)
				setMoveLeft();
			else if (state == JUMPRIGHT && stopright == false)
				setMoveRight();
			y = object->y - hitHeight -1;
			yspeed = 0;
			canjump = true;
		}else if (prevy >= object->y + object->hitHeight)
		{
			yspeed = 0;
			y = object->y + object->hitHeight + 1;
		}
	}
}

void PlayerObject::onHit(std::unique_ptr<Bullet>& bullet){
	m_sound->PlayWaveFile(Sounds::hitsound);
	decreaseHealth(bullet->damage);
}

void PlayerObject::decreaseHealth(int damage)
{
	if (invincible < 1){
		curhealth -= damage;
		invincible = 10;
	}
	if (curhealth < 1){
		isdead = true;
		m_sound->PlayWaveFile(Sounds::playerdeath);
	}
}

void PlayerObject::resetPlayer()
{
	x = startx;
	y = starty;
	xspeed = 0;
	yspeed = 0;
	setStandRight();
	curhealth = maxhealth;
	mapPosition = x - width * 3;
	isdead = false;
}
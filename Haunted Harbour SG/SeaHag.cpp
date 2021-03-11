#include "stdafx.h"
#include "SeaHag.h"
#include <cmath>

SeaHag::SeaHag(PlayerObject* v,int cx, int cy ):EnemyObject(201,201)
{
	type = enemyType::hag;
	height = 39;
	width = 28;
	curCell = 0;
	endCell = 4;
	startCell = 0;
	loopCells = true;
	xspeed = -5;
	yspeed= 0;
	bullettype = BulletType::gbullet;
	isdead = false;
	radius = 20;
	centerx = cx;
	centery = cy;
	angle = 0;
	victor =v;
	shootdelay = 20;
	shoottick = 0;
	maxhealth = curhealth = 10;
	hitdisx = 0;
	hitdisy = 0;
}


SeaHag::~SeaHag(void)
{
}

void SeaHag::move(){
	if (isdead == false){
		x = std::cos(angle)* radius + centerx;
		y = std::sin(angle)* radius + centery;
		angle += 0.15;

		if (shoottick++ >= shootdelay){
			shoottick = 0;
			fire();
		}	
	}
	animate();
}

void SeaHag::onHit(std::unique_ptr<Bullet>& bullet){
	curhealth -= bullet->damage;
	if (curhealth < 1){
	startCell = 0;
	width = 32;
	height = 28;
	endCell = 6;
	curCell = 0;
	picX = 0;
	picY = 156;
	loopCells = false;
	isdead = true;
	deathtimer = 20;
	m_sound->PlayWaveFile(Sounds::hagdeath);
	}
}

void SeaHag::onHit(std::unique_ptr<Explosion>& explodes){
	curhealth -= explodes->damage;
	if (curhealth < 1){
	startCell = 0;
	width = 32;
	height = 28;
	endCell = 6;
	curCell = 0;
	picX = 0;
	picY = 156;
	loopCells = false;
	isdead = true;
	deathtimer = 20;
	m_sound->PlayWaveFile(Sounds::hagdeath);
	}
}

void SeaHag::checkEnemyCollisionWithBlock(HitObject* object){
	/*if(hitTest(object)){
		if (prevx + hitWidth <= object->x){
			xspeed *= -1; 
			x = object->x - hitWidth;
			picY = 0;
		}
		else if(prevx >= object -> x + object -> hitWidth){
			xspeed *= -1; 
			x = object->x + object->hitWidth;
			picY = 35;

		}
		else if (prevy + hitHeight <= object->y){		
			yspeed =0;
			y = object->y - hitHeight;
		}else if (prevy >= object->y + object->hitHeight){
			yspeed=0;
			y = object->y + object->hitHeight;
		}
	}*/
}

void SeaHag::fire()
{
	float s = 30;
	int xdiff = victor->x - x;
	int ydiff = victor->y - y;
	float length = std::sqrt((xdiff*xdiff) + (ydiff*ydiff));
	int xs = xdiff*(s/length);
	int ys = ydiff*(s/length);
	fireBullet(x, y, xs, ys);
}
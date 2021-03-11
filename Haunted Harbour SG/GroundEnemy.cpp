#include "stdafx.h"
#include "GroundEnemy.h"
#include "soundclass.h"


GroundEnemy::GroundEnemy(int x, int y):EnemyObject(x, y)
{
	width = 28;
	height = 37;
	xspeed = -5;
	curCell = 0;
	startCell = 0;
	endCell = 10;
	loopCells = true;
	bullettype = BulletType::gbullet;
	isdead = false;
	type = enemyType::crab;
	maxhealth = curhealth = 30;
	prevx = x;
	prevy = y;
	hitdisx = 0;
	hitdisy = 0;
}


GroundEnemy::~GroundEnemy(void)
{
}

void GroundEnemy::move(){
	yspeed += GRAVITY;
	prevy = y;
	prevx = x;
	x += xspeed;
	y += yspeed;
	if (y > GROUND - height){
		y = GROUND - height;
		yspeed = 0;
	}	
	animate();
	if (!isdead){
		int rNum = rand()%30;
		if(rNum == 1){
			if(xspeed > 0){
				fireBullet(x + 10, y + 20, xspeed + 10, yspeed);
			}else{fireBullet(x - 10, y + 20, xspeed - 10, yspeed);}
		}
	}
}

void GroundEnemy::onHit(std::unique_ptr<Bullet>& bullet){
	x += bullet->xspeed;
	if ((curhealth -= bullet->damage) < 1){
		curCell	= 0;
		endCell = 0;
		if (xspeed < 0){
			picY = 70;
		}else if(xspeed > 0){
			picY = 105;
		}
		xspeed = 0;
		isdead = true;
		deathtimer = 100;
		m_sound->PlayWaveFile(Sounds::crabdeath);
	}
}

void GroundEnemy::onHit(std::unique_ptr<Explosion>& explodes){
	if ((curhealth -= explodes->damage) < 1){
		curCell	= 0;
		endCell = 0;
		if (xspeed < 0){
			picY = 70;
		}else if(xspeed > 0){
			picY = 105;
		}
		xspeed = 0;
		isdead = true;
		deathtimer = 100;
		m_sound->PlayWaveFile(Sounds::crabdeath);
	}
}

void GroundEnemy::checkEnemyCollisionWithBlock(HitObject* object){
	if(hitTest(object)){
		if (prevy + hitHeight <= object->y){		
			yspeed =0;
			y = object->y - hitHeight - 1;
		}else if (prevy >= object->y + object->hitHeight){
			yspeed=0;
			y = object->y + object->hitHeight + 1;
		}
		else if (prevx + hitWidth <= object->x){
			xspeed *= -1; 
			x = object->x - hitWidth - 1;
			picY = 0;
		}
		else if(prevx >= object -> x + object -> hitWidth){
			xspeed *= -1; 
			x = object->x + object->hitWidth + 1;
			picY = 35;
		}		
	}
}


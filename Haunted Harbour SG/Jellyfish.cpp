#include "stdafx.h"
#include "Jellyfish.h"
#include "PlayerObject.h"


Jellyfish::Jellyfish(int posx, int posy):EnemyObject(posx, posy)
{
	width = 55;
	height = 42;
	startCell = 0;
	endCell = 7;
	loopCells = true;
	curCell = 0;
	isdead = false;
	type = enemyType::jelly;
	xspeed = 10;
	maxhealth = curhealth = 20;
	yspeed = 0;
	timer = 0;
	turnLeft();
	hitWidth = width;
	hitdisx = 0;
	hitdisy = 0;
}


Jellyfish::~Jellyfish(void)
{
}

void Jellyfish::checkEnemyCollisionWithBlock(HitObject* object){
	if(hitTest(object)){
		//checkLeft
		if (prevx + hitWidth <= object->x){			
			x = object->x - hitWidth;
		    turnLeft();
		}
		//checkRight
		else if(prevx >= object -> x + object -> hitWidth){
		    turnRight();
			x = object->x + object->hitWidth + 1;
		}	
		else if (prevy + hitHeight <= object->y){		
			yspeed =0;
			y = object->y - hitHeight - 1;
		}else if (prevy >= object->y + object->hitHeight){
			yspeed=0;
			y = object->y + object->hitHeight;
		}
	}
}

void Jellyfish::move()
{
	if (isdead == false){
	prevx = x;
	x += xspeed;
	timer += 1;
	if (xspeed > 0 && timer > 70){
		turnLeft();
	}else if(xspeed < 0 && timer > 70){
		turnRight();
	}
	}
	animate();
}

void Jellyfish::turnLeft()
{
	xspeed *= -1; 
	picY = 44;
	timer = 0;
	xdis = 15;
}

void Jellyfish::turnRight()
{
	xspeed *= -1; 
	picY = 0;
	timer = 0;
	xdis = 5;
}

void Jellyfish::onHit(std::unique_ptr<Bullet>& bullet){
	x += bullet->xspeed;
	if ((curhealth -= bullet->damage) < 1){
	isdead = true;
	deathtimer = 1;
	m_sound->PlayWaveFile(Sounds::jellydeath);
	}
}

void Jellyfish::onHit(std::unique_ptr<Explosion>& explodes){
	if ((curhealth -= explodes->damage) < 1){
	isdead = true;
	deathtimer = 1;
	m_sound->PlayWaveFile(Sounds::jellydeath);
	}
}

void Jellyfish::checkEnemyCollisionWithPlayer(PlayerObject* object)
{
	if(hitTest(object)){
	object->decreaseHealth(10);
	}
}
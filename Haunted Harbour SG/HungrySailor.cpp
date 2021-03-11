#include "stdafx.h"
#include "HungrySailor.h"
#include "PlayerObject.h"


HungrySailor::HungrySailor(PlayerObject* v, int x, int y):EnemyObject(x, y)
{
	victor = v;
	width = 77;
	height = 94;
	startCell = 0;
	endCell = 8;
	loopCells = false;
	curCell = 0;
	isdead = false;
	type = enemyType::sailor;
	bullettype = BulletType::fball;
	maxhealth = curhealth = 50;
	yspeed = 0;
	hitWidth = width;
	hitHeight = height;
	xdis = 9;
	shoottimer = 0;
	hitdisx = 20;
	hitdisy = 0;
}


HungrySailor::~HungrySailor(void)
{
}

void HungrySailor::onHit(std::unique_ptr<Bullet>& bullet){
}

void HungrySailor::move(){
	if ((x - victor->x) < 300 && x > victor->x){
		if (curCell < endCell){
			curCell += 1;
		}
	}else if (curCell > 0){
			curCell -= 1;
		}
		
		if (curCell == endCell && shoottimer < 1){
		fireBullet(x + 10, y + 45, -10, 0);
		m_sound->PlayWaveFile(Sounds::fireball);
		shoottimer = 30;
		}
		shoottimer -= 1;
	picX = width*curCell + xdis;
}

void HungrySailor::checkEnemyCollisionWithBlock(HitObject* object){

}

void HungrySailor::checkEnemyCollisionWithPlayer(PlayerObject* object){
	if(hitTest(victor)){
	victor->decreaseHealth(9999);
	}
}
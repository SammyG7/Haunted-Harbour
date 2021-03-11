#include "stdafx.h"
#include "LighthouseKeeper.h"
#include "PlayerObject.h"
#include "Vec2.h"

bool LighthouseKeeper::shouldplaysound = false;

LighthouseKeeper::LighthouseKeeper(PlayerObject* v, int x, int y):EnemyObject(x, y)
{
	picY = 55; 
	victor = v;
	width = 50;
	height = 87;
	startCell = 0;
	endCell = 10;
	loopCells = true;
	curCell = 0;
	isdead = false;
	type = enemyType::keeper;
	maxhealth = curhealth = 50;
	yspeed = 0;
	hitWidth = width;
	hitHeight = height;
	xdis = 68;
	lookAt = true;
	hitable = false;
	hitdisx = 0;
	hitdisy = 0;
	
}


LighthouseKeeper::~LighthouseKeeper(void)
{

}


void LighthouseKeeper::move()
{
	if (victor->x + victor->hitWidth < x ){
		if (victor->state == STANDLEFT || victor->state == JUMPLEFT || victor->state == SHOOTLEFT || victor->state == MOVELEFT){
			if (state != State::followleft){
				state = State::followleft;
				picY = 55; 
				startCell = 0;
				endCell = 10;
				curCell = startCell;
			}
		}else {
			if (state != State::hideleft){
				state = State::hideleft;
				picY = 80; 
				startCell = 13;
				endCell = 15;
				curCell = startCell;
			}
		}
	}else if (victor->x > x + width){
		if (victor->state == STANDRIGHT || victor->state == JUMPRIGHT || victor->state == SHOOTRIGHT || victor->state == MOVERIGHT){
			if (state != State::followright){
				state = State::followright;
				picY = 145; 
				startCell = 0;
				endCell = 10;
				curCell = startCell;
			}
		}else {
			if (state != State::hideright){
				state = State::hideright;
				picY = 170; 
				startCell = 13;
				endCell = 15;
				curCell = startCell;
			}

		}
	}

	if (state == State::followleft || state == State::followright){
	Vec2 d(victor->x - x, victor->y - y);
	float distance = d.magnitude();
	auto s = 4.0f;
	auto r = s/distance;
	auto m = d*r;
	x += m.x;
	if (y < GROUND - height){
	y += m.y;
	}
    if (std::abs(victor->x - x) < 400){
	shouldplaysound = true;
	}
	}
	animate();


}

void LighthouseKeeper::onHit(std::unique_ptr<Bullet>& bullet)
{
}

void LighthouseKeeper::checkEnemyCollisionWithBlock(HitObject* object)
{
}

void LighthouseKeeper::turnLeft()
{
	picY = 55;
}

void LighthouseKeeper::turnRight()
{
	picY = 144;
}

void LighthouseKeeper::checkEnemyCollisionWithPlayer(PlayerObject* victor){
if (state == State::followleft || state == State::followright){
	if(hitTest(victor)){
	victor->decreaseHealth(50);
	}
}
}
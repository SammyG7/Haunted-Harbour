#pragma once
#include "enemyobject.h"
#include "PlayerObject.h"
class SeaHag :
	public EnemyObject
{
public:
	SeaHag(PlayerObject* v, int cx, int cy);
	int radius;
	int centerx;
	int centery;
	float angle;
	int shoottick;
	int shootdelay;
	PlayerObject* victor;
	void move();
	void onHit(std::unique_ptr<Bullet>& bullet);
	void onHit(std::unique_ptr<Explosion>& explodes);
	void checkEnemyCollisionWithBlock(HitObject* object);
	void fire();
	virtual ~SeaHag(void);
};


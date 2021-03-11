#pragma once
#include "enemyobject.h"
class HungrySailor :
	public EnemyObject
	
{
public:
	HungrySailor(PlayerObject* v, int x, int y);
	PlayerObject* victor;
	int shoottimer;
	void move();
	void onHit(std::unique_ptr<Bullet>& bullet);
	void onHit(std::unique_ptr<Explosion>& bullet){}
	void checkEnemyCollisionWithBlock(HitObject* object);
	void checkEnemyCollisionWithPlayer(PlayerObject* object);
	virtual ~HungrySailor(void);
};


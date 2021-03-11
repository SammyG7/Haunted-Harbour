#pragma once
#include "enemyobject.h"
class Jellyfish :
	public EnemyObject
{
public:
	Jellyfish(int, int);
	virtual ~Jellyfish(void);
	int timer;
	void checkEnemyCollisionWithBlock(HitObject* object);
	void move();
	void turnRight();
	void turnLeft();
	void onHit(std::unique_ptr<Bullet>& bullet);
	void onHit(std::unique_ptr<Explosion>& explodes);
	void checkEnemyCollisionWithPlayer(PlayerObject* object);
};


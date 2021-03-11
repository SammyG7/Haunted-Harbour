#pragma once
#include "EnemyObject.h"
class GroundEnemy :
	public EnemyObject
{
public:
	GroundEnemy(int x, int y);
	virtual ~GroundEnemy(void);
	void move();
	void onHit(std::unique_ptr<Bullet>& bullet);
	void onHit(std::unique_ptr<Explosion>& explodes);
	void checkEnemyCollisionWithBlock(HitObject* object);
};


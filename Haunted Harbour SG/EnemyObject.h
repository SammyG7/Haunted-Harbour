#pragma once
#include "weaponsobject.h"
class PlayerObject;
enum class enemyType{
	hag,
	crab,
	jelly,
	sailor,
	keeper
};
class EnemyObject :
	public WeaponsObject
{
public:

	EnemyObject(int posx, int posy):WeaponsObject("../pics/SkullCrab.bmp", 200, 200)
	{
	x = posx;
	y = posy;
	yspeed = 0;
	xspeed = 0;
	deathtimer = 1;
	}
	int xspeed;
	int yspeed;
	int maxhealth;
	int curhealth;
	int deathtimer;
	bool isdead;
	enemyType type;
	virtual void move() = 0;
	virtual void onHit(std::unique_ptr<Bullet>& bullet) = 0;
	virtual void onHit(std::unique_ptr<Explosion>& explodes) = 0;
	virtual void checkEnemyCollisionWithBlock(HitObject* object) = 0;
	virtual void checkEnemyCollisionWithPlayer(PlayerObject* object){};
	virtual ~EnemyObject(void)
	{
	}
};


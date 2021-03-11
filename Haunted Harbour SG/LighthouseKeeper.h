#pragma once
#include "enemyobject.h"
class LighthouseKeeper :
	public EnemyObject
{
	enum class State{
		hideleft,
		hideright,
		followleft,
		followright
	}state;

public:
	LighthouseKeeper(PlayerObject* v, int x, int y);
	PlayerObject* victor;
	bool lookAt;
	void turnLeft();
	void turnRight();
	void move();
	static bool shouldplaysound;
	void onHit(std::unique_ptr<Bullet>& bullet);
	void onHit(std::unique_ptr<Explosion>& bullet){}
	void checkEnemyCollisionWithBlock(HitObject* object);
	void checkEnemyCollisionWithPlayer(PlayerObject* victor);
	virtual ~LighthouseKeeper(void);
};


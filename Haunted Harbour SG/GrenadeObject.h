#pragma once
#include "GraphicsObject.h"
#include "Counter.h"
class EnemyObject;
class GrenadeObject :
	public GraphicsObject
{
public:
	GrenadeObject(void);
	virtual ~GrenadeObject(void);
	int xspeed;
	int yspeed;
	int damage;
	int fired;
	int prevx;
	int prevy;
	bool grounded;
	bool shouldunground;
	Counter<40> grenadetimer;
	void move();
	void checkCollisionWithObject(HitObject* object);
	void checkCollisionWithEnemy(EnemyObject* enemy);
};


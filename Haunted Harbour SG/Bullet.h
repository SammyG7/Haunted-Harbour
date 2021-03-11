#pragma once
#include "GraphicsObject.h"
enum  BulletType{
pbullet,
gbullet,
fball
};



class Bullet:public GraphicsObject 
{
public:
	Bullet(void);
	virtual ~Bullet(void);
	int xspeed;
	int yspeed;
	int damage;
	int distancetravelled;
	int maxdistance;
	int fired;
	bool exploding;
	void move();
	virtual void explode();
	BulletType type;
};


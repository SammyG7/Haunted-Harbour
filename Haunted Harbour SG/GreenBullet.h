#pragma once
#include "bullet.h"
class GreenBullet :
	public Bullet
{
public:
	GreenBullet(void);
	virtual ~GreenBullet(void);
	void explode();
};


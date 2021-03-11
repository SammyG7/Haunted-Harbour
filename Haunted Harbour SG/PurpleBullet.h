#pragma once
#include "bullet.h"
class PurpleBullet :
	public Bullet
{
public:
	PurpleBullet(void);
	virtual ~PurpleBullet(void);
	void explode();
};


#pragma once
#include "bullet.h"
class FireBall :
	public Bullet
{
public:
	FireBall(void);
    void explode();
	virtual ~FireBall(void);
};


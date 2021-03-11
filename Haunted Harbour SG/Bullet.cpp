#include "stdafx.h"
#include "Bullet.h"
#include <cmath>


Bullet::Bullet(void):GraphicsObject(0, 0, 12, 12)
{ 
	fired = true;
	hitHeight = height = 12;
	hitWidth = width = 12;
	distancetravelled = 0;
	maxdistance = 1000;
	xspeed = 0;
	yspeed = 0;
	exploding = false;
    type = pbullet;
	damage = 10;
}


Bullet::~Bullet(void)
{
}

void Bullet::move()
{
	animate();
	if (exploding){
		if (curCell < endCell){

		} else {fired = false;}
	}else{
		x += xspeed;
		y += yspeed;
		distancetravelled += std::abs(xspeed) + std::abs(yspeed);
		if (distancetravelled >= maxdistance){
			distancetravelled = 0;
			fired = false;
		}
	}

}

void Bullet::explode(){

}
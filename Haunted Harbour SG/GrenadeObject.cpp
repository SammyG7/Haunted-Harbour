#include "stdafx.h"
#include "GrenadeObject.h"
#include "EnemyObject.h"


GrenadeObject::GrenadeObject(void):GraphicsObject(0, 0, 246, 285)
{
	xspeed = 0;
	yspeed = 0;
	fired = true;
	width = hitWidth = 25;
	height = hitHeight = 29;
	grounded = false;
	shouldunground = false;
}


GrenadeObject::~GrenadeObject(void)
{
}

void GrenadeObject::move()
{
	prevx = x;
	prevy = y;
	x += xspeed;
	y += yspeed;
	if (xspeed > 0){
		xspeed --;
	} else if (xspeed < 0){
		xspeed ++;
	}
	if (!grounded){
	yspeed += GRAVITY;

	}else if(shouldunground){
		grounded = false;
	}
		shouldunground = true;

}

void GrenadeObject::checkCollisionWithObject(HitObject* object)
{
	if (hitTest(object)){
		shouldunground = false;
		if (prevx + hitWidth <= object->x){
			xspeed *= -1;
			x = object -> x - hitWidth - 1;
		}else if(prevx >= object -> x + object -> hitWidth){
			xspeed *= -1;
			x = object->x + object->hitWidth + 1;
		}else if (prevy + hitHeight <= object->y){				
			if (yspeed <= GRAVITY*4){
				grounded = true;
				yspeed = 0;
			}else{
                yspeed *= -0.48;
			}
			y = object->y - hitHeight;
		}else if (prevy >= object->y + object->hitHeight)
		{
			yspeed *= -0.99;
			y = object->y + object->hitHeight + 1;
		}
		
	}
	if (y + height > GROUND){
		shouldunground = false;
		if (yspeed <= GRAVITY*4){
				grounded = true;
				yspeed = 0;
			}else{
                yspeed *= -0.48;
			}
			y = GROUND - hitHeight;
	}
}

void GrenadeObject::checkCollisionWithEnemy(EnemyObject* enemy)
{

}
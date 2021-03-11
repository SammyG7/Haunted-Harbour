#include "stdafx.h"
#include "HitObject.h"


HitObject::HitObject(void)
{
	hitdisx = 0;
	hitdisy = 0;
}


HitObject::~HitObject(void)
{
}

bool HitObject::hitTest(HitObject* object){
	if (x + hitdisx > object->x + object->hitdisx + object->hitWidth|| 
		y + hitdisy > object->y + object->hitdisy + object->hitHeight||
		x + hitWidth + hitdisx < object->x + object->hitdisx||
		y + hitHeight + hitdisy < object->y + object->hitdisy)
	{
		return false;
	}
	return true;
}


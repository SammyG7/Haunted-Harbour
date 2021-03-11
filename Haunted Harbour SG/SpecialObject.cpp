#include "stdafx.h"
#include "SpecialObject.h"


SpecialObject::SpecialObject(SpecialType itype, int xpos, int ypos, int w, int h):GraphicsObject(xpos, ypos, w, h)
{
	type = itype;
}


SpecialObject::~SpecialObject(void)
{
}

void SpecialObject::checkPlayerCollisionWithSpecial(HitObject* object)
{
	if (hitTest(object)){
		callback(object);
	}
}
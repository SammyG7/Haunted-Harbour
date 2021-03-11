#pragma once
#include "GraphicsObject.h"
#include <functional>
enum class SpecialType{
	key,
	lChest,
	uChest,
	powerup
};
class SpecialObject :
	public GraphicsObject
{
public:
	SpecialObject(SpecialType type, int xpos, int ypos, int w, int h);
	SpecialType type;
	void checkPlayerCollisionWithSpecial(HitObject* object);
	std::function<void(HitObject*)> callback;
	virtual ~SpecialObject(void);
};


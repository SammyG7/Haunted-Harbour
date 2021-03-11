#pragma once
#include "PlayerObject.h"
class HealthBar
{
public:
	HealthBar(PlayerObject* v);
	PlayerObject* victor;
	void draw(HDC screen);
	~HealthBar(void);
};


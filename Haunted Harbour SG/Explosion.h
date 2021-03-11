#pragma once
#include "graphicsobject.h"
class Explosion :
	public GraphicsObject
{
public:
	Explosion(void);
	virtual ~Explosion(void);
	bool fired;
	int damage;
};


#pragma once
#include "GraphicsObject.h"
class BackgrondObject: public GraphicsObject
{
public:
	BackgrondObject(CString filname, int posx, int posy, int h, int w, double ss);
	~BackgrondObject(void);
	void draw(HDC offScreenDC);
	double scrollSpeed;
};


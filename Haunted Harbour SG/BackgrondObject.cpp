#include "stdafx.h"
#include "BackgrondObject.h"


BackgrondObject::BackgrondObject(CString filename, int posx, int posy, int w, int h, double ss):GraphicsObject(filename,posx,posy)
{
	width = w;
	height = h;
	scrollSpeed = ss;
}


BackgrondObject::~BackgrondObject(void)
{
}

void BackgrondObject::draw(HDC offScreenDC)
{int relativeX=(int)((x-mapPosition)*scrollSpeed)%width;
HDC ScreenDC;
ScreenDC = offScreenDC;
image.SetTransparentColor(RGB(255, 174, 201));
image.TransparentBlt(ScreenDC, relativeX , y, width, height, 0, 0, width, height);
image.TransparentBlt(ScreenDC, relativeX + width, y, width, height, 0, 0, width, height);
image.TransparentBlt(ScreenDC, relativeX - width, y, width, height, 0, 0, width, height);
image.TransparentBlt(ScreenDC, relativeX + width + width, y, width, height, 0, 0, width, height);
image.TransparentBlt(ScreenDC, relativeX - width - width, y, width, height, 0, 0, width, height);
}

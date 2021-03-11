#pragma once
#include "HitObject.h"
class GraphicsObject:public HitObject
{
public:
	GraphicsObject(CString filename, int xpos, int ypos, int w=55, int h = 42);
	GraphicsObject(int xpos, int ypos, int w, int h);
	virtual ~GraphicsObject(void);
	void draw(HDC offScreenDC);
	void draw(HDC offScreenDC, CImage& image);
	void drawAlpha(HDC offScreenDC, CImage& image);
	void animate();
	void drawStatic(HDC offScreenDC);
	CString ID;
	CImage image;
	int height;
	int width;
	int picX;
	int picY;
	int curCell;
	int endCell;
	int startCell;
	bool loopCells;
	int xdis;
	int ydis;
};


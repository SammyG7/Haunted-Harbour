#include "stdafx.h"
#include "GraphicsObject.h"

GraphicsObject::GraphicsObject(int xpos, int ypos, int w, int h){

width = w;
height= h;
x = xpos;
y = ypos;
picX = 0;
picY = 0;
curCell = 0;
endCell = 0;
startCell = 0;
loopCells = true;
hitHeight = h;
hitWidth = w;
xdis = 0;
ydis = 0;
}
GraphicsObject::GraphicsObject(CString filename,int xpos,int ypos, int w, int h)
{
	*this = GraphicsObject(xpos, ypos, w, h);
	ID = filename;
	image.Load(ID);
}


GraphicsObject::~GraphicsObject(void)
{
}

void GraphicsObject::draw(HDC offScreenDC)
{HDC ScreenDC;
ScreenDC = offScreenDC;
image.SetTransparentColor(RGB(255, 174, 201));
image.TransparentBlt(ScreenDC, x - mapPosition, y, width, height, picX, picY, width, height);
}

void GraphicsObject::draw(HDC offScreenDC, CImage& drawimage)
{HDC ScreenDC;
ScreenDC = offScreenDC;
drawimage.SetTransparentColor(RGB(255, 174, 201));
drawimage.TransparentBlt(ScreenDC, x - mapPosition, y, width, height, picX, picY, width, height);
}

void GraphicsObject::drawAlpha(HDC offScreenDC, CImage& drawimage)
{HDC ScreenDC;
ScreenDC = offScreenDC;
drawimage.SetTransparentColor(RGB(255, 174, 201));
drawimage.AlphaBlend(ScreenDC, x - mapPosition, y, width, height, picX, picY, width, height, 100);
}

void GraphicsObject::drawStatic(HDC offScreenDC)
{HDC ScreenDC;
ScreenDC = offScreenDC;
image.SetTransparentColor(RGB(255, 174, 201));
image.TransparentBlt(ScreenDC, x, y, width, height, picX, picY, width, height);
}


void GraphicsObject::animate()
{
	//Multiplies cell number by cell width to find where you are
	picX = width*curCell + xdis;
	//Increments the current frame of animation 
	curCell += 1;
	//Reset if at end of cells
	if (curCell >= endCell){
		if(loopCells == true){
	curCell = startCell;
	}else{
	curCell = endCell;
	}
	}
	
	
}



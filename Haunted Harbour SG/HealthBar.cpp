#include "stdafx.h"
#include "HealthBar.h"


HealthBar::HealthBar(PlayerObject* v)
{
	victor = v;
}


HealthBar::~HealthBar(void)
{
}

void HealthBar::draw(HDC screen)
{
	int recty;
	HBRUSH hbrRed, hbrWhite;
	hbrRed=CreateSolidBrush(RGB(255,0,0));
	hbrWhite=CreateSolidBrush(RGB(255,255,255));
	SelectObject(screen, hbrWhite);
	Rectangle(screen, 10, 10, 20, 90);
    SelectObject(screen, hbrRed);
	recty = double(victor->maxhealth - victor->curhealth) / double(victor->maxhealth) * 80;
	Rectangle(screen, 10, recty + 10, 20, 90);
	DeleteObject(hbrRed);
	DeleteObject(hbrWhite);
}

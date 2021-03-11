#pragma once
class HitObject
{
public:
	HitObject(void);
	~HitObject(void);
	int x;
	int y;
	int hitWidth;
	int hitHeight;
	int hitdisx;
	int hitdisy;
	bool hitTest(HitObject* object);
};


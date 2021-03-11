#pragma once
#include "WeaponsObject.h"
#define MOVERIGHT 1
#define MOVELEFT 2
#define JUMPRIGHT 3
#define JUMPLEFT 4
#define SHOOTRIGHT 5
#define SHOOTLEFT 6
#define STANDRIGHT 7
#define STANDLEFT 8
class PlayerObject: public WeaponsObject
{
public:
	PlayerObject(void);
	virtual ~PlayerObject(void);
	int xspeed;
	int yspeed;
	int state;
	int curhealth;
	int maxhealth;
	int invincible;
	int startx;
	int starty;
	int shoottimer;
	bool godmode;
	bool stopright;
	bool stopleft;
	bool isdead;
	bool canjump;
	bool facing;
	void resetPlayer();
	void move();
	void setMoveRight();
	void setMoveLeft();
	void setJumpRight();
	void setJumpLeft();
	void setShootRight();
	void setShootLeft();
	void setStandLeft();
	void setStandRight();
	void checkCollisionWithBlock(HitObject* object);
	bool isJumping();
	void onHit(std::unique_ptr<Bullet>& bullet); 
	void decreaseHealth(int);
};


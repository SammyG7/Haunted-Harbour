#pragma once
#include "graphicsobject.h"
#include "Bullet.h"
#include <vector>
#include "PurpleBullet.h"
#include "GreenBullet.h"
#include "FireBall.h"
#include "soundclass.h"
#include "GrenadeObject.h"
#include "Explosion.h"
#include <memory>

class WeaponsObject :
	public GraphicsObject
{
public:
	WeaponsObject(CString filename, int xpos, int ypos);
	virtual ~WeaponsObject(void);
	std::vector<std::unique_ptr<Bullet>> bullets;
	std::vector<std::unique_ptr<GrenadeObject>> grenades;
	std::vector<std::unique_ptr<Explosion>> explodes;
	GraphicsObject pbullet_image;
	GraphicsObject gbullet_image;
	GraphicsObject fball_image;
	BulletType bullettype;
	void fireBullet(int x, int y, int xs, int ys);
	void throwGrenade(int x, int y, int xs, int ys);
	void drawBullets(HDC offscreenDC);
	void drawGrenades(HDC offScreenDC, CImage &image, CImage &image2);
	void moveBullets();
	void checkBulletCollisionWithBlock(HitObject* object);
	void checkGrenadeCollisionWithBlock(HitObject* object);
	void checkBulletCollisionWithObject(WeaponsObject* object);
	void checkExplosionCollisionWithObject(WeaponsObject* object);
	void explodeGrenades();
	virtual void onHit(std::unique_ptr<Bullet>& bullet);
	virtual void onHit(std::unique_ptr<Explosion>& explodes);
	int prevx;
	int prevy;
	bool hitable;
	static SoundClass* m_sound;
	
};


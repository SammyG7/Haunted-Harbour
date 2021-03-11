#include "stdafx.h"
#include "WeaponsObject.h"

SoundClass* WeaponsObject::m_sound;

WeaponsObject::WeaponsObject(CString filename, int xpos, int ypos):GraphicsObject(filename, xpos, ypos)
	, pbullet_image("../Pics/PurpleFire.bmp", 0, 0), gbullet_image("../Pics/GreenFire.bmp", 0, 0), fball_image("../Pics/Fireballs.bmp", 0, 0) 
{
	bullettype = BulletType::pbullet;
	hitable = true;
}

WeaponsObject::~WeaponsObject(void)
{
}

void WeaponsObject::drawBullets(HDC offscreenDC)
{ 
	for (auto&& bullet : bullets){
		switch(bullet->type){
		case BulletType:: pbullet:
			bullet->draw(offscreenDC, pbullet_image.image);
			break;
		case BulletType :: gbullet:
			bullet->draw(offscreenDC, gbullet_image.image);
			break;
		case BulletType :: fball:
			bullet->draw(offscreenDC, fball_image.image);
			break;
		}
	}

}
void WeaponsObject::fireBullet(int ix, int iy, int xs, int ys)
{
	std::unique_ptr<Bullet> bullet;
	switch(bullettype){
	case BulletType::pbullet:
		bullet.reset(new PurpleBullet());
		break;
	case BulletType::gbullet:
		bullet.reset(new GreenBullet());
		break;
	case BulletType::fball:
		bullet.reset(new FireBall());
		break;
	}
	bullet->x = ix;
	bullet->y = iy;
	bullet->xspeed = xs;
	bullet->yspeed = ys;
	bullets.push_back(std::move(bullet));

}
template <typename T>
bool isFired(const T& bullet){
	return !bullet->fired;
}

void WeaponsObject::moveBullets()
{
	for (auto&& bullet: bullets){
		bullet->move();
	}
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),isFired<std::unique_ptr<Bullet>>), bullets.end());

	for (auto&& grenade: grenades){
		grenade->move();
	}
	grenades.erase(std::remove_if(grenades.begin(), grenades.end(),isFired<std::unique_ptr<GrenadeObject>>), grenades.end());
	explodes.erase(std::remove_if(explodes.begin(), explodes.end(),isFired<std::unique_ptr<Explosion>>), explodes.end());
	for (auto&& explode: explodes){
		if (explode->curCell >= 6)
			explode->fired= false;
		explode->animate();
	}
	
}

void WeaponsObject::checkBulletCollisionWithBlock(HitObject* object){
	for (auto&& bullet: bullets){
		if (!bullet->exploding && object->hitTest(bullet.get())){
			if (std::abs(bullet->x - object->x) < std::abs(bullet->x - (object->x + object->hitWidth))){
				bullet->x = object->x;
			}else if(std::abs(bullet->x - object->x) > std::abs(bullet->x -(object->x + object->hitWidth))){
				bullet->x = object->x + object->hitWidth;
			}
			bullet->explode();
		}
	}
}

void WeaponsObject::checkGrenadeCollisionWithBlock(HitObject* object){
	for (auto&& grenade: grenades){
			grenade->checkCollisionWithObject(object);	
	}
}

void WeaponsObject::checkBulletCollisionWithObject(WeaponsObject* object){
	for (auto&& bullet: bullets){
		if (!bullet->exploding && object->hitable &&object->hitTest(bullet.get())){
			if (std::abs(bullet->x - object->x) < std::abs(bullet->x - (object->x + object->hitWidth))){
				bullet->x = object->x;
			}else if(std::abs(bullet->x - object->x) > std::abs(bullet->x -(object->x + object->hitWidth))){
				bullet->x = object->x + object->hitWidth;
			}
			bullet->explode();
			object->onHit(bullet);
		}
	}
}

void WeaponsObject::checkExplosionCollisionWithObject(WeaponsObject* object){
	for (auto&& explode: explodes){
		if (object->hitable && object->hitTest(explode.get())){
			object->onHit(explode);
		}
	}
}

void WeaponsObject::onHit(std::unique_ptr<Bullet>& bullet){

}

void WeaponsObject::onHit(std::unique_ptr<Explosion>& explodes){

}

void WeaponsObject::throwGrenade(int x, int y, int xs, int ys)
{
	std::unique_ptr<GrenadeObject> grenade (new GrenadeObject);
	
	grenade->x = x;
	grenade->y = y;
	grenade->xspeed = xs;
	grenade->yspeed = ys;
	grenades.push_back(std::move(grenade));
}

void WeaponsObject::drawGrenades(HDC offScreenDC, CImage &image, CImage &image2)
{
	for (auto&& grenade : grenades){	
			//grenade->drawAlpha(offScreenDC, image);
			grenade->draw(offScreenDC, image);
	}
	for (auto&& explosion : explodes){	
			explosion->draw(offScreenDC, image2);
	}
}

void WeaponsObject::explodeGrenades(){
	for (auto&& grenade : grenades){
		if (grenade->grenadetimer()){
			std::unique_ptr<Explosion> e(new Explosion()) ;
			m_sound->PlayWaveFile(Sounds::grenade);
			int gx = grenade->x + grenade->width/2;
			int gy = grenade->y + grenade->height/2;
			int ex = gx - e->width/2;
			int ey = gy - e->height/2;
			e->x = ex;
			e->y = ey;
			explodes.push_back(std::move(e));
			grenade->fired = false;
		}
	}
}
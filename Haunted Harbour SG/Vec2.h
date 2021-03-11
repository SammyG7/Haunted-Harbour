#include <cmath>
struct Vec2
{
	Vec2(){}
	Vec2(float ix, float iy) : x(ix), y(iy){}
	Vec2 operator*(const float w){
		Vec2 v;
		v.x = w*x;
		v.y = w*y;
	return v;
	}
	float magnitude(){
	return std::sqrt(x*x + y*y);
	}
	float x;
	float y;

};

#include "./Shot.hpp"

Shot::Shot(Vec2 p, bool isLeft){
	pos = p;
	vel = Vec2(bulletSpeed * (isLeft ? 1 : -1), 0).rotate(Radians(2 * Random(-5, 5)));
}

int Shot::update(Circle rivalPlayer){
	pos += vel;
	return 0;
}

void Shot::draw(){
	Circle(pos, 8).draw(Color(L"#ffff00"));
}

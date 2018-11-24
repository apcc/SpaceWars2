#include "./Shot.hpp"

Shot::Shot(Vec2 p, bool isLeft){
	pos = p;
	vel = Vec2(bulletSpeed * (isLeft ? 1 : -1), 0).rotate(Radians(Random(-5, 5)));
}

void Shot::update(){
	pos += vel;
}

void Shot::draw(){
	Circle(pos, 8).draw(Color(L"#ffff00"));
}

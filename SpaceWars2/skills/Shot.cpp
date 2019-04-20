#include "./Shot.hpp"

bool Shot::update(Vec2 _myPos, Vec2 _oppPos) {
	return Bullet::update(_myPos, _oppPos);
}

void Shot::draw(){
	getShape().draw(Color(L"#ffff00"));
}

bool Shot::isVisible(){
	return getShape().intersects(Rect(0, 0, Config::WIDTH + 1, Config::HEIGHT + 1));
}

int Shot::getDamage(Circle _circle) {
	if(_circle.intersects(this->getShape())){
		shouldBeDestroyed=true;
		return 10;
	}
	return 0;
}

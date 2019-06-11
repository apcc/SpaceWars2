#include "./Shot.hpp"

bool Shot::update(Vec2 _myPos, Vec2 _oppPos) {
	return Bullet::update(_myPos, _oppPos);
}

void Shot::draw(){
	getShape().draw(Color(L"#ffff00"));
}

bool Shot::isVisible(){
	return getShape().intersects(activeField);
}

int Shot::getDamage(Circle _circle) {
	if(_circle.intersects(this->getShape())){
		shouldBeDestroyed=true;
		return 15;
	}
	return 0;
}

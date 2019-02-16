#include "./Shot.hpp"

bool Shot::update(Vec2 myPos, Vec2 oppPos) {
	return Bullet::update(myPos, oppPos);
}

void Shot::draw(){
	getShape().draw(Color(L"#ffff00"));
}

bool Shot::isInvisible(){
	return !getShape().intersects(Rect(0, 0, Config::Width + 1, Config::Height + 1));
}

int Shot::getDamage(Circle circle) {
	if(circle.intersects(this->getShape())){
		shouldBeDestroyed=true;
		return 2;
	}
	return 0;
}

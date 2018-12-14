#include "./Shot.hpp"

bool Shot::update() {
	return Bullet::update();
}

void Shot::draw(){
	getShape().draw(Color(L"#ffff00"));
}

bool Shot::isInvisible(){
	return !getShape().intersects(Rect(0, 0, Config::Width + 1, Config::Height + 1));
}

bool Shot::intersects(Circle circle) {
	return circle.intersects(this->getShape());
}

#include "./Shot.hpp"

bool Shot::update() {
	return Bullet::update();
}

void Shot::draw(){
	this->getShape().draw(Color(L"#ffff00"));
}

bool Shot::isInvisible(){
	return !Circle(pos, 8).intersects(Rect(0, 0, Config::Width + 1, Config::Height + 1));
}

bool Shot::intersects(Circle circle) {
	return circle.intersects(this->getShape());
}

#include "./Reflection.hpp"

bool Reflection::update(Vec2 myPos, Vec2 oppPos) {
	return Bullet::update(myPos, oppPos);
}

void Reflection::draw() {
	getShape().draw(Color(isLeft ? L"#00ffff" : L"#0000ff"));
}

bool Reflection::isVisible() {
	//return !getShape().intersects(Rect(0, 0, Config::WIDTH + 1, Config::HEIGHT + 1));
	if (getShape().intersects(Rect(-20, Config::HEIGHT, Config::WIDTH + 20, Config::HEIGHT + 20))) {
		vel.y = -vel.y;
	}
	if (getShape().intersects(Rect(-20, -20, Config::WIDTH+20, 0))) {
		vel.y = -vel.y;
	}
	if (getShape().intersects(Rect(Config::WIDTH, -20, Config::WIDTH+20, Config::HEIGHT+20))) {
		vel.x = -vel.x;
		ReflectCount++;
	}
	if (getShape().intersects(Rect(-20, 20, 0, Config::HEIGHT+20))) {
		vel.x = -vel.x;
		ReflectCount++;
	}
	if (ReflectCount == 3) {
		return false;
	}
	else {
		return true;
	}
}

int Reflection::getDamage(Circle circle) {
	if (circle.intersects(this->getShape())) {
		shouldBeDestroyed = true;
		return 2;
	}
	return 0;
}

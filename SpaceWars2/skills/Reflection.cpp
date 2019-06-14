#include "./Reflection.hpp"

bool Reflection::update(Vec2 myPos, Vec2 oppPos) {
	return Bullet::update(myPos, oppPos);
}

void Reflection::draw() {
	getShape().draw(Color(isLeft ? L"#00ffff" : L"#00ff00"));
}

bool Reflection::isVisible() {
	//return !getShape().intersects(Rect(0, 0, Config::WIDTH + 1, Config::HEIGHT + 1));
	/*if (getShape().intersects(Rect(-20, Config::HEIGHT, Config::WIDTH + 20, Config::HEIGHT + 20))) { //下
		vel.y = -vel.y;
	}
	if (getShape().intersects(Rect(-20, -20, Config::WIDTH+20, 0))) { //上
		vel.y = -vel.y;
	}
	if (getShape().intersects(Rect(Config::WIDTH, -20, Config::WIDTH+20, Config::HEIGHT+20))) { //右
		vel.x = -vel.x;
		ReflectCount++;
	}
	if (getShape().intersects(Rect(-20, 20, 0, Config::HEIGHT+20))) { //左
		vel.x = -vel.x;
		ReflectCount++;
	}*/

	if (activeField.y > pos.y) {
		vel.y *= -1;
	}
	if (activeField.y + activeField.h < pos.y) {
		vel.y *= -1;
	}
	if (ReflectCount < 2) {
		if (activeField.x > pos.x) {
			vel.x *= -1;
			ReflectCount++;
		}
		if (activeField.x + activeField.w < pos.x) {
			vel.x *= -1;
			ReflectCount++;
		}
	}
	return getShape().intersects(activeField);
}

int Reflection::getDamage(Circle circle) {
	if (circle.intersects(this->getShape())) {
		shouldBeDestroyed = true;
		return 20;
	}
	return 0;
}

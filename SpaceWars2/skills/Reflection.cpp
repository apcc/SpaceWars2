#include "./Reflection.hpp"

bool Reflection::update(Vec2 myPos, Vec2 oppPos) {
	return Bullet::update(myPos, oppPos);
}

void Reflection::draw() {
	getShape().draw(Color(isLeft ? L"#00ffff" : L"#0000ff"));
}

bool Reflection::isInvisible() {
	//return !getShape().intersects(Rect(0, 0, Config::Width + 1, Config::Height + 1));
	if (getShape().intersects(Rect(-20, Config::Height, Config::Width + 20, Config::Height + 20))) {
		vel.y = -vel.y;
	}
	if (getShape().intersects(Rect(-20, -20, Config::Width+20, 0))) {
		vel.y = -vel.y;
	}
	if (getShape().intersects(Rect(Config::Width, -20, Config::Width+20, Config::Height+20))) {
		vel.x = -vel.x;
		ReflectCount++;
	}
	if (getShape().intersects(Rect(-20, 20, 0, Config::Height+20))) {
		vel.x = -vel.x;
		ReflectCount++;
	}
	if (ReflectCount == 3) {
		return 1;
	}
	else {
		return 0;
	}
}

int Reflection::getDamage(Circle circle) {
	if (circle.intersects(this->getShape())) {
		shouldBeDestroyed = true;
		return 2;
	}
	return 0;
}

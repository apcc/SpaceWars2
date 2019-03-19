#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Reflection : public Bullet {
private:
	Circle getShape() { return Circle(pos, 8); }
public:
	Reflection(Vec2 p, bool left) : Bullet(p, left) {
		vel = Vec2(bulletSpeed * (left ? 1 : -1), 0).rotate(Radians(Random(-40, 40)));
	}

	bool update(Vec2 myPos, Vec2 oppPos) override;
	void draw() override;
	bool isInvisible() override;
	int getDamage(Circle circle) override;
	int ReflectCount = 0;

	const static int bulletSpeed = 5;
};
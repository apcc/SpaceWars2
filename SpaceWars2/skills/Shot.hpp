#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Shot : public Bullet {
private:
	Circle getShape() { return Circle(pos,8); }
public:
	Shot(Vec2 p, bool left) : Bullet(p, left) {
		vel = Vec2(bulletSpeed * (left ? 1 : -1), 0).rotate(Radians(Random(-5, 5)));
	}

	bool update() override;
	void draw() override;
	bool isInvisible() override;
	bool intersects(Circle circle) override;
	int getDamage() override { return 2; }

	const static int bulletSpeed = 20;
};

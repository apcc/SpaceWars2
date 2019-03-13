#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Shot : public Bullet {
private:
	Circle getShape() { return Circle(pos,8); }
public:
	Shot(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		vel = Vec2(bulletSpeed * (isLeft ? 1 : -1), 0).rotate(Radians(Random(-5, 5)));
	}

	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isInvisible() override;
	int getDamage(Circle _circle) override;

	const static int bulletSpeed = 20;
};

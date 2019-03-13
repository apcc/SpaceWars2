#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Grenade : public Bullet {
private:
	Circle getShape() { return Circle(pos, (fuse>EXPLODE_TIMING)?8:EXPLODE_RADIUS); }
	int fuse;
	const static int EXPLODE_TIMING=20;
	const static int EXPLODE_RADIUS=300;
public:
	Grenade(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		vel = Vec2(bulletSpeed * (_isLeft ? 1 : -1), 0).rotate(Radians(Random(-5, 5)));
		fuse = 1 * 60 + EXPLODE_TIMING;
	}

	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isInvisible() override;
	int getDamage(Circle _circle) override;
	void explode();

	const static int bulletSpeed = 10;
};

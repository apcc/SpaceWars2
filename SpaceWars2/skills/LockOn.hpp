#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class LockOn : public Bullet {
private:
	Circle getShape() { return Circle(pos, 5); }
public:
	LockOn(Vec2 p, bool left) : Bullet(p, left) {

	}
	bool update(Vec2 myPos, Vec2 oppPos) override;
	void draw() override;
	bool isInvisible() override;
	int getDamage(Circle circle) override;

};

#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Flame : public Bullet {
private:
	Vec2 ppos;
	Circle getShape() { return Circle(pos, 20); }
	RectF getShapeFlameBelt() {
		if (isLeft) {
			if (bulletSpeed * 80 < pos.x - ppos.x) {
				return  RectF(pos.x, pos.y - 20, -bulletSpeed * 80, 40);
			}
			else {
				return RectF(pos.x, pos.y - 20, -(pos.x - ppos.x), 40);
			}
		}
		else {
			if (bulletSpeed * 80 < ppos.x - pos.x) {
				return  RectF(pos.x + bulletSpeed, pos.y - 20, bulletSpeed * 80, 40);
			}
			else {
				return RectF(pos.x, pos.y - 20, -(pos.x - ppos.x), 40);
			}
		}
	}
public:
	Flame(Vec2 p, bool left) : Bullet(p, left) {
		vel = Vec2(bulletSpeed * (left ? 1 : -1), 0)/*.rotate(Radians(Random(-5, 5)))*/;
		ppos = p;
	}

	bool update(Vec2 myPos, Vec2 oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle circle) override;

	const static int bulletSpeed = 6;
};

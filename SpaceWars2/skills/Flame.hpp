#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Flame : public Bullet {
private:
	Vec2 ppos;
	Circle getShape() { return Circle(pos, shrinkRate * 20); }
	RectF getShapeFlameBelt() {
		if (isLeft) {
			if (bulletSpeed * 120 * shrinkRate < pos.x - ppos.x) {
				return  RectF(pos.x, pos.y - 20*shrinkRate, -bulletSpeed * 120*shrinkRate, 40*shrinkRate);
			}
			else {
				return RectF(pos.x, pos.y - 20 * shrinkRate, -(pos.x - ppos.x)*shrinkRate, 40*shrinkRate);
			}
		}
		else {
			if (bulletSpeed * 120 < ppos.x - pos.x) {
				return  RectF(pos.x + bulletSpeed, pos.y - 20, bulletSpeed * 120, 40);
			}
			else {
				return RectF(pos.x, pos.y - 20, -(pos.x - ppos.x), 40);
			}
		}
	}
	Vec2 Shrink(Rect _area) override {
		Bullet::Shrink(_area);
		ppos = pos;
		return pos;
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

	const static int bulletSpeed = 4;
};

#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Flame : public Bullet {
private:
	Vec2 ppos;
	Circle getShape() { return Circle(pos, shrinkRate * 35); }
	RectF getShapeFlameBelt() {
		if (isLeft) {
			if (bulletSpeed * 80 * shrinkRate < pos.x - ppos.x) {
				return  RectF(pos.x, pos.y - 35*shrinkRate, -bulletSpeed * 80*shrinkRate, 70*shrinkRate);
			}
			else {
				return RectF(pos.x, pos.y - 35*shrinkRate, -(pos.x - ppos.x), 70*shrinkRate);
			}
		}
		else {
			if (bulletSpeed * 80 * shrinkRate < ppos.x - pos.x) {
				return  RectF(pos.x + bulletSpeed*shrinkRate, pos.y - 35*shrinkRate, bulletSpeed * 80 * shrinkRate, 70*shrinkRate);
			}
			else {
				return RectF(pos.x, pos.y - 35*shrinkRate, -(pos.x - ppos.x), 70*shrinkRate);
			}
		}
	}
	Vec2 shrink(Rect _area) override {
		Bullet::shrink(_area);
		ppos = pos;
		return pos;
	}
public:
	Flame(Vec2 p, bool left) : Bullet(p, left) {
		vel = Vec2(bulletSpeed * (left ? 1 : -1), 0)/*.rotate(Radians(Random(-5, 5)))*/;
		ppos = p;
		SoundAsset(L"flame").playMulti(0.4);
	}

	bool update(Vec2 myPos, Vec2 oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle circle) override;

	const static int bulletSpeed = 6;
};

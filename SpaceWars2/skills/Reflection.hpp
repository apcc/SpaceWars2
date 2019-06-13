#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Reflection : public Bullet {
private:
	Circle getShape() { return Circle(pos, drawRate * 8); }
	double drawRate = 1;
public:
	Reflection(Vec2 p, bool left) : Bullet(p, left) {
		vel = Vec2(bulletSpeed * (left ? 1 : -1), 0).rotate(Radians(Random(-40, 40)));
		SoundAsset(L"reflection").playMulti(0.4);
	}

	bool update(Vec2 myPos, Vec2 oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle circle) override;
	int ReflectCount = 0;

	Vec2 shrink(Rect _area) override {
		Bullet::shrink(_area);
		drawRate = shrinkRate * 2;
		return pos;
	}

	const static int bulletSpeed = 8;
};

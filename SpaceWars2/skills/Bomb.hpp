#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"
#include "../CommonData.hpp"


class Bomb final : public Bullet {
private:
	bool explosion = false;
	static int numberOfLUsed;
	static int numberOfRUsed;
	int BombUsed;
	int nowBombNumber;
	int bulletSpeed = 20;
	int fuse = 0;
	double drawRate = 1;
	const static int EXPLODE_RADIUS = 100;
	Circle getShape() {
		if (explosion) {
			return Circle(pos, EXPLODE_RADIUS);
		}
		else {
			return Circle(pos, 40);
		}

	}
public:
	Bomb(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		vel = Vec2(bulletSpeed * (isLeft ? 1 : -1), 0);
		SoundAsset(L"bomb").playMulti(0.8);

		if (isLeft) {
			numberOfLUsed++;
		}
		else {
			numberOfRUsed++;
		}
		nowBombNumber = (isLeft ? numberOfLUsed : numberOfRUsed);
	}
	Vec2 Shrink(Rect _area) override {
		Bullet::Shrink(_area);
		drawRate = shrinkRate * 2;
		return pos;
	}
	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
};

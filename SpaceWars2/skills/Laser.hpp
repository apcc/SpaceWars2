#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Laser : public Bullet {
private:
	bool isCharging = true;
	int energy = 1;
	int DamageDeal = 0;
	Vec2 ppos;
	bool isLeft;
	bool isLInvalid = false;
	bool isRInvalid = false;
	static bool isLShooting;
	static bool isRShooting;

	const static int CHARGE_TIME_LIMIT = 1000; // charge時間の上限
	const static int WAITING_TIME = 100; // 実行までにかかるwaiting時間
	const static int COOLDOWN_TIME = 1000; // 実行後のクールダウン時間（要検討）

	RectF getShapeShooten(){
		if(isLeft)	return RectF(ppos - Vec2(0, energy),  Config::WIDTH, energy * 2);
		else		return RectF(ppos - Vec2(Config::WIDTH, energy), Config::WIDTH, energy * 2);
	}
	Circle getShapeCharging(){
		if(isLeft)	return Circle(ppos + Vec2( 25 + energy, 0), energy);
		else		return Circle(ppos + Vec2(-25 - energy, 0), energy);
	}

public:
	Laser(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		isLeft = _isLeft;
		if (isLeft ? isLShooting : isRShooting) { // if another instance is already created and still alive...
			(isLeft ? isLInvalid : isRInvalid) = true; // this laser is disabled
		} else (isLeft ? isLShooting : isRShooting) = true;
	}
	~Laser() override {
		if (!(isLeft ? isLInvalid : isRInvalid))
			(isLeft ? isLShooting : isRShooting) = false;
	};

	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isInvisible() override;
	int getDamage(Circle _circle) override;

	const static int bulletSpeed = 10;
};

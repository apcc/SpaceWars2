#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class Laser : public Bullet {
private:
	bool isCharging = true;
	int energy = 1;
	int DamageDeal = 0;
	Vec2 *ppos;
	bool isLeft;
	bool isInvalid = false;
	static bool isInvoked;

	const static int CHARGE_TIME_LIMIT = 1000; // charge時間の上限
	const static int WAITING_TIME = 100; // 実行までにかかるwaiting時間
	const static int COOLDOWN_TIME = 1000; // 実行後のクールダウン時間（要検討）

	RectF getShapeShooten(){
		if(isLeft)	return RectF(*ppos - Vec2(0, energy),  Config::Width, energy * 2);
		else		return RectF(*ppos - Vec2(Config::Width, energy), Config::Width, energy * 2);
	}
	Circle getShapeCharging(){
		if(isLeft)	return Circle(*ppos + Vec2( 25 + energy, 0), energy);
		else		return Circle(*ppos + Vec2(-25 - energy, 0), energy);
	}

public:
	Laser(Vec2 *p, bool left) : Bullet(p, left) {
		ppos = p;
		isLeft = left;
		if (isInvoked) { // if another instance is already created and still alive...
			isInvalid = true; // this laser is disabled
		} else isInvoked = true;
	}
	~Laser() override {
		if (!isInvalid)
			isInvoked = false;
	};

	bool update() override;
	void draw() override;
	bool isInvisible() override;
	int getDamage(Circle circle) override;

	const static int bulletSpeed = 10;
};

#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"
#include "../Scenes/Game.hpp"


class VLaser final : public Bullet {
private:
	bool isCharging = true;
	int energy = 1;
	Vec2 myPos;
	bool isLeft;
	bool isLInvalid = false;
	bool isRInvalid = false;
	static bool isLShooting;
	static bool isRShooting;
	double drawRate = 1;

	const static int CHARGE_TIME_LIMIT = 1000; // charge時間の上限
	const static int WAITING_TIME = 100; // 実行までにかかるwaiting時間
	const static int COOLDOWN_TIME = 1000; // 実行後のクールダウン時間（要検討）

	RectF getShapeShotten() {
		if(isLeft)	return RectF(myPos - Vec2(0, energy * shrinkRate), { activeField.x + activeField.w - myPos.x, energy * 2 * shrinkRate});
		else		return RectF({ activeField.x, myPos.y - energy * shrinkRate }, myPos.x - activeField.x, energy * 2 * shrinkRate);

	}
	Circle getShapeCharging() {
		if(isLeft)	return Circle(myPos + Vec2((25 + energy)*drawRate, 0), energy*drawRate);
		else		return Circle(myPos + Vec2((-25 - energy)*drawRate, 0), energy*drawRate);
	}

public:
	VLaser(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		isLeft = _isLeft;
		if (isLeft ? isLShooting : isRShooting) { // if another instance is already created and still alive...
			(isLeft ? isLInvalid : isRInvalid) = true; // this laser is disabled
		}
		else {
			(isLeft ? isLShooting : isRShooting) = true;
			++(isLeft ? Data::LPlayer : Data::RPlayer).mainSkillCnt;
		}
	}
	~VLaser() override {
		if (!(isLeft ? isLInvalid : isRInvalid))
			(isLeft ? isLShooting : isRShooting) = false;
	};


	Vec2 shrink(Rect _area) override {
		Bullet::shrink(_area);
		drawRate = shrinkRate * 2;
		return pos;
	}
	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
	Vec2 shrinkVec2(Vec2 _d);
	const static int bulletSpeed = 10;
};

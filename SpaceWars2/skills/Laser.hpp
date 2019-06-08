#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"
#include "../Scenes/Game.hpp"


class Laser final : public Bullet {
private:
	bool isCharging = true;
	int energy = 1;
	Vec2 myPos;
	bool isLeft;
	bool isLInvalid = false;
	bool isRInvalid = false;
	static bool isLShooting;
	static bool isRShooting;
	Sound chargeSound;
	Sound laserSound;

	const static int CHARGE_TIME_LIMIT = 1000; // charge時間の上限
	const static int WAITING_TIME = 100; // 実行までにかかるwaiting時間
	const static int COOLDOWN_TIME = 1000; // 実行後のクールダウン時間（要検討）

	RectF getShapeShotten(){
		if(isLeft)	return RectF(myPos - Vec2(0, energy),  Config::WIDTH, energy * 2);
		else		return RectF(myPos - Vec2(Config::WIDTH, energy), Config::WIDTH, energy * 2);
	}
	Circle getShapeCharging(){
		if(isLeft)	return Circle(myPos + Vec2( 25 + energy, 0), energy);
		else		return Circle(myPos + Vec2(-25 - energy, 0), energy);
	}

public:
	Laser(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		isLeft = _isLeft;
		if (isLeft ? isLShooting : isRShooting) { // if another instance is already created and still alive...
			(isLeft ? isLInvalid : isRInvalid) = true; // this laser is disabled
		}
		else {
			(isLeft ? isLShooting : isRShooting) = true;
			++(isLeft ? Data::LPlayer : Data::RPlayer).mainSkillCnt;
			chargeSound = Sound(L"/9020");
			laserSound = Sound(L"/9021");
			chargeSound.setLoop(true);
			laserSound.setLoop(true);
			chargeSound.play();
		}
	}
	~Laser() override {
		if (!(isLeft ? isLInvalid : isRInvalid))
			(isLeft ? isLShooting : isRShooting) = false;
		laserSound.stop(1s);
	};

	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;

	const static int bulletSpeed = 10;
};

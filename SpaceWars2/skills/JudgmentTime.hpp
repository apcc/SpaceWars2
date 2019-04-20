#pragma once
#include <Siv3d.hpp>
#include "Bullet.hpp"
#include "../CommonData.hpp"

#define PLAYER (!isLeft ? Data::LPlayer : Data::RPlayer)

class JudgmentTime : public Bullet {
private:
	int lifeTime = 1;
public:
	JudgmentTime(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		PLAYER.changeSpeed(0);
	}
	~JudgmentTime(){
		PLAYER.changeSpeed(15);
	}
	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
};

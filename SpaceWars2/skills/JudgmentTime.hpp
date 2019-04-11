#pragma once
#include <Siv3d.hpp>
#include "Bullet.hpp"
#include "../CommonData.hpp"

class JudgmentTime : public Bullet {
private:
	int lifeTime = 180;
	Circle getShape() { return Circle(pos, 30+lifeTime); }
public:
	JudgmentTime(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		(!isLeft ? Data::LPlayer : Data::RPlayer).changeSpeed(0);
	}
	~JudgmentTime(){
		(!isLeft ? Data::LPlayer : Data::RPlayer).changeSpeed(15);
	}
	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
};

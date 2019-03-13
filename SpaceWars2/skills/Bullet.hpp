#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

class Bullet {
protected:
	Vec2 pos, vel = {};
	bool shouldBeDestroyed = false;
public:
	Bullet():
		pos(Vec2(0, 0)),
		isLeft(true) {};
	Bullet(Vec2 _pos, bool _isLeft) :
		pos(_pos),
		isLeft(_isLeft) {};
	virtual ~Bullet() = default;

	virtual bool update(Vec2 _myPos, Vec2 _oppPos) = 0;
	virtual void draw() = 0;
	virtual bool isInvisible() = 0;
	virtual int getDamage(Circle _circle) = 0;

	bool isLeft;
};

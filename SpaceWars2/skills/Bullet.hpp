#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

class Bullet {
protected:
	Vec2 pos, vel = {};
	bool shouldBeDestroyed = false;
	RectF activeField = RectF(0, 0, Config::WIDTH, Config::HEIGHT);
	double shrinkRate = 1;
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
	virtual bool isVisible() = 0;
	virtual int getDamage(Circle _circle) = 0;

	Vec2 getPos() {
		return pos;
	}

	Vec2 Shrink(Rect _area) {
		if (_area.w * 9 != _area.h * 16) {
			LOG_ERROR(L"縮小に失敗しました;引数は縦横比が9:16のVec2でなくてはなりません");
		}
		shrinkRate = (double)_area.w / activeField.w;
		Vec2 distance = pos.asPoint() - activeField.center;
		pos = distance * shrinkRate + _area.center;
		vel *= shrinkRate;
		activeField = _area;
		return pos;
	}

	bool isLeft;
};

#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

class Bullet {
protected:
	Vec2 pos,vel;
public:
	Bullet():pos(Vec2(0,0)),isLeft(false){};
	Bullet(Vec2 pos, bool isLeft):
		pos(pos),
		isLeft(isLeft){}
	// Bullet(int32 x, int32 y, bool isLeft){};

	virtual bool update() = 0;
	virtual void draw() = 0;
	virtual bool isInvisible() = 0;
	virtual bool intersects(Circle circle) = 0;
	virtual int getDamage() = 0;

	bool isLeft;
};

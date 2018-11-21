#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

class Bullet {
public:
	Bullet(){};
	// Bullet(int32 x, int32 y, bool isLeft){};

	Vec2 pos,vel;

	virtual int update(Circle rivalCircle){ (void)(rivalCircle);/*WarningC4100対策*/ return 0; };
	virtual void draw(){};
};

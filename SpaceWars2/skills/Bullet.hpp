#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

class Bullet {
public:
	Bullet(){};
	// Bullet(int32 x, int32 y, bool isLeft){};

	Vec2 pos,vel;

	virtual void update(){};
	virtual void draw(){};
};

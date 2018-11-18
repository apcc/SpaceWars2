#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

class Bullet {
public:
	Bullet();
	Bullet(int32 x, int32 y, bool isLeft);

	int32 posX;
	int32 posY;
	int32 vx;
	int32 vy;
	bool active;

	const int bulletSpeed = 3;

	const static int bulletSpeed;
};

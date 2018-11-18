#pragma once
#include "./Bullet.hpp"

Bullet::Bullet(){
	Bullet(0,0,0);
}

Bullet::Bullet(int32 x, int32 y, bool isLeft){
	posX = x;
	posY = y;
	double direction = Radians(10 * Random(-2, 2));
	vx = bulletSpeed * cos(direction) * (isLeft?1:-1);
	vy = bulletSpeed * sin(direction);
	active = true;
}

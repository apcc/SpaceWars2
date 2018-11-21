#pragma once
#include <Siv3D.hpp>
#include "./Bullet.hpp"

class Shot : public Bullet {
	public:
	Shot(){};
	Shot(Vec2 pos, bool isLeft);

	int update(Circle rivalPlayer);
	void draw();

	const static int bulletSpeed = 10;
	const static int damage = 2;
};

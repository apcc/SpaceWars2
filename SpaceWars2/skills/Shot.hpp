#pragma once
#include <Siv3D.hpp>
#include "./Bullet.hpp"

class Shot : public Bullet {
	public:
	Shot(){};
	Shot(Vec2 pos, bool isLeft);

	void update();
	void draw();

	const static int bulletSpeed = 10;
	const static int damage = 2;
};

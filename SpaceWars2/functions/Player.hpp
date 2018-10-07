#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

class Player {
	public:
	int32 posX;
	int32 posY;
	bool isLeft;
	Circle ship;

	void Init(int32, int32, bool);
	void Control();
};

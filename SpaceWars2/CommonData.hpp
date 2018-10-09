#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"

#include "./functions/Player.hpp"

typedef struct {
	int count = 0;
	Texture background = Texture(L"images/background.png");
	Player LPlayer;
	Player RPlayer;
} CommonData;

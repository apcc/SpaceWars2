#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"

#include "./functions/Player.hpp"

typedef struct {
	Texture background = Texture(L"images/background.png");
	Font CicaR32 = Font(32, L"Cica");
	Player LPlayer;
	Player RPlayer;
} CommonData;
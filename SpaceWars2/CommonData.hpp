#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"

#include "./functions/Player.hpp"
#include "./functions/Debug.hpp"


struct CommonData {
	Player LPlayer;
	Player RPlayer;
	Debug debug;
};

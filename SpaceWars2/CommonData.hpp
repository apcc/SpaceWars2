#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"

#include "./functions/Player.hpp"


struct CommonData {
	// Player LPlayer;
	// Player RPlayer;
};

namespace Data {
	extern Player LPlayer;
	extern Player RPlayer;
};

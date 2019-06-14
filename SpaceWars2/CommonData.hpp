#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"

#include "./functions/Player.hpp"
#include "./functions/KeyRepeat.hpp"


struct CommonData {
	// Player LPlayer;
	// Player RPlayer;
};

namespace Data {
	extern Player LPlayer;
	extern Player RPlayer;

	extern KeyRepeat KeyEnter;
	extern KeyRepeat KeyBack;
	extern KeyRepeat LKeyBack;
	extern KeyRepeat RKeyBack;
	extern KeyRepeat LKeySelect;
	extern KeyRepeat RKeySelect;
	extern KeyRepeat LKeyCancel;
	extern KeyRepeat RKeyCancel;
	extern KeyRepeat KeyUp;
	extern KeyRepeat KeyLeft;
	extern KeyRepeat KeyDown;
	extern KeyRepeat KeyRight;
	extern KeyRepeat KeySelectUp;
	extern KeyRepeat KeySelectDown;
}

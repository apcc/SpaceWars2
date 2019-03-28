#include "KeyRepeat.hpp"
#include "../Scenes/Game.hpp"
// default constructor
KeyRepeat::KeyRepeat() {
	name = L"";
	isAxis = false;
	isClicked = false;
	pressTime = 0;
	border = 0;
}

// Button Constructor
KeyRepeat::KeyRepeat(bool _isLeft, const String& _name) {
	name = (_isLeft ? L"L_" : L"R_") + _name;
	isAxis = false;
	isClicked = false;
	pressTime = 0;
	border = 0;
}

// Axis Constructor
KeyRepeat::KeyRepeat(bool _isLeft, const String& _name, int _border) {
	name = (_isLeft ? L"L_" : L"R_") + _name;
	isAxis = true;
	isClicked = false;
	pressTime = 0;
	border = _border;
}

bool KeyRepeat::repeat(int _time) {
	if (!isClicked && GamePad::input.button(name).pressed) {
		// clicked
		isClicked = true;
		return true;
	} else if (GamePad::input.button(name).pressed) {
		// pressed
		if (pressTime >= _time) {
			pressTime = 0;
			isClicked = false;
		}
	} else {
		// released
		pressTime = 0;
		isClicked = false;
	}
	++pressTime;

	return false;
}

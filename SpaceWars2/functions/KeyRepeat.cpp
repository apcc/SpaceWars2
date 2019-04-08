#include "KeyRepeat.hpp"
#include "./XInput.hpp"

// default constructor
KeyRepeat::KeyRepeat() {
	name = L"";
	isLeft = true;
	isClicked = false;
	time = 0;
	border = 0;
}

// Abnormal Button Constructor (ex. Enter etc...)
KeyRepeat::KeyRepeat(const String& _name) {
	name = _name;
	isLeft = -1;
	isClicked = false;
	time = 0;
	border = 0;
}

// Button Constructor
KeyRepeat::KeyRepeat(bool _isLeft, const String& _name) {
	name = _name;
	isLeft = (int)_isLeft;
	isClicked = false;
	time = 0;
	border = 0;
}

bool KeyRepeat::repeat(int _time, bool _clickBarrage /* = true */) {
	++time;

	if(isLeft == -1) {
		if (!isClicked && GamePad::Key(name)) {
			// clicked
			if (_clickBarrage ? time >= _time : true) {
				// valid
				isClicked = true;
				time = 0;
				return true;
			}
		}
		else if (GamePad::Key(name)) {
			// pressed
			if (time >= _time) {
				// valid
				time = 0;
				// isClicked = false;
				return true;
			}
		}
		else {
			// released
			isClicked = false;
		}
	}
	else {
		if (!isClicked && GamePad::Key(!!isLeft, name)) {
			Println(L"clicked");
			// clicked
			if (_clickBarrage ? time >= _time : true) {
				Println(L"clicked->valid");
				// valid
				isClicked = true;
				time = 0;
				return true;
			}
		}
		else if (GamePad::Key(!!isLeft, name)) {
			Println(L"pressed");
			// pressed
			if (time >= _time) {
				Println(L"pressed->valid");
				// valid
				time = 0;
				// isClicked = false;
				return true;
			}
		}
		else {
			// released
			isClicked = false;
		}
	}
	
	return false;
}

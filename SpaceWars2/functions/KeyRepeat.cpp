#include "KeyRepeat.hpp"
#include "./XInput.hpp"

// default constructor
KeyRepeat::KeyRepeat() {
	name = L"";
	isLeft = true;
	isClicked = false;
	pressTime = 0;
	border = 0;
}

// Abnormal Button Constructor (ex. Enter etc...)
KeyRepeat::KeyRepeat(const String& _name) {
	name = _name;
	isLeft = 3;
	isClicked = false;
	pressTime = 0;
	border = 0;
}

// Button Constructor
KeyRepeat::KeyRepeat(bool _isLeft, const String& _name) {
	name = _name;
	isLeft = (int)_isLeft;
	isClicked = false;
	pressTime = 0;
	border = 0;
}

bool KeyRepeat::repeat(int _time) {
	if(isLeft == 3) {
		if (!isClicked && GamePad::Key(name)) {
			// clicked
			isClicked = true;
			return true;
		}
		else if (GamePad::Key(name)) {
			// pressed
			if (pressTime >= _time) {
				pressTime = 0;
				isClicked = false;
			}
		}
		else {
			// released
			pressTime = 0;
			isClicked = false;
		}
	}else{	
		if (!isClicked && GamePad::Key(!!isLeft, name)) {
			// clicked
			isClicked = true;
			return true;
		}
		else if (GamePad::Key(!!isLeft, name)) {
			// pressed
			if (pressTime >= _time) {
				pressTime = 0;
				isClicked = false;
			}
		}
		else {
			// released
			pressTime = 0;
			isClicked = false;
		}
	} 
	++pressTime;

	return false;
}

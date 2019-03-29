#pragma once
#include <Siv3D.hpp>
#include "./XInput.hpp"


class KeyRepeat {
private:
	String name;
	bool isLeft;
	bool isAxis;
	bool isClicked;
	int pressTime;
	int border;

public:
	KeyRepeat(); // default constructor
	KeyRepeat(bool _isLeft, const String& _name);				// Button Constructor
	KeyRepeat(bool _isLeft, const String& _name, int _border);	// Axis Constructor

	bool repeat(int _time);
};

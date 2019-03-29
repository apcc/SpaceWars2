#pragma once
#include <Siv3D.hpp>

class KeyRepeat {
private:
	String name;
	bool isLeft;
	bool isClicked;
	int pressTime;
	int border;

public:
	KeyRepeat();
	KeyRepeat(bool _isLeft, const String& _name);

	bool repeat(int _time);
};

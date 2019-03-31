#pragma once
#include <Siv3D.hpp>

class KeyRepeat {
private:
	String name;
	int isLeft; // 0:Right 1:Left -1:Undefined
	bool isClicked;
	int pressTime;
	int border;

public:
	KeyRepeat();
	KeyRepeat(const String& _name);
	KeyRepeat(bool _isLeft, const String& _name);

	bool repeat(int _time);
};

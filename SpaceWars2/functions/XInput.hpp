#pragma once
#include "../asc/Input.hpp"


namespace GamePad {
	extern asc::Input input;

	extern XInput LGamePad;
	extern XInput RGamePad;

	extern void SetAxis();
	extern void SetButton();

	extern Vec2 Move(bool _isLeft, int _speed);
	extern bool Skill(bool _isLeft, const String& _name);

	extern bool KeyUp(bool _isLeft);
	extern bool KeyDown(bool _isLeft);
	extern bool KeyLeft(bool _isLeft);
	extern bool KeyRight(bool _isLeft);
}

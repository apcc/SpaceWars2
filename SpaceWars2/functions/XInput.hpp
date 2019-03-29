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

	extern bool Key(bool _isLeft, const String& _name);
}

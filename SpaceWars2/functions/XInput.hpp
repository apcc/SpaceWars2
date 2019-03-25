#pragma once
#include "../asc/Input.hpp"


namespace Controller {
	extern asc::Input input;

	extern XInput LController;
	extern XInput RController;

	extern void SetAxis();
	extern void SetButton();

	extern Vec2 Move(bool _isLeft, int _speed);
	extern bool Skill(bool _isLeft, const String& _name);
}

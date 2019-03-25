#pragma once
#include "../asc/Input.hpp"


namespace Controller {
	extern asc::Input input;

	extern XInput LController;
	extern XInput RController;

	extern void SetAxis();
	extern void SetButton();

	extern Vec2 Ctrl(bool _isLeft, int _speed);
	extern bool Skill(bool _isLeft, String _name);
}

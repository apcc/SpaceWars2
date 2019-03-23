#include "XInput.hpp"

#define BORDER 0.5

using asc::XInput;


asc::Input Controller::input = asc::Input();

XInput Controller::LController = XInput(0);
XInput Controller::RController = XInput(1);


void Controller::SetAxis() {
	// Left
	input.addAxis(L"L_CtrlX", asc::Axis(Input::KeyD, Input::KeyA) | asc::Axis(asc::Axis(LController, asc::XInputAxis::LeftThumbX)));
	input.addAxis(L"L_CtrlY", asc::Axis(Input::KeyW, Input::KeyS) | asc::Axis(asc::Axis(LController, asc::XInputAxis::LeftThumbY)));

	// Right
	input.addAxis(L"R_CtrlX", asc::Axis(Input::KeySemicolon, Input::KeyK) | asc::Axis(asc::Axis(RController, asc::XInputAxis::LeftThumbX)));
	input.addAxis(L"R_CtrlY", asc::Axis(Input::KeyO, Input::KeyL) | asc::Axis(asc::Axis(RController, asc::XInputAxis::LeftThumbY)));
}

Vec2 Controller::Ctrl(bool _isLeft, int _speed) {
	String lr = (_isLeft ? L"L" : L"R");
	Vec2 raw = {};

	if (fabs(input.axis(lr + L"_CtrlX")) > BORDER)
		raw.x = input.axis(lr + L"_CtrlX") * _speed;

	if (fabs(input.axis(lr + L"_CtrlY")) > BORDER)
		raw.y = input.axis(lr + L"_CtrlY") * _speed * -1;

	return raw;
}


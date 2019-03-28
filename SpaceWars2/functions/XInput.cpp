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

void Controller::SetButton() {
	// MainSkill
	input.addButton(L"L_MainSkill", s3d::Input::KeyQ | XInput(0).buttonA);
	input.addButton(L"R_MainSkill", s3d::Input::KeyI | XInput(1).buttonA);

	// SubSkill
	input.addButton(L"L_SubSkill", s3d::Input::KeyE | XInput(0).buttonLB);
	input.addButton(L"R_SubSkill", s3d::Input::KeyP | XInput(1).buttonLB);

	// SpecialSkill
	input.addButton(L"L_SpecialSkill", s3d::Input::KeyLShift | XInput(0).buttonRB);
	input.addButton(L"R_SpecialSkill", s3d::Input::KeyRShift | XInput(1).buttonRB);

	// WASD
	input.addButton(L"L_KeyUp" ,   s3d::Input::KeyW | XInput(0).buttonUp);
	input.addButton(L"L_KeyLeft",  s3d::Input::KeyA | XInput(0).buttonLeft);
	input.addButton(L"L_KeyDown",  s3d::Input::KeyS | XInput(0).buttonDown);
	input.addButton(L"L_KeyRight", s3d::Input::KeyD | XInput(0).buttonRight);

	// OKL;
	input.addButton(L"R_KeyUp",    s3d::Input::KeyO | XInput(1).buttonUp);
	input.addButton(L"R_KeyLeft",  s3d::Input::KeyK | XInput(1).buttonLeft);
	input.addButton(L"R_KeyDown",  s3d::Input::KeyL | XInput(1).buttonDown);
	input.addButton(L"R_KeyRight", s3d::Input::KeySemicolon | XInput(1).buttonRight);
}


Vec2 Controller::Move(bool _isLeft, int _speed) {
	String lr = (_isLeft ? L"L" : L"R");
	Vec2 raw = {};

	if (fabs(input.axis(lr + L"_CtrlX")) > BORDER)
		raw.x = input.axis(lr + L"_CtrlX") * _speed;

	if (fabs(input.axis(lr + L"_CtrlY")) > BORDER)
		raw.y = input.axis(lr + L"_CtrlY") * _speed * -1;

	return raw;
}

/// <summary>
/// 指定されたボタンが押されているか調べます。
/// </summary>
/// <param name="_isLeft">
/// LPlayer or RPlayer
/// </param>
/// <param name="_name">
/// MainSkill, SubSkill, SpecialSkill のいずれか
/// </param>
/// <returns>
/// _name に対応するボタンが押されている場合は true, それ以外の場合は false
/// </returns>
bool Controller::Skill(bool _isLeft, const String& _name) {
	String lr = (_isLeft ? L"L" : L"R");

	// if (_name.includes(L"MainSkill" || L"SubSkill" || L"SpecialSkill"))
		return input.button(lr + L"_" + _name).pressed;

	return false;
}

bool Controller::KeyUp(bool _isLeft) {
	String lr = (_isLeft ? L"L" : L"R");
	return input.button(lr + L"_KeyUp").pressed || input.axis(lr + L"_CtrlY") > 0.8;
}

bool Controller::KeyLeft(bool _isLeft) {
	String lr = (_isLeft ? L"L" : L"R");
	return input.button(lr + L"_KeyLeft").pressed || input.axis(lr + L"_CtrlX") < -0.8;
}

bool Controller::KeyDown(bool _isLeft) {
	String lr = (_isLeft ? L"L" : L"R");
	return input.button(lr + L"_KeyDown").pressed || input.axis(lr + L"_CtrlY") < -0.8;
}

bool Controller::KeyRight(bool _isLeft) {
	String lr = (_isLeft ? L"L" : L"R");
	return input.button(lr + L"_KeyRight").pressed || input.axis(lr + L"_CtrlX") > 0.8;
}

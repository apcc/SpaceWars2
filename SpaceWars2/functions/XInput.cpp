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
/// �w�肳�ꂽ�{�^����������Ă��邩���ׂ܂��B
/// </summary>
/// <param name="_isLeft">
/// LPlayer or RPlayer
/// </param>
/// <param name="_name">
/// MainSkill, SubSkill, SpecialSkill �̂����ꂩ
/// </param>
/// <returns>
/// _name �ɑΉ�����{�^����������Ă���ꍇ�� true, ����ȊO�̏ꍇ�� false
/// </returns>
bool Controller::Skill(bool _isLeft, String _name) {
	String lr = (_isLeft ? L"L" : L"R");

	// if (_name.includes(L"MainSkill" || L"SubSkill" || L"SpecialSkill"))
		return input.button(lr + L"_" + _name).pressed;

	return false;
}

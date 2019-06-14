#include "XInput.hpp"

#define BORDER 0.1

using asc::XInput;


asc::Input GamePad::input = asc::Input();

bool GamePad::isErrorCalled = false;
MessageBoxCommand GamePad::com = MessageBoxCommand::No;

XInput GamePad::LGamePad = XInput(0);
XInput GamePad::RGamePad = XInput(1);


void GamePad::SetAxis() {
	LGamePad.setLeftThumbDeadZone();
	LGamePad.setRightThumbDeadZone();
	RGamePad.setLeftThumbDeadZone();
	RGamePad.setRightThumbDeadZone();

	// Left
	input.addAxis(L"L_CtrlX",
		asc::Axis(Input::KeyD, Input::KeyA) 
		| asc::Axis(asc::Axis(LGamePad, asc::XInputAxis::LeftThumbX)) 
		| asc::Axis(asc::Axis(LGamePad, asc::XInputAxis::RightThumbX))
	);
	input.addAxis(L"L_CtrlY", 
		asc::Axis(Input::KeyW, Input::KeyS) 
		| asc::Axis(asc::Axis(LGamePad, asc::XInputAxis::LeftThumbY)) 
		| asc::Axis(asc::Axis(LGamePad, asc::XInputAxis::RightThumbY))
	);

	// Right
	input.addAxis(L"R_CtrlX", 
		asc::Axis(Input::KeySemicolon, Input::KeyK)
		| asc::Axis(Input::KeyRight, Input::KeyLeft)
		| asc::Axis(asc::Axis(RGamePad, asc::XInputAxis::LeftThumbX)) 
		| asc::Axis(asc::Axis(RGamePad, asc::XInputAxis::RightThumbX))
	);
	input.addAxis(L"R_CtrlY", 
		asc::Axis(Input::KeyO, Input::KeyL)
		| asc::Axis(Input::KeyUp, Input::KeyDown)
		| asc::Axis(asc::Axis(RGamePad, asc::XInputAxis::LeftThumbY)) 
		| asc::Axis(asc::Axis(RGamePad, asc::XInputAxis::RightThumbY))
	);
}

void GamePad::SetButton() {
	// MainSkill
	input.addButton(L"L_MainSkill", s3d::Input::KeyQ | XInput(0).buttonB);
	input.addButton(L"R_MainSkill", s3d::Input::KeyI | s3d::Input::KeySlash | XInput(1).buttonB);

	// SubSkill
	input.addButton(L"L_SubSkill", s3d::Input::KeyE | XInput(0).buttonLB);
	input.addButton(L"R_SubSkill", s3d::Input::KeyP | s3d::Input::KeyBackslash | XInput(1).buttonLB);

	// SpecialSkill
	input.addButton(L"L_SpecialSkill", s3d::Input::KeyLShift | XInput(0).buttonRB);
	input.addButton(L"R_SpecialSkill", s3d::Input::KeyRShift | XInput(1).buttonRB);

	// WASD
	input.addButton(L"L_KeyUp" ,   s3d::Input::KeyW | XInput(0).buttonUp);
	input.addButton(L"L_KeyLeft",  s3d::Input::KeyA | XInput(0).buttonLeft);
	input.addButton(L"L_KeyDown",  s3d::Input::KeyS | XInput(0).buttonDown);
	input.addButton(L"L_KeyRight", s3d::Input::KeyD | XInput(0).buttonRight);

	// OKL;
	input.addButton(L"R_KeyUp",    s3d::Input::KeyO | s3d::Input::KeyUp | XInput(1).buttonUp);
	input.addButton(L"R_KeyLeft",  s3d::Input::KeyK | s3d::Input::KeyLeft | XInput(1).buttonLeft);
	input.addButton(L"R_KeyDown",  s3d::Input::KeyL | s3d::Input::KeyDown | XInput(1).buttonDown);
	input.addButton(L"R_KeyRight", s3d::Input::KeySemicolon | s3d::Input::KeyRight | XInput(1).buttonRight);

	// SkillSelect
	input.addButton(L"KeySelectUp",   s3d::Input::KeyW | s3d::Input::KeyO | s3d::Input::KeyUp);
	input.addButton(L"KeySelectDown", s3d::Input::KeyS | s3d::Input::KeyL | s3d::Input::KeyDown);

	// 操作
	input.addButton(L"KeyEnter",    s3d::Input::KeyEnter    | s3d::Input::KeyEnter);
	input.addButton(L"L_KeyBack",   s3d::Input::KeyLControl | s3d::Input::KeyBackspace);
	input.addButton(L"R_KeyBack",   s3d::Input::KeyRControl | s3d::Input::KeyBackspace);
	input.addButton(L"L_KeySelect", s3d::Input::KeyLShift   | XInput(0).buttonA);
	input.addButton(L"R_KeySelect", s3d::Input::KeyRShift   | XInput(1).buttonA);
	input.addButton(L"L_KeyCancel", s3d::Input::KeyLControl | s3d::Input::KeyEnd | XInput(0).buttonB);
	input.addButton(L"R_KeyCancel", s3d::Input::KeyRControl | s3d::Input::KeyEnd | XInput(1).buttonB);
}


Vec2 GamePad::Move(bool _isLeft, int _speed) {
	String lr = (_isLeft ? L"L" : L"R");
	Vec2 raw = {};

	if (fabs(input.axis(lr + L"_CtrlX")) > BORDER) {
		raw.x = input.axis(lr + L"_CtrlX") * (double)_speed;
	}

	if (fabs(input.axis(lr + L"_CtrlY")) > BORDER) {
		raw.y = input.axis(lr + L"_CtrlY") * (double)_speed * -1.0;
	}
	return raw;
}

bool GamePad::Key(bool _isLeft, const String& _name) {
	String lr = (_isLeft ? L"L" : L"R");

	if (!input.hasButton(lr + L"_" + _name)) {
		LOG_ERROR(L"GamePad::Key() で指定された ", _name, L" は存在しません。");
		if (!isErrorCalled) {
			com = MessageBox::Show(L"Fatal Error", L"GamePad::Key() で存在しない名前が指定されました。\n終了します。詳細はlog.htmlを参照してください。", MessageBoxStyle::Ok, 0);
			isErrorCalled = true;
		}
		if (com == MessageBoxCommand::Ok)
			System::Exit();
		return false;
	}

	if (_name == L"KeyUp")
		return input.button(lr + L"_KeyUp").pressed || input.axis(lr + L"_CtrlY") > 0.8;

	if (_name == L"KeyLeft")
		return input.button(lr + L"_KeyLeft").pressed || input.axis(lr + L"_CtrlX") < -0.8;

	if (_name == L"KeyDown")
		return input.button(lr + L"_KeyDown").pressed || input.axis(lr + L"_CtrlY") < -0.8;

	if(_name == L"KeyRight")
		return input.button(lr + L"_KeyRight").pressed || input.axis(lr + L"_CtrlX") > 0.8;

	if (_name == L"KeyCancel")
		return input.button(lr + L"_KeyCancel").pressed 
			|| XInput((int)!_isLeft). leftTrigger > 0.5 
			|| XInput((int)!_isLeft).rightTrigger > 0.5 
			|| s3d::Input::KeyBackspace.pressed;

	return input.button(lr + L"_" + _name).pressed;
}

bool GamePad::Key(const String& _name) {
	if (input.hasButton(_name))
		return input.button(_name).pressed;

	if (_name == L"KeyUp")
		return input.button(L"L_KeyUp").pressed || input.button(L"R_KeyUp").pressed || input.axis(L"L_CtrlY") > 0.8 || input.axis(L"R_CtrlY") > 0.8;

	if (_name == L"KeyLeft")
		return input.button(L"L_KeyLeft").pressed || input.button(L"R_KeyLeft").pressed || input.axis(L"L_CtrlX") < -0.8 || input.axis(L"R_CtrlX") < -0.8;

	if (_name == L"KeyDown")
		return input.button(L"L_KeyDown").pressed || input.button(L"R_KeyDown").pressed || input.axis(L"L_CtrlY") < -0.8 || input.axis(L"R_CtrlY") < -0.8;

	if (_name == L"KeyRight")
		return input.button(L"L_KeyBack").pressed || input.button(L"R_KeyBack").pressed || input.axis(L"L_CtrlX") > 0.8 || input.axis(L"R_CtrlX") > 0.8;

	if (_name == L"KeyCancel")
		return input.button(L"L_KeyCancel").pressed || input.button(L"R_KeyCancel").pressed || XInput(0).leftTrigger > 0.5 || XInput(0).rightTrigger > 0.5 || XInput(0).leftTrigger > 0.5 || XInput(0).rightTrigger > 0.5;

	if (input.hasButton(L"L_" + _name) && input.hasButton(L"R_" + _name))
		return input.button(L"L_" + _name).pressed || input.button(L"R_" + _name).pressed;
	
	LOG_ERROR(L"GamePad::Key() で指定された ", _name, L" は存在しません。");
	if (!isErrorCalled) {
		com = MessageBox::Show(L"Fatal Error", L"GamePad::Key() で存在しない名前が指定されました。\n終了します。詳細はlog.htmlを参照してください。", MessageBoxStyle::Ok, 0);
		isErrorCalled = true;
	}
	if (com == MessageBoxCommand::Ok)
		System::Exit();
	return false;
}

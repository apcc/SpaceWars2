#include "ControlGuidance.hpp"

void ControlGuidance::init() {

}

void ControlGuidance::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"ScreenGuidance", 500);
}

void ControlGuidance::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.5));

	Line({ 25, 18 }, { 225, 18 }).draw(5);
	SmartUI::Get(S32)(L"操作方法").draw({ 30, 20 });
	Line({ 25, 82 }, { 225, 82 }).draw(5);


	constexpr int cY = 400; //Y軸の基準(center)

	TextureAsset(L"controller").drawAt(Window::Center().x, cY);

	// stick
	drawPointLine({ 539, cY + 72 }, { 265, cY + 72 });
	TextureAsset(L"stick_64").drawAt(225, cY + 72);
	rightCAlign(SmartUI::Get(S28), L"移動", 175, cY + 72);
	// A
	drawPointLine({ 830, cY + 13 }, { 1015, cY + 72 }, Color(L"#afa"));
	TextureAsset(L"buttonA_64").drawAt(1055, cY + 72);
	leftCAlign(SmartUI::Get(S28), L"決定", 1105, cY + 72);
	// B
	drawPointLine({ 880, cY - 37 }, { 1015, cY - 37 }, Color(L"#faa"));
	TextureAsset(L"buttonB_64").drawAt(1055, cY - 37);
	Line({ 1100, cY - 12 }, { 1210, cY - 12 }).draw(10, Color(L"#7CFC00"));
	leftCAlign(SmartUI::Get(S28), L"main", 1105, cY - 37);
	// LB
	drawPointLine({ 435, cY - 190 }, { 265, cY - 190 });
	TextureAsset(L"buttonLB_64").drawAt( 225, cY - 190);
	Line({ 95, cY - 165 }, { 180, cY - 165 }).draw(10, Color(L"#4169E1"));
	rightCAlign(SmartUI::Get(S28), L"sub", 175, cY - 190);
	// RB
	drawPointLine({ 845, cY - 190 }, { 965, cY - 190 });
	TextureAsset(L"buttonRB_64").drawAt(1005, cY - 190);
	Line({ 1050, cY - 165 }, { 1210, cY - 165 }).draw(10, Color(L"#FFD000"));
	leftCAlign(SmartUI::Get(S28), L"special", 1055, cY - 190);

	// 右下操作方法表示
	Vec2 buttonPos(1190, 692);
	buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos).w + 6;
	buttonPos.x += (int)CicaR::Get(C12)(L"次へ").draw(buttonPos).w + 15;
}


void ControlGuidance::drawPointLine(Vec2 _root, Vec2 _pos, Color _color) {
	int isLeft = 0; // -1:left 0:center 1:right
	int xSlope = 0;
	if (_pos.x > _root.x) isLeft = -1;
	if (_pos.x < _root.x) isLeft = 1;
	if (_pos.y > _root.y) xSlope = -1;
	if (_pos.y < _root.y) xSlope = 1;
	double move = _pos.y - _root.y;

	Circle(_root, 6).draw(_color);
	LineString({ _root, _root.movedBy(move * isLeft * xSlope, move), _pos }).draw(5, _color);
}

template <typename T>
void ControlGuidance::rightCAlign(Font _font, T _text, int _x, int _y, Color _color) {
	_font(_text).drawAt(_x - (int)_font(_text).region().w / 2, _y, _color);	
}

template <typename T>
void ControlGuidance::leftCAlign(Font _font, T _text, int _x, int _y, Color _color) {
	_font(_text).drawAt(_x + (int)_font(_text).region().w / 2, _y, _color);
}

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

	constexpr int cY = 400; //Y軸の基準(center)

	TextureAsset(L"controller").drawAt(Window::Center().x, cY);

	drawPointLine({ 539, cY + 72 }, {  265, cY + 72 }); // stick
	drawPointLine({ 830, cY + 13 }, { 1015, cY + 72 }, Color(L"#afa")); // A
	drawPointLine({ 880, cY - 37 }, { 1015, cY - 37 }, Color(L"#faa")); // B

	drawPointLine({435, cY - 190}, { 265, cY - 190}); // LB
	drawPointLine({845, cY - 190}, {1015, cY - 190}); // RB

	TextureAsset(L"stick_64").drawAt(225, cY + 75);
	rightCAlign(SmartUI::GetFont(S28), L"移動", 175, cY + 75);
	TextureAsset(L"buttonA_64").drawAt(1055, cY + 75);
	leftCAlign(SmartUI::GetFont(S28), L"決定", 1105, cY + 75);
	TextureAsset(L"buttonB_64").drawAt(1055, cY - 35);
	Line({ 1100, cY - 10 }, { 1215, cY - 10 }).draw(10, Color(L"#7CFC00"));
	leftCAlign(SmartUI::GetFont(S28), L"main", 1105, cY - 35);

	TextureAsset(L"buttonLB_64").drawAt( 225, cY - 190);
	Line({ 90, cY - 165 }, { 180, cY - 165 }).draw(10, Color(L"#4169E1"));
	rightCAlign(SmartUI::GetFont(S28), L"sub", 175, cY - 190);
	TextureAsset(L"buttonRB_64").drawAt(1055, cY - 190);
	Line({ 1100, cY - 165 }, { 1260, cY - 165 }).draw(10, Color(L"#FFD000"));
	leftCAlign(SmartUI::GetFont(S28), L"special", 1105, cY - 190);
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
	_font(_text).drawAt(_x - _font(_text).region().w / 2, _y, _color);	
}

template <typename T>
void ControlGuidance::leftCAlign(Font _font, T _text, int _x, int _y, Color _color) {
	_font(_text).drawAt(_x + _font(_text).region().w / 2, _y, _color);
}

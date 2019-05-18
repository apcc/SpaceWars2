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

	constexpr int cY = 400; //Y軸の基準(center)

	TextureAsset(L"controller").drawAt(Window::Center().x, cY);

	drawPointLine({ 539, cY + 72 }, {  265, cY + 72 }); // stick
	drawPointLine({ 445, cY - 40 }, {  265, cY - 40 }); // cross
	drawPointLine({ 830, cY + 13 }, { 1015, cY + 72 }, Color(L"#afa")); // A
	drawPointLine({ 880, cY - 37 }, { 1015, cY - 37 }, Color(L"#faa")); // B

	drawPointLine({420, cY - 190}, { 265, cY - 190}); // LT
	drawPointLine({455, cY - 190}, { 265, cY - 265}); // LB
	drawPointLine({860, cY - 190}, {1015, cY - 190}); // RT
	drawPointLine({825, cY - 190}, {1015, cY - 265}); // RB

	TextureAsset(L"stick_64").drawAt(225, cY + 75);
	rightCAlign(SmartUI::GetFont(S28), L"移動", 175, cY + 75);
	TextureAsset(L"cross_64").drawAt(225, cY - 40);
	rightCAlign(SmartUI::GetFont(S28), L"選択", 175, cY - 40);
	TextureAsset(L"buttonA_64").drawAt(1055, cY + 75);
	leftCAlign(SmartUI::GetFont(S28), L"決定", 1105, cY + 75);
	TextureAsset(L"buttonB_64").drawAt(1055, cY - 35);
	leftCAlign(SmartUI::GetFont(S28), L"main", 1105, cY - 35);

	TextureAsset(L"buttonLT_64").drawAt( 225, cY - 190);
	rightCAlign(SmartUI::GetFont(S28), L"Cancel", 175, cY - 190);
	TextureAsset(L"buttonLB_64").drawAt( 225, cY - 265);
	rightCAlign(SmartUI::GetFont(S28), L"sub", 175, cY - 265);
	TextureAsset(L"buttonRT_64").drawAt(1055, cY - 190);
	leftCAlign(SmartUI::GetFont(S28), L"Cancel", 1105, cY - 190);
	TextureAsset(L"buttonRB_64").drawAt(1055, cY - 265);
	leftCAlign(SmartUI::GetFont(S28), L"special", 1105, cY - 265);
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

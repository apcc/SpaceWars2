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

	drawPointLine({ 540, cY + 75 }, {  265, cY + 75 });
	drawPointLine({ 445, cY - 40 }, {  265, cY - 40 });
	drawPointLine({ 830, cY + 15 }, { 1015, cY + 15 }, Color(L"#afa"));
	drawPointLine({ 880, cY - 35 }, { 1015, cY - 35 }, Color(L"#faa"));

	drawPointLine({435, cY - 190}, { 265, cY - 225});
	drawPointLine({450, cY - 195}, { 265, cY - 260});
	drawPointLine({845, cY - 190}, {1015, cY - 225});
	drawPointLine({830, cY - 195}, {1015, cY - 260});

	TextureAsset(L"stick_64").drawAt(225, cY + 75);
	TextureAsset(L"cross_64").drawAt(225, cY - 40);
	TextureAsset(L"buttonA_64").drawAt(1055, cY + 15);
	TextureAsset(L"buttonB_64").drawAt(1055, cY - 35);

	TextureAsset(L"buttonLB_64").drawAt( 225, cY - 225);
	TextureAsset(L"buttonLT_64").drawAt( 225, cY - 260);
	TextureAsset(L"buttonRB_64").drawAt(1055, cY - 225);
	TextureAsset(L"buttonRT_64").drawAt(1055, cY - 260);
}


void ControlGuidance::drawPointLine(Vec2 _root, Vec2 _pos, Color _color) {
	int isLeft = 0; // -1:left 0:center 1:right
	if (_pos.x > _root.x) isLeft = -1;
	if (_pos.x < _root.x) isLeft = 1;
	double move = _pos.y - _root.y;

	Circle(_root, 6).draw(_color);
	LineString({ _root, _root.movedBy(move * isLeft, move), _pos }).draw(5, _color);
}

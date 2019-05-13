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

	drawPointLineString(LineString({ {435, cY - 190}, {400, cY - 225}, { 265, cY - 225} }));
	drawPointLineString(LineString({ {450, cY - 195}, {385, cY - 260}, { 265, cY - 260} }));
	drawPointLineString(LineString({ {845, cY - 190}, {880, cY - 225}, {1015, cY - 225} }));
	drawPointLineString(LineString({ {830, cY - 195}, {895, cY - 260}, {1015, cY - 260} }));

	TextureAsset(L"stick_24").drawAt(245, cY + 75);
	TextureAsset(L"cross_24").drawAt(245, cY - 40);
	TextureAsset(L"buttonA_24").drawAt(1035, cY + 15);
	TextureAsset(L"buttonB_24").drawAt(1035, cY - 35);

	TextureAsset(L"buttonLB_24").drawAt( 245, cY - 225);
	TextureAsset(L"buttonLT_24").drawAt( 245, cY - 260);
	TextureAsset(L"buttonRB_24").drawAt(1035, cY - 225);
	TextureAsset(L"buttonRT_24").drawAt(1035, cY - 260);
}


void ControlGuidance::drawPointLine(Vec2 _root, Vec2 _pos, Color _color) {
	Line(_root, _pos).draw(5, _color);
	Circle(_root, 8).draw(_color);
}

void ControlGuidance::drawPointLineString(LineString _line, Color _color) {
	_line.draw(5, _color);
	Circle(_line.point(0), 5).draw(_color);
}


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

	TextureAsset(L"controller").drawAt(Window::Center());

	drawPointLine({ 540, 435 }, { 265, 435 });
	drawPointLine({ 445, 320 }, { 265, 320 });
	drawPointLine({ 830, 375 }, { 1015, 375 }, Color(L"#afa"));
	drawPointLine({ 880, 325 }, { 1015, 325 }, Color(L"#faa"));

	drawPointLineString(LineString({ {435, 170}, {400, 135}, {265, 135} }));
	drawPointLineString(LineString({ {450, 165}, {385, 100}, {265, 100} }));
	drawPointLineString(LineString({ {845, 170}, {880, 135}, {1015, 135} }));
	drawPointLineString(LineString({ {830, 165}, {895, 100}, {1015, 100} }));

	TextureAsset(L"stick_24").drawAt(245, 435);
	TextureAsset(L"cross_24").drawAt(245, 320);
	TextureAsset(L"buttonA_24").drawAt(1035, 375);
	TextureAsset(L"buttonB_24").drawAt(1035, 325);

	TextureAsset(L"buttonLB_24").drawAt(245, 135);
	TextureAsset(L"buttonLT_24").drawAt(245, 100);
	TextureAsset(L"buttonRB_24").drawAt(1035, 135);
	TextureAsset(L"buttonRT_24").drawAt(1035, 100);
}


void ControlGuidance::drawPointLine(Vec2 _root, Vec2 _pos, Color _color) {
	Line(_root, _pos).draw(5, _color);
	Circle(_root, 8).draw(_color);
}

void ControlGuidance::drawPointLineString(LineString _line, Color _color) {
	_line.draw(5, _color);
	Circle(_line.point(0), 5).draw(_color);
}


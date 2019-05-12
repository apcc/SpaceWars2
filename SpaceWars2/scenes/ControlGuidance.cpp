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

	drawPointLine({ 265, 435 }, { 540, 435 });
	drawPointLine({ 265, 320 }, { 445, 320 });
	drawPointLine({ 1015, 375 }, { 830, 375 }, Color(L"#afa"));
	drawPointLine({ 1015, 325 }, { 880, 325 }, Color(L"#faa"));
}


void ControlGuidance::drawPointLine(Vec2 _root, Vec2 _pos, Color _color) {
	Line(_root, _pos).draw(5, _color);
	Circle(_pos, 8).draw(_color);
}


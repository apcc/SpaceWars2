#include "ScreenGuidance.hpp"

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"SkillSelect", 500);
}

void ScreenGuidance::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	FontAsset(L"Smart32")(L"ScreenGuidance").drawCenter(40, Color(L"#ffffff"));
}

#include "ScreenGuidance.hpp"

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"SkillSelect", 500);
}

void ScreenGuidance::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"ScreenGuidance").drawCenter(40, Color(L"#ffffff"));
}

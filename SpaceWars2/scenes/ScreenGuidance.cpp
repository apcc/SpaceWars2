#include "ScreenGuidance.hpp"

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	changeScene(Debug::inputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"SkillSelect", 500);
}

void ScreenGuidance::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"ScreenGuidance").drawCenter(40, Color(L"#ffffff"));
}

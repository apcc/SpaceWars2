#include "./ScreenGuidance.hpp"
#include "../Config.hpp"
#include "../functions/Debug.hpp"

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	changeScene(Debug::inputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"SkillSelect", 500);
}

void ScreenGuidance::draw() const {
	TextureAsset(L"background").resize(Config::Width, Config::Height).draw();
	FontAsset(L"CicaR32")(L"ScreenGuidance").drawCenter(40, Color(L"#ffffff"));
}

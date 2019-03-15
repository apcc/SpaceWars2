#include "./ControlGuidance.hpp"
#include "../Config.hpp"
#include "../functions/Debug.hpp"

void ControlGuidance::init() {

}

void ControlGuidance::update() {
	changeScene(Debug::inputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"ScreenGuidance", 500);
}

void ControlGuidance::draw() const {
	TextureAsset(L"background").resize(Config::Width, Config::Height).draw();
	FontAsset(L"CicaR32")(L"ControlGuidance").drawCenter(40, Color(L"#ffffff"));
}

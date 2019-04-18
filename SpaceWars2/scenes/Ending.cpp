#include "Ending.hpp"

void Ending::init() {

}

void Ending::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"Opening");
}

void Ending::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"Smart32")(L"Thank you for playing!").drawCenter(40, Color(L"#ffffff"));
}

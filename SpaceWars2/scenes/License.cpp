#include "License.hpp"

void License::init() {

}

void License::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"Opening", 250);
}

void License::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"License").drawCenter(40, Color(L"#ffffff"));
}

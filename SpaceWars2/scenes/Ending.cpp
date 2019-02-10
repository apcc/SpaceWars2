#include "./Ending.hpp"
#include "../Config.hpp"

void Ending::init() {

}

void Ending::update() {
	changeScene(m_data->debug.inputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"Opening");
}

void Ending::draw() const {
	TextureAsset(L"background").resize(Config::Width, Config::Height).draw();
	FontAsset(L"CicaR32")(L"Thank you for playing!").drawCenter(40, Color(L"#ffffff"));
}

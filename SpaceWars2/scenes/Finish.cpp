#include "./Finish.hpp"
#include "../Config.hpp"

void Finish::init() {

}

void Finish::update() {
	changeScene(m_data->debug.inputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"Ending", 500);
}

void Finish::draw() const {
	TextureAsset(L"background").resize(Config::Width, Config::Height).draw();
	FontAsset(L"CicaR32")(L"RED WIN!（知らんけど").drawCenter(40, Color(L"#ffffff"));
}

#include "./ScreenGuidance.hpp"
#include "../Config.hpp"

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"SkillSelect");
}

void ScreenGuidance::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"ScreenGuidance").drawCenter(40, Color(L"#ffffff"));
}

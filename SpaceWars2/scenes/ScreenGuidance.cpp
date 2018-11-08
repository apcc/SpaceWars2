#pragma once
#include "ScreenGuidance.hpp"
#include "../Config.hpp"

void ScreenGuidance::init() {
	m_data->count++;
	Println(m_data->count);

}

void ScreenGuidance::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"SkillSelect");
	if (this->mode)
		y++;
	else
		y--;
	if (y < 0)mode = true;
	if (y > 800)mode = false;
}

void ScreenGuidance::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"ScreenGuidance").drawCenter(y/*200*/, Color(L"#ffffff"));
}

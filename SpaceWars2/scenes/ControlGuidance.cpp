#pragma once
#include "ControlGuidance.hpp"
#include "../Config.hpp"

void ControlGuidance::init() {
	m_data->count++;
	Println(m_data->count);

}

void ControlGuidance::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"ScreenGuidance");
	if (this->mode)
		y++;
	else
		y--;
	if (y < 0)mode = true;
	if (y > 800)mode = false;
}

void ControlGuidance::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"ControlGuidance").drawCenter(y/*200*/, Color(L"#ffffff"));
}

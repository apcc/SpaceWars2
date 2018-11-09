#pragma once
#include "ControlGuidance.hpp"
#include "../Config.hpp"

void ControlGuidance::init() {

}

void ControlGuidance::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"ScreenGuidance");
}

void ControlGuidance::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"ControlGuidance").drawCenter(40, Color(L"#ffffff"));
}

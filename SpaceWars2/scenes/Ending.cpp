#pragma once
#include "Ending.hpp"
#include "../Config.hpp"

void Ending::init() {

}

void Ending::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Opening");
}

void Ending::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"Thank you for playing!").drawCenter(40, Color(L"#ffffff"));
}

#pragma once
#include "Ending.hpp"
#include "Config.hpp"

void Ending::init() {
	this->CicaR32 = Font(32, L"Cica"); // :ac:
	m_data->count++;
	Println(m_data->count);

}

void Ending::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Opening");
	if (this->mode)
		y++;
	else
		y--;
	if (y < 0)mode = true;
	if (y > 800)mode = false;
}

void Ending::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	CicaR32(L"Thank you for playing!").drawCenter(y/*200*/, Color(L"#ffffff"));
}

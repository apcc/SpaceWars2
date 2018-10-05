#pragma once
#include "Opening.hpp"
#include "../Config.hpp"

void Opening::init(){
	this->CicaR32 = Font(32, L"Cica"); // :ac:
	m_data->count++;
	Println(m_data->count);
}

void Opening::update(){
	if (Input::KeyEnter.clicked)
		changeScene(L"ControlGuidance");
	if (this->mode)
		y++;
	else
		y--;
	if (y < 0)mode = true;
	if (y > 720)mode = false;
}

void Opening::draw() const{
	m_data->background.resize(Config::Width, Config::Height).draw();
	CicaR32(L"SpaceWars2").drawCenter(y/*200*/, Color(L"#ffffff"));
}

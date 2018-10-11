#pragma once
#include "SkillSelect.hpp"
#include "../Config.hpp"

void SkillSelect::init() {
	this->CicaR32 = Font(32, L"Cica"); // :ac:
	m_data->count++;
	Println(m_data->count);
	m_data->LPlayer.Init(40, Config::Height / 2, true);  //‰~‚Ì”¼Œa
	m_data->RPlayer.Init(1240, Config::Height / 2, false); //Width-‰~‚Ì”¼Œa
}

void SkillSelect::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Game");
	if (this->mode)
		y++;
	else
		y--;
	if (y < 0)mode = true;
	if (y > 720)mode = false;
}

void SkillSelect::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	CicaR32(L"SkillSelect").drawCenter(y/*200*/, Color(L"#ffffff"));
}

#pragma once
#include "SkillSelect.hpp"
#include "../Config.hpp"

#include "../functions/Player.hpp"

void SkillSelect::init() {
	this->CicaR32 = Font(32, L"Cica"); // :ac:
	m_data->count++;
	Println(m_data->count);
	m_data->LPlayer.Init(40, Config::Height / 2, true);
	m_data->RPlayer.Init(1240, Config::Height / 2, false);
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

	m_data->LPlayer.SkillSelect();
	m_data->RPlayer.SkillSelect();

}

void SkillSelect::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	CicaR32(L"SkillSelect").drawCenter(y/*200*/, Color(L"#ffffff"));
	
	CicaR32(m_data->LPlayer.whatMainSkill).draw(40, 40);
	CicaR32(m_data->LPlayer.whatSubSkill).draw(40, 80);
	CicaR32(m_data->LPlayer.whatSpecialSkill).draw(40, 120);

	CicaR32(m_data->RPlayer.whatMainSkill).draw(1240, 40);
	CicaR32(m_data->RPlayer.whatSubSkill).draw(1240, 80);
	CicaR32(m_data->RPlayer.whatSpecialSkill).draw(1240, 120);
}

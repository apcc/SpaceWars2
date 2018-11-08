#pragma once
#include "SkillSelect.hpp"
#include "../Config.hpp"

#include "../functions/Player.hpp"

void SkillSelect::init() {
	m_data->LPlayer.Init(40, Config::Height / 2, true);
	m_data->RPlayer.Init(1240, Config::Height / 2, false);
}

void SkillSelect::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Game");
	
	m_data->LPlayer.SkillSelect();
	m_data->RPlayer.SkillSelect();

}

void SkillSelect::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"SkillSelect").drawCenter(40, Color(L"#ffffff"));
	
	m_data->CicaR32(m_data->LPlayer.whatMainSkill).draw(40, 40);
	m_data->CicaR32(m_data->LPlayer.whatSubSkill).draw(40, 80);
	m_data->CicaR32(m_data->LPlayer.whatSpecialSkill).draw(40, 120);

	m_data->CicaR32(m_data->RPlayer.whatMainSkill).draw(1240, 40);
	m_data->CicaR32(m_data->RPlayer.whatSubSkill).draw(1240, 80);
	m_data->CicaR32(m_data->RPlayer.whatSpecialSkill).draw(1240, 120);
}

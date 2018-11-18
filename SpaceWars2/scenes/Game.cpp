#pragma once
#include "Game.hpp"
#include "../Config.hpp"

#include "../functions/Player.hpp"

void Game::init() {

}

void Game::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Finish");

	m_data->LPlayer.Control();
	m_data->RPlayer.Control();

	m_data->LPlayer.UpdateMainSkill();
	m_data->LPlayer.UpdateSubSkill();
	m_data->LPlayer.UpdateSpecialSkill();
	m_data->RPlayer.UpdateMainSkill();
	m_data->RPlayer.UpdateSubSkill();
	m_data->RPlayer.UpdateSpecialSkill();
}

void Game::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"I am game scene! Hello!").drawCenter(40, Color(L"#ffffff"));
	m_data->LPlayer.DrawShip();
	m_data->RPlayer.DrawShip();
	m_data->LPlayer.DrawGauge();
	m_data->RPlayer.DrawGauge();

	m_data->LPlayer.DrawMainSkill();
	m_data->LPlayer.DrawSubSkill();
	m_data->LPlayer.DrawSpecialSkill();
	m_data->RPlayer.DrawMainSkill();
	m_data->RPlayer.DrawSubSkill();
	m_data->RPlayer.DrawSpecialSkill();
}

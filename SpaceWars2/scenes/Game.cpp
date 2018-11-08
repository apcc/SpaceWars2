#pragma once
#include "Game.hpp"
#include "../Config.hpp"

#include "../functions/Player.hpp"

void Game::init() {
	m_data->count++;
	Println(m_data->count);
}

void Game::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Finish");
	m_data->LPlayer.Control();
	m_data->RPlayer.Control();
}

void Game::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"I am game scene! Hello!").drawCenter(y/*200*/, Color(L"#ffffff"));
	m_data->LPlayer.DrawShip();
	m_data->RPlayer.DrawShip();
}

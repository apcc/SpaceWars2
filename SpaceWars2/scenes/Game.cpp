#pragma once
#include "Game.hpp"
#include "../Config.hpp"

#include "../functions/Player.hpp"

void Game::init() {
	this->CicaR32 = Font(32, L"Cica"); // :ac:
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
	CicaR32(L"I am game scene! Hello!").drawCenter(y/*200*/, Color(L"#ffffff"));
	m_data->LPlayer.ship.draw(Color(L"#ff0000"));
	m_data->RPlayer.ship.draw(Color(L"#0000ff"));
}

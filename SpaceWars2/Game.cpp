#include "Game.hpp"

void Game::init() {
	this->CicaR32 = Font(32, L"Cica"); // :ac:
	m_data->count++;
	Println(m_data->count);

}

void Game::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Finish");
	if (this->mode)
		y++;
	else
		y--;
	if (y < 0)mode = true;
	if (y > 800)mode = false;
}

void Game::draw() const {
	CicaR32(L"I am game scene! Hello!").drawCenter(y/*200*/, Color(L"#000000"));
}
#include "Finish.hpp"

void Finish::init() {
	this->CicaR32 = Font(32, L"Cica"); // :ac:
	m_data->count++;
	Println(m_data->count);

}

void Finish::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Ending");
	if (this->mode)
		y++;
	else
		y--;
	if (y < 0)mode = true;
	if (y > 800)mode = false;
}

void Finish::draw() const {
	CicaR32(L"RED WIN!（知らんけど").drawCenter(y/*200*/, Color(L"#000000"));
}
#pragma once
#include "Finish.hpp"
#include "../Config.hpp"

void Finish::init() {

}

void Finish::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Ending");
}

void Finish::draw() const {
	m_data->background.resize(Config::Width, Config::Height).draw();
	FontAsset(L"CicaR32")(L"RED WIN!（知らんけど").drawCenter(40, Color(L"#ffffff"));
}

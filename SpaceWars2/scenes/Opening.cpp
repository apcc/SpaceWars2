#pragma once
#include "Opening.hpp"
#include "../Config.hpp"

void Opening::init(){
	m_data->LPlayer.Init(40,   Config::Height/2, true);  //円の半径
	m_data->RPlayer.Init(1240, Config::Height/2, false); //Width-円の半径
}

void Opening::update(){
	if (Input::KeyEnter.clicked)
		changeScene(L"ControlGuidance");
}

void Opening::draw() const{
	TextureAsset(L"background").resize(Config::Width, Config::Height).draw();
	FontAsset(L"CicaR32")(L"SpaceWars2").drawCenter(40, Color(L"#ffffff"));
}

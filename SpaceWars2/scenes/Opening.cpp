#include "./Opening.hpp"
#include "../Config.hpp"

void Opening::init(){
	m_data->LPlayer.Init(Vec2(  80, Config::Height/2), true);  //円の半径
	m_data->RPlayer.Init(Vec2(1200, Config::Height/2), false); //Width-円の半径
}

void Opening::update(){
	if (Input::KeyEnter.clicked)
		changeScene(L"ControlGuidance");
}

void Opening::draw() const{
	m_data->background.resize(Config::Width, Config::Height).draw();
	m_data->CicaR32(L"SpaceWars2").drawCenter(40, Color(L"#ffffff"));
}

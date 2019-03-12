#include "./Opening.hpp"
#include "../Config.hpp"
#include "../functions/Debug.hpp"

void Opening::init(){
	m_data->LPlayer.Init(Vec2(  80, Config::HEIGHT/2), true);  //円の半径
	m_data->RPlayer.Init(Vec2(1200, Config::HEIGHT/2), false); //Width-円の半径
}

void Opening::update(){
	changeScene(Debug::inputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"ControlGuidance", 500);
}

void Opening::draw() const{
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"SpaceWars2").drawCenter(40, Color(L"#ffffff"));
}

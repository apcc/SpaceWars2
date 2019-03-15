#include "Opening.hpp"

void Opening::init(){
	Data::LPlayer.init(Vec2(  80, Config::HEIGHT/2), true);  //円の半径
	Data::RPlayer.init(Vec2(1200, Config::HEIGHT/2), false); //Width-円の半径
}

void Opening::update(){
	changeScene(Debug::InputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"ControlGuidance", 500);
}

void Opening::draw() const{
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"SpaceWars2").drawCenter(40, Color(L"#ffffff"));
}

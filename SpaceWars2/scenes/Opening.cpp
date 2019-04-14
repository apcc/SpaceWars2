#include "Opening.hpp"

void Opening::init(){
	Data::LPlayer.init(Vec2(  80, Config::HEIGHT/2), true);  //円の半径
	Data::RPlayer.init(Vec2(1200, Config::HEIGHT/2), false); //WIDTH-円の半径
}

void Opening::update(){
	changeScene(Debug::InputFnKey(), 250);

	if ((GamePad::Key(true, L"KeyUp") || GamePad::Key(false, L"KeyUp")) && selecting > 0)
		--selecting;
	if ((GamePad::Key(true, L"KeyDown") || GamePad::Key(false, L"KeyDown")) && selecting < 2)
		++selecting;

	if (Data::KeyEnter.repeat(20)) {
		switch(selecting) {
		case 0:
			changeScene(L"ControlGuidance", 500);
			break;

		case 1:
			changeScene(L"License");
			break;

		case 2:
			System::Exit();
			break;

		default:
			LOG_ERROR(L"Title画面で意図しない値 \"", selecting, L"\" が参照されました。");
		}
	}

}

void Opening::draw() const{
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	TextureAsset(L"title-logo").drawAt(Config::WIDTH / 2, 150);

	FontAsset(L"CicaR32")(L"START").draw(900, 450);
	FontAsset(L"CicaR32")(L"LICENSE").draw(900, 525);
	FontAsset(L"CicaR32")(L"EXIT").draw(900, 600);
	Triangle({ 850, 465 + selecting * 75 }, { 878, 481 + selecting * 75 }, { 850, 497 + selecting * 75 }).draw();
}

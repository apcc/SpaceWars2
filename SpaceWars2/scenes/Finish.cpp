#include "Finish.hpp"

void Finish::init() {
	if (Data::LPlayer.isHPRunOut() && Data::RPlayer.isHPRunOut())
		isDraw = true;
	if (Data::LPlayer.isHPRunOut())
		isLeftWin = false;
	if (Data::RPlayer.isHPRunOut())
		isLeftWin = true;
	
	if (isDraw)
		winner = L"引き分け！";
	else if (isLeftWin)
		winner = L"REDの勝ち！";
	else
		winner = L"BLUEの勝ち！";
}

void Finish::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"Ending", 500);
}

void Finish::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(winner).drawCenter(40, Color(L"#ffffff"));
}

#include "Game.hpp"

void Game::init() {

}

void Game::update() {

	if (!finish) {
		changeScene(Debug::InputFnKey(), 250);

		Data::LPlayer.update(bullets);
		Data::RPlayer.update(bullets);

		if (!Player::inJudgmentTime) {
			for (auto itr = bullets.begin(); itr != bullets.end();) {
				Vec2 myPos = ((**itr).isLeft ? Data::LPlayer : Data::RPlayer).circle().center;
				Vec2 oppPos = ((**itr).isLeft ? Data::RPlayer : Data::LPlayer).circle().center;

				if ((**itr).update(myPos, oppPos)) {
					delete* itr;
					itr = bullets.erase(itr);
				}
				else {
					itr++;
				}
			}
		}
	}
	else { // finish

		if (Data::KeyEnter.repeat(20))
			changeScene(L"Ending", 500);
	}

	if (Data::LPlayer.isHPRunOut() || Data::RPlayer.isHPRunOut())
		finish = true;
}

void Game::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();

	/*Data::LPlayer.DrawMainSkill();
	Data::LPlayer.DrawSubSkill();
	Data::LPlayer.DrawSpecialSkill();
	Data::RPlayer.DrawMainSkill();
	Data::RPlayer.DrawSubSkill();
	Data::RPlayer.DrawSpecialSkill();*/
	for(auto bul : bullets){
		bul->draw();
	}

	Data::LPlayer.drawShip();
	Data::RPlayer.drawShip();
	Data::LPlayer.drawGauge();
	Data::RPlayer.drawGauge();

	if (!finish) {
		FontAsset(L"Smart32")(L"I am game scene! Hello!").drawCenter(40, Color(L"#ffffff"));

		Vec2 buttonPos(890, 692);

		buttonPos.x += (int)TextureAsset(L"stick_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"移動").draw(buttonPos).w + 15;

		buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"Main").draw(buttonPos).w + 15;

		buttonPos.x += (int)TextureAsset(L"buttonLB_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"Sub").draw(buttonPos).w + 15;

		buttonPos.x += (int)TextureAsset(L"buttonRB_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"Special").draw(buttonPos).w + 15;
	}
	else {
		Rect(0, 0, Config::WIDTH, Config::HEIGHT).draw(ColorF(L"#000").setAlpha(0.7));

		FontAsset(L"Smart32")(L"Finish!").drawCenter(300, Color(L"#ffffff"));
	}
}

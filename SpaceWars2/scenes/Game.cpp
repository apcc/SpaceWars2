#include "Game.hpp"

void Game::init() {}

void Game::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"Finish", 500);

	Data::LPlayer.update(bullets);
	Data::RPlayer.update(bullets);


	/*Data::RPlayer.receiveDamage(Data::LPlayer.UpdateMainSkill(Data::RPlayer.circle()));
	Data::LPlayer.UpdateSubSkill();
	Data::LPlayer.UpdateSpecialSkill();

	Data::LPlayer.receiveDamage(Data::RPlayer.UpdateMainSkill(Data::LPlayer.circle()));
	Data::RPlayer.UpdateSubSkill();
	Data::RPlayer.UpdateSpecialSkill();*/

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

	if(Data::LPlayer.isHPRunOut() || Data::RPlayer.isHPRunOut())
		changeScene(L"Finish");
}

void Game::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"Smart32")(L"I am game scene! Hello!").drawCenter(40, Color(L"#ffffff"));

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
}

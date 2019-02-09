#include "./Game.hpp"
#include "../Config.hpp"

#include "../functions/Player.hpp"

void Game::init() {

}

void Game::update() {
	if (Input::KeyEnter.clicked)
		changeScene(L"Finish");

	m_data->LPlayer.Update(bullets);
	m_data->RPlayer.Update(bullets);


	/*m_data->RPlayer.receiveDamage(m_data->LPlayer.UpdateMainSkill(m_data->RPlayer.circle()));
	m_data->LPlayer.UpdateSubSkill();
	m_data->LPlayer.UpdateSpecialSkill();

	m_data->LPlayer.receiveDamage(m_data->RPlayer.UpdateMainSkill(m_data->LPlayer.circle()));
	m_data->RPlayer.UpdateSubSkill();
	m_data->RPlayer.UpdateSpecialSkill();*/

	for(auto itr = bullets.begin(); itr != bullets.end();){
		if((**itr).update()){
			delete *itr;
			itr = bullets.erase(itr);
		}else{
			itr++;
		}
	}

	if(m_data->LPlayer.gameEnd() || m_data->RPlayer.gameEnd())
		changeScene(L"Finish");
}

void Game::draw() const {
	TextureAsset(L"background").resize(Config::Width, Config::Height).draw();
	FontAsset(L"CicaR32")(L"I am game scene! Hello!").drawCenter(40, Color(L"#ffffff"));

	/*m_data->LPlayer.DrawMainSkill();
	m_data->LPlayer.DrawSubSkill();
	m_data->LPlayer.DrawSpecialSkill();
	m_data->RPlayer.DrawMainSkill();
	m_data->RPlayer.DrawSubSkill();
	m_data->RPlayer.DrawSpecialSkill();*/
	for(auto bul : bullets){
		bul->draw();
	}
  
	m_data->LPlayer.DrawShip();
	m_data->RPlayer.DrawShip();
	m_data->LPlayer.DrawGauge();
	m_data->RPlayer.DrawGauge();
}

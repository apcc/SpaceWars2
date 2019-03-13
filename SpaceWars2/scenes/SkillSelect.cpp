#include "SkillSelect.hpp"

void SkillSelect::init() {

}

void SkillSelect::update() {
	changeScene(Debug::inputFnKey(), 250);
	if (Input::KeyEnter.clicked)
		changeScene(L"Game", 500);

	m_data->LPlayer.skillSelect();
	m_data->RPlayer.skillSelect();

}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"SkillSelect").drawCenter(40, Color(L"#ffffff"));

	FontAsset(L"CicaR32")(m_data->LPlayer.whatMainSkill).draw(40, 40);
	FontAsset(L"CicaR32")(m_data->LPlayer.whatSubSkill).draw(40, 80);
	FontAsset(L"CicaR32")(m_data->LPlayer.whatSpecialSkill).draw(40, 120);

	FontAsset(L"CicaR32")(m_data->RPlayer.whatMainSkill).draw(1240, 40);
	FontAsset(L"CicaR32")(m_data->RPlayer.whatSubSkill).draw(1240, 80);
	FontAsset(L"CicaR32")(m_data->RPlayer.whatSpecialSkill).draw(1240, 120);
}

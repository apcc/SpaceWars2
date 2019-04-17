#include "SkillSelect.hpp"

void SkillSelect::init() {

}

void SkillSelect::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"Three", 500);

	Data::LPlayer.skillSelect();
	Data::RPlayer.skillSelect();

}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"Smart32")(L"SkillSelect").drawCenter(40, Color(L"#ffffff"));

	FontAsset(L"Smart32")(Data::LPlayer.whatMainSkill).draw(40, 40);
	FontAsset(L"Smart32")(Data::LPlayer.whatSubSkill).draw(40, 80);
	FontAsset(L"Smart32")(Data::LPlayer.whatSpecialSkill).draw(40, 120);

	FontAsset(L"Smart32")(Data::RPlayer.whatMainSkill).draw(1240, 40);
	FontAsset(L"Smart32")(Data::RPlayer.whatSubSkill).draw(1240, 80);
	FontAsset(L"Smart32")(Data::RPlayer.whatSpecialSkill).draw(1240, 120);
}

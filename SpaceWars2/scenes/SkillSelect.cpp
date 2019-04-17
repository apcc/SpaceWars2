#include "SkillSelect.hpp"

#define V80 { 80, 80 }

void SkillSelect::init() {
	int i = 0;
	for (int j = -1; j < 6; j++) {
		TextureAsset::Register(L"main" + Format(j),		L"/800" + Format(i));
		TextureAsset::Register(L"sub" + Format(j),		L"/801" + Format(i));
		TextureAsset::Register(L"special" + Format(j),	L"/802" + Format(i));
		++i;
	}
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
	FontAsset(L"CicaR32")(L"SkillSelect").drawCenter(40, Color(L"#ffffff"));

	FontAsset(L"CicaR32")(Data::LPlayer.whatMainSkill).draw(40, 40);
	FontAsset(L"CicaR32")(Data::LPlayer.whatSubSkill).draw(40, 80);
	FontAsset(L"CicaR32")(Data::LPlayer.whatSpecialSkill).draw(40, 120);

	FontAsset(L"CicaR32")(Data::RPlayer.whatMainSkill).draw(1240, 40);
	FontAsset(L"CicaR32")(Data::RPlayer.whatSubSkill).draw(1240, 80);
	FontAsset(L"CicaR32")(Data::RPlayer.whatSpecialSkill).draw(1240, 120);
	
	TextureAsset(L"main" + Format(Data::LPlayer.whatMainSkill - 1)).resize(V80).drawAt(130, 450);
	TextureAsset(L"sub" + Format(Data::LPlayer.whatSubSkill - 1)).resize(V80).drawAt(320, 450);
	TextureAsset(L"special" + Format(Data::LPlayer.whatSpecialSkill - 1)).resize(V80).drawAt(510, 450);
	TextureAsset(L"main" + Format(Data::RPlayer.whatMainSkill - 1)).resize(V80).drawAt(770, 450);
	TextureAsset(L"sub" + Format(Data::RPlayer.whatSubSkill - 1)).resize(V80).drawAt(960, 450);
	TextureAsset(L"special" + Format(Data::RPlayer.whatSpecialSkill - 1)).resize(V80).drawAt(1150, 450);

	TextureAsset(L"main" + Format(Data::LPlayer.whatMainSkill)).drawAt(130, 550);
	TextureAsset(L"sub" + Format(Data::LPlayer.whatSubSkill)).drawAt(320, 550);
	TextureAsset(L"special" + Format(Data::LPlayer.whatSpecialSkill)).drawAt(510, 550);
	TextureAsset(L"main" + Format(Data::RPlayer.whatMainSkill)).drawAt(770, 550);
	TextureAsset(L"sub" + Format(Data::RPlayer.whatSubSkill)).drawAt(960, 550);
	TextureAsset(L"special" + Format(Data::RPlayer.whatSpecialSkill)).drawAt(1150, 550);

	TextureAsset(L"main" + Format(Data::LPlayer.whatMainSkill + 1)).resize(V80).drawAt(130, 650);
	TextureAsset(L"sub" + Format(Data::LPlayer.whatSubSkill + 1)).resize(V80).drawAt(320, 650);
	TextureAsset(L"special" + Format(Data::LPlayer.whatSpecialSkill + 1)).resize(V80).drawAt(510, 650);
	TextureAsset(L"main" + Format(Data::RPlayer.whatMainSkill + 1)).resize(V80).drawAt(770, 650);
	TextureAsset(L"sub" + Format(Data::RPlayer.whatSubSkill + 1)).resize(V80).drawAt(960, 650);
	TextureAsset(L"special" + Format(Data::RPlayer.whatSpecialSkill + 1)).resize(V80).drawAt(1150, 650);
}

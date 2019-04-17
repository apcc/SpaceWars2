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
	TextureAsset::Register(L"mainTriangle", L"/8100");
	TextureAsset::Register(L"subTriangle", L"/8101");
	TextureAsset::Register(L"specialTriangle", L"/8102");
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
	
	TextureAsset(L"main" + Format(Data::LPlayer.whatMainSkill - 1)).resize(V80).drawAt(130, 440);
	TextureAsset(L"sub" + Format(Data::LPlayer.whatSubSkill - 1)).resize(V80).drawAt(320, 440);
	TextureAsset(L"special" + Format(Data::LPlayer.whatSpecialSkill - 1)).resize(V80).drawAt(510, 440);
	TextureAsset(L"main" + Format(Data::RPlayer.whatMainSkill - 1)).resize(V80).drawAt(770, 440);
	TextureAsset(L"sub" + Format(Data::RPlayer.whatSubSkill - 1)).resize(V80).drawAt(960, 440);
	TextureAsset(L"special" + Format(Data::RPlayer.whatSpecialSkill - 1)).resize(V80).drawAt(1150, 440);

	TextureAsset(L"main" + Format(Data::LPlayer.whatMainSkill)).drawAt(130, 550);
	TextureAsset(L"sub" + Format(Data::LPlayer.whatSubSkill)).drawAt(320, 550);
	TextureAsset(L"special" + Format(Data::LPlayer.whatSpecialSkill)).drawAt(510, 550);
	TextureAsset(L"main" + Format(Data::RPlayer.whatMainSkill)).drawAt(770, 550);
	TextureAsset(L"sub" + Format(Data::RPlayer.whatSubSkill)).drawAt(960, 550);
	TextureAsset(L"special" + Format(Data::RPlayer.whatSpecialSkill)).drawAt(1150, 550);

	TextureAsset(L"main" + Format(Data::LPlayer.whatMainSkill + 1)).resize(V80).drawAt(130, 660);
	TextureAsset(L"sub" + Format(Data::LPlayer.whatSubSkill + 1)).resize(V80).drawAt(320, 660);
	TextureAsset(L"special" + Format(Data::LPlayer.whatSpecialSkill + 1)).resize(V80).drawAt(510, 660);
	TextureAsset(L"main" + Format(Data::RPlayer.whatMainSkill + 1)).resize(V80).drawAt(770, 660);
	TextureAsset(L"sub" + Format(Data::RPlayer.whatSubSkill + 1)).resize(V80).drawAt(960, 660);
	TextureAsset(L"special" + Format(Data::RPlayer.whatSpecialSkill + 1)).resize(V80).drawAt(1150, 660);

	Rect(  80, 500, 100).drawFrame(0, 4, Color(L"#7cfc00"));
	Rect( 270, 500, 100).drawFrame(0, 4, Color(L"#4169e1"));
	Rect( 460, 500, 100).drawFrame(0, 4, Color(L"#ffd000"));
	Rect( 720, 500, 100).drawFrame(0, 4, Color(L"#7cfc00"));
	Rect( 910, 500, 100).drawFrame(0, 4, Color(L"#4169e1"));
	Rect(1100, 500, 100).drawFrame(0, 4, Color(L"#ffd000"));

	if (Data::LPlayer.whatMainSkill != 0)
		TextureAsset(L"mainTriangle").draw(115, 485);
	if (Data::LPlayer.whatMainSkill != MAIN_NUM - 1)
		TextureAsset(L"mainTriangle").flip().draw(115, 600);
	if (Data::LPlayer.whatSubSkill != 0)
		TextureAsset(L"subTriangle").draw(305, 485);
	if (Data::LPlayer.whatSubSkill != SUB_NUM - 1)
		TextureAsset(L"subTriangle").flip().draw(305, 600);
	if (Data::LPlayer.whatSpecialSkill != 0)
		TextureAsset(L"specialTriangle").draw(495, 485);
	if (Data::LPlayer.whatSpecialSkill != SPECIAL_NUM - 1)
		TextureAsset(L"specialTriangle").flip().draw(495, 600);

	if (Data::RPlayer.whatMainSkill != 0)
		TextureAsset(L"mainTriangle").draw(755, 485);
	if (Data::RPlayer.whatMainSkill != MAIN_NUM - 1)
		TextureAsset(L"mainTriangle").flip().draw(755, 600);
	if (Data::RPlayer.whatSubSkill != 0)
		TextureAsset(L"subTriangle").draw(945, 485);
	if (Data::RPlayer.whatSubSkill != SUB_NUM - 1)
		TextureAsset(L"subTriangle").flip().draw(945, 600);
	if (Data::RPlayer.whatSpecialSkill != 0)
		TextureAsset(L"specialTriangle").draw(1135, 485);
	if (Data::RPlayer.whatSpecialSkill != SPECIAL_NUM - 1)
		TextureAsset(L"specialTriangle").flip().draw(1135, 600);
	
}

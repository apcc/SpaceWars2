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

	switch (Data::LPlayer.skillSelect()) {
	case 0:
		LMainAlpha = 1.0;
		LSubAlpha = 0.5;
		break;

	case 1:
		LMainAlpha = 0.5;
		LSubAlpha = 1.0;
		LSpecialAlpha = 0.5;
		break;

	case 2:
		LSubAlpha = 0.5;
		LSpecialAlpha = 1.0;
		break;

	default:
		LOG_ERROR(L"SkillSelect::update()のLPlayer用switchでdefaultが参照されました。");
	}

	switch(Data::RPlayer.skillSelect()) {
	case 0:
		RMainAlpha = 1.0;
		RSubAlpha = 0.5;
		break;

	case 1:
		RMainAlpha = 0.5;
		RSubAlpha = 1.0;
		RSpecialAlpha = 0.5;
		break;

	case 2:
		RSubAlpha = 0.5;
		RSpecialAlpha = 1.0;
		break;

	default:
		LOG_ERROR(L"SkillSelect::update()のRPlayer用switchでdefaultが参照されました。");
	}

}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"SkillSelect").drawCenter(40, Color(L"#ffffff"));

	for (int isLeft = 0; isLeft < 2; isLeft++) {
		Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
		String skilltype[3] = { L"main", L"sub", L"special" };
		int whatskill[3] = { (*PLAYER).whatMainSkill, (*PLAYER).whatSubSkill, (*PLAYER).whatSpecialSkill };
		for (int i = -1; i < 2; i++) {
			for (int type = 0; type < 3; type++) {
				if (i) TextureAsset(skilltype[type] + Format(whatskill[type] + i)).resize(V80).drawAt(770 + 190 * type - 640 * isLeft, 550 + 110 * i);
				else  TextureAsset(skilltype[type] + Format(whatskill[type])).drawAt(770 + 190 * type - 640 * isLeft, 550);
			}
		}
	}

	// 選択中のskillの枠
	Rect(  80, 500, 100).drawFrame(0, 4, ColorF(L"#7cfc00").setAlpha(LMainAlpha));
	Rect( 270, 500, 100).drawFrame(0, 4, ColorF(L"#4169e1").setAlpha(LSubAlpha));
	Rect( 460, 500, 100).drawFrame(0, 4, ColorF(L"#ffd000").setAlpha(LSpecialAlpha));
	Rect( 720, 500, 100).drawFrame(0, 4, ColorF(L"#7cfc00").setAlpha(RMainAlpha));
	Rect( 910, 500, 100).drawFrame(0, 4, ColorF(L"#4169e1").setAlpha(RSubAlpha));
	Rect(1100, 500, 100).drawFrame(0, 4, ColorF(L"#ffd000").setAlpha(RSpecialAlpha));

	// 枠の上下の三角 for LPlayer
	if (Data::LPlayer.whatMainSkill != 0)
		TextureAsset(L"mainTriangle").draw(115, 485, Alpha((int)(255 * LMainAlpha)));
	if (Data::LPlayer.whatMainSkill != MAIN_NUM - 1)
		TextureAsset(L"mainTriangle").flip().draw(115, 600, Alpha((int)(255 * LMainAlpha)));
	if (Data::LPlayer.whatSubSkill != 0)
		TextureAsset(L"subTriangle").draw(305, 485, Alpha((int)(255 * LSubAlpha)));
	if (Data::LPlayer.whatSubSkill != SUB_NUM - 1)
		TextureAsset(L"subTriangle").flip().draw(305, 600, Alpha((int)(255 * LSubAlpha)));
	if (Data::LPlayer.whatSpecialSkill != 0)
		TextureAsset(L"specialTriangle").draw(495, 485, Alpha((int)(255 * LSpecialAlpha)));
	if (Data::LPlayer.whatSpecialSkill != SPECIAL_NUM - 1)
		TextureAsset(L"specialTriangle").flip().draw(495, 600, Alpha((int)(255 * LSpecialAlpha)));

	// 枠の上下の三角 for RPlayer
	if (Data::RPlayer.whatMainSkill != 0)
		TextureAsset(L"mainTriangle").draw(755, 485, Alpha((int)(255 * RMainAlpha)));
	if (Data::RPlayer.whatMainSkill != MAIN_NUM - 1)
		TextureAsset(L"mainTriangle").flip().draw(755, 600, Alpha((int)(255 * RMainAlpha)));
	if (Data::RPlayer.whatSubSkill != 0)
		TextureAsset(L"subTriangle").draw(945, 485, Alpha((int)(255 * RSubAlpha)));
	if (Data::RPlayer.whatSubSkill != SUB_NUM - 1)
		TextureAsset(L"subTriangle").flip().draw(945, 600, Alpha((int)(255 * RSubAlpha)));
	if (Data::RPlayer.whatSpecialSkill != 0)
		TextureAsset(L"specialTriangle").draw(1135, 485, Alpha((int)(255 * RSpecialAlpha)));
	if (Data::RPlayer.whatSpecialSkill != SPECIAL_NUM - 1)
		TextureAsset(L"specialTriangle").flip().draw(1135, 600, Alpha((int)(255 * RSpecialAlpha)));
	
}

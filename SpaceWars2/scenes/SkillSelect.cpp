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
		LAlpha[0] = 1.0;
		LAlpha[1] = 0.5;
		break;

	case 1:
		LAlpha[0] = 0.5;
		LAlpha[1] = 1.0;
		LAlpha[2] = 0.5;
		break;

	case 2:
		LAlpha[1] = 0.5;
		LAlpha[2] = 1.0;
		break;

	default:
		LOG_ERROR(L"SkillSelect::update()のLPlayer用switchでdefaultが参照されました。");
	}

	switch(Data::RPlayer.skillSelect()) {
	case 0:
		RAlpha[0] = 1.0;
		RAlpha[1] = 0.5;
		break;

	case 1:
		RAlpha[0] = 0.5;
		RAlpha[1] = 1.0;
		RAlpha[2] = 0.5;
		break;

	case 2:
		RAlpha[1] = 0.5;
		RAlpha[2] = 1.0;
		break;

	default:
		LOG_ERROR(L"SkillSelect::update()のRPlayer用switchでdefaultが参照されました。");
	}

}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	FontAsset(L"CicaR32")(L"SkillSelect").drawCenter(40, Color(L"#ffffff"));

	for (int isLeft = 0; isLeft < 2; isLeft++) { // LPlayer, RPlayer
		Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
		String skillType[3] = { L"main", L"sub", L"special" };
		int whatSkill[3] = { (*PLAYER).whatMainSkill, (*PLAYER).whatSubSkill, (*PLAYER).whatSpecialSkill };
		int skillNum[3] = { MAIN_NUM - 1, SUB_NUM - 1, SPECIAL_NUM - 1 };
		for (int type = 0; type < 3; type++) { // mainSkill, subSkill, specialSkill

			// skillIconの描画
			for (int i = -1; i < 2; i++) { // -1:前 0:選択中 1:後
				if (i) TextureAsset(skillType[type] + Format((int)whatSkill[type] + i)).resize(V80)
					.drawAt(770 + (190 * type) - (640 * isLeft), 550 + 110 * i);
				else   TextureAsset(skillType[type] + Format((int)whatSkill[type]))
					.drawAt(770 + (190 * type) - (640 * isLeft), 550);
			}

			// 三角マークの描画
			if (whatSkill[type] != 0)
				TextureAsset(skillType[type] + L"Triangle").draw(755 + (190 * type) - (640 * isLeft), 485, Alpha((int)(255 * LAlpha[type])));
			if (whatSkill[type] != skillNum[type])
				TextureAsset(skillType[type] + L"Triangle").flip().draw(755 + (190 * type) - (640 * isLeft), 600, Alpha((int)(255 * LAlpha[type])));
		}
	}

	// 選択中のskillの枠
	Rect(  80, 500, 100).drawFrame(0, 4, ColorF(L"#7cfc00").setAlpha(LAlpha[0]));
	Rect( 270, 500, 100).drawFrame(0, 4, ColorF(L"#4169e1").setAlpha(LAlpha[1]));
	Rect( 460, 500, 100).drawFrame(0, 4, ColorF(L"#ffd000").setAlpha(LAlpha[2]));
	Rect( 720, 500, 100).drawFrame(0, 4, ColorF(L"#7cfc00").setAlpha(RAlpha[0]));
	Rect( 910, 500, 100).drawFrame(0, 4, ColorF(L"#4169e1").setAlpha(RAlpha[1]));
	Rect(1100, 500, 100).drawFrame(0, 4, ColorF(L"#ffd000").setAlpha(RAlpha[2]));
}

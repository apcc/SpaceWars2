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

	for (int isLeft = 0; isLeft <= 1; isLeft++) { // LPlayer, RPlayer
		Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
		double alpha[3]      = { (isLeft ? LAlpha : RAlpha)[0], (isLeft ? LAlpha : RAlpha)[1], (isLeft ? LAlpha : RAlpha)[2] };
		String skillType[3]  = { L"main", L"sub", L"special" };
		int    whatSkill[3]  = { PLAYER->whatMainSkill, PLAYER->whatSubSkill, PLAYER->whatSpecialSkill };
		int    skillNum[3]   = { MAIN_NUM - 1, SUB_NUM - 1, SPECIAL_NUM - 1 };
		String skillColor[3] = { L"#7cfc00", L"#4169e1", L"#ffd000" };
		for (int type = 0; type < 3; type++) { // mainSkill, subSkill, specialSkill

			// skillIconの描画
			for (int i = -1; i <= 1; i++) { // -1:前 0:選択中 1:後
				if (i)
					TextureAsset(skillType[type] + Format((int)whatSkill[type] + i)).resize(V80)
						.drawAt(770 + (190 * type) - (640 * isLeft), 520 + 110 * i);
				else
					TextureAsset(skillType[type] + Format((int)whatSkill[type]))
						.drawAt(770 + (190 * type) - (640 * isLeft), 520);
			}
			
			// 選択中のskillの枠
			Rect(720 + (190 * type) - (640 * isLeft), 470, 100).drawFrame(0, 4, ColorF(skillColor[type]).setAlpha(alpha[type]));

			// 三角マークの描画
			if (whatSkill[type] != 0)
				TextureAsset(skillType[type] + L"Triangle")
					.draw(755 + (190 * type) - (640 * isLeft), 455, Alpha((int)(255 * alpha[type])));
			if (whatSkill[type] != skillNum[type])
				TextureAsset(skillType[type] + L"Triangle").flip()
					.draw(755 + (190 * type) - (640 * isLeft), 570, Alpha((int)(255 * alpha[type])));
		}
	}
}

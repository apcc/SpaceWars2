#include "SkillSelect.hpp"

#define V80 { 80, 80 }

bool SkillSelect::isLoaded = false;

void SkillSelect::init() {
	Data::LPlayer.initWithoutSkill(Vec2(80, Config::HEIGHT / 2), true);  //円の半径
	Data::RPlayer.initWithoutSkill(Vec2(1200, Config::HEIGHT / 2), false); //WIDTH-円の半径

	if (!isLoaded) {
		for (auto i : step(7)) {
			TextureAsset::Register(L"main"    + Format(i - 1), L"/800" + Format(i));
			TextureAsset::Register(L"sub"     + Format(i - 1), L"/801" + Format(i));
			TextureAsset::Register(L"special" + Format(i - 1), L"/802" + Format(i));
		}
		for (auto i : step(5)) {
			TextureAsset::Register(L"mainBullet"    + Format(i), L"/820" + Format(i));
			TextureAsset::Register(L"subBullet"     + Format(i), L"/821" + Format(i));
			TextureAsset::Register(L"specialBullet" + Format(i), L"/822" + Format(i));
		}
		TextureAsset::Register(L"mainTriangle", L"/8100");
		TextureAsset::Register(L"subTriangle", L"/8101");
		TextureAsset::Register(L"specialTriangle", L"/8102");
		TextureAsset::Register(L"ready", L"/8110");
		isLoaded = true;
	}

	LContinue = false;
	RContinue = false;
}

void SkillSelect::update() {
	changeScene(Debug::InputFnKey(), 250);
	 if (nextStageTime > 100)
	 	changeScene(L"Game", 500);

	if (LContinue && RContinue) ++nextStageTime;
	else nextStageTime = 0;

	if (Data::LKeyBack.repeat(20, true)) LContinue = false;
	if (Data::RKeyBack.repeat(20, true)) RContinue = false;

	if (Data::LKeySelect.repeat(20, true)) LContinue = true;
	if (Data::RKeySelect.repeat(20, true)) RContinue = true;

	if (!LContinue) {
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
	}

	if (!RContinue) {
		switch (Data::RPlayer.skillSelect()) {
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
}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	SmartUI::Get(S32)(L"SkillSelect").drawCenter(40, Color(L"#ffffff"));

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

		if (LContinue) {
			Rect(0, 0, Window::Center().x, Config::HEIGHT)
				.draw(ColorF(L"#00f").setAlpha(0.1));
			TextureAsset(L"ready").drawAt(Window::Center().x / 2, Window::Center().y);
		}
		if (RContinue) {
			Rect(Window::Center().x, 0, Window::Center().x, Config::HEIGHT)
				.draw(ColorF(L"#00f").setAlpha(0.1));
			TextureAsset(L"ready").drawAt(Window::Center().x * 1.5, Window::Center().y);
		}
	}

	Vec2 buttonPos(820, 692);

	buttonPos.x += (int)TextureAsset(L"cross_24").draw(buttonPos).w + 5;
	buttonPos.x += (int)TextureAsset(L"stick_24").draw(buttonPos).w + 6;
	buttonPos.x += (int)CicaR::Get(C12)(L"Skill選択").draw(buttonPos).w + 15;

	buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos).w + 6;
	buttonPos.x += (int)CicaR::Get(C12)(L"Continue").draw(buttonPos).w + 15;

	buttonPos.x += (int)TextureAsset(L"buttonLT_24").draw(buttonPos).w + 3;
	buttonPos.x += (int)TextureAsset(L"buttonRT_24").draw(buttonPos).w + 4;
	buttonPos.x += (int)CicaR::Get(C12)(L"Cancel").draw(buttonPos).w + 15;
}

#include "SkillSelect.hpp"

#define V80 { 80, 80 }

bool SkillSelect::isLoaded = false;

void SkillSelect::init() {

	if (!isLoaded) {
		int i = 0;
		for (int j = -1; j < 6; j++) {
			TextureAsset::Register(L"main" + Format(j), L"/800" + Format(i));
			TextureAsset::Register(L"sub" + Format(j), L"/801" + Format(i));
			TextureAsset::Register(L"special" + Format(j), L"/802" + Format(i));
			++i;
		}
		TextureAsset::Register(L"mainTriangle", L"/8100");
		TextureAsset::Register(L"subTriangle", L"/8101");
		TextureAsset::Register(L"specialTriangle", L"/8102");

		TextReader descReader(L"/7601");

		String str;//毎行用
		int lane = 0;
		while (descReader.readLine(str)) {
			lane++;
			if (lane == 1)continue;
			skillDescriptManager.AddDescript(str);
		}

		isLoaded = true;
	}

	LReady = false;
	RReady = false;
}

void SkillSelect::update() {
	changeScene(Debug::InputFnKey(), 250);
	 if (nextStageTime > 100)
	 	changeScene(L"Game", 500);

	if (LReady && RReady) ++nextStageTime;
	else nextStageTime = 0;

	if (Data::LKeyBack.repeat(20, true)) LReady = false;
	if (Data::RKeyBack.repeat(20, true)) RReady = false;

	if (Data::LKeySelect.repeat(20, true)) LReady = true;
	if (Data::RKeySelect.repeat(20, true)) RReady = true;

	if(!LReady) whatLselecting = Data::LPlayer.skillSelect();
	if(!RReady) whatRselecting = Data::RPlayer.skillSelect();
}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();

	for (int isLeft = 0; isLeft <= 1; isLeft++) { // LPlayer, RPlayer

		Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
		double alpha[3]      = { 0.5, 0.5, 0.5 };
		alpha[(isLeft ? whatLselecting : whatRselecting)] = 1.0;
		String skillType[3]  = { L"main", L"sub", L"special" };
		int    whatSkill[3]  = { PLAYER->whatMainSkill, PLAYER->whatSubSkill, PLAYER->whatSpecialSkill };
		int    skillNum[3]   = { MAIN_NUM - 1, SUB_NUM - 1, SPECIAL_NUM - 1 };
		String skillColor[3] = { L"#7cfc00", L"#4169e1", L"#ffd000" };
		int selectingType = (isLeft ? whatLselecting : whatRselecting);
		SkillDescript descript = skillDescriptManager.skillDescription[selectingType][whatSkill[selectingType]];

		SmartUI::GetFont(S24)(descript.name).draw((!isLeft) * Window::Width() / 2 + 30, 20, Color(L"#ffffff"));

		Rect({290, 90}, 16*19, 9*19).draw(ColorF(L"#dddddd"));

		Vec2 chartCenter = Vec2(150, 175);
		const double chartSize = 85;

		if (selectingType == 0) {
			Quad(
				{ (!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y - chartSize },
				{ (!isLeft) * Window::Width() / 2 + chartCenter.x + chartSize, chartCenter.y },
				{ (!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y + chartSize },
				{ (!isLeft) * Window::Width() / 2 + chartCenter.x - chartSize, chartCenter.y }
			).draw(ColorF(L"#00bfff").setAlpha(0.4));
			Line((!isLeft) * Window::Width() / 2 + chartCenter.x - chartSize, chartCenter.y, (!isLeft) * Window::Width() / 2 + chartCenter.x + chartSize, chartCenter.y).draw();
			Line((!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y - chartSize, (!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y + chartSize).draw();


			LineString(
				{
					{ (!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y - chartSize * descript.status[0] / 10 },
					{ (!isLeft) * Window::Width() / 2 + chartCenter.x + chartSize * descript.status[1] / 10, chartCenter.y },
					{ (!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y + chartSize * descript.status[2] / 10 },
					{ (!isLeft) * Window::Width() / 2 + chartCenter.x - chartSize * descript.status[3] / 10, chartCenter.y },
					{ (!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y - chartSize * descript.status[0] / 10 }
				}
			).draw(5, ColorF(L"#ffffff").setAlpha(0.9));
		}
		else {
			chartCenter += Vec2((!isLeft) * Window::Width() / 2, 0);
			Triangle(chartCenter, chartSize*sqrt(3), 0_deg).draw(ColorF(L"#00bfff").setAlpha(0.4));
			Vec2 posOftriangle[3] = {
				{chartCenter - Vec2(0, chartSize)},
				{chartCenter + Vec2(chartSize, 0).rotated(Pi * 5 / 6)},
				{chartCenter + Vec2(chartSize, 0).rotated(Pi * 1 / 6)},
			};
			for (int i = 0; i < 3; i++) {
				Line(chartCenter, posOftriangle[i]).draw();
			}

			LineString(
				{
					{chartCenter - Vec2(0, chartSize * descript.status[0] / 10)},
					{chartCenter + Vec2(chartSize * descript.status[1] / 10, 0).rotated(Pi * 5 / 6)},
					{chartCenter + Vec2(chartSize * descript.status[2] / 10, 0).rotated(Pi * 1 / 6)},
					{chartCenter - Vec2(0, chartSize * descript.status[0] / 10)}
				}
			).draw(5, ColorF(L"#ffffff").setAlpha(0.9));
		}

		SmartUI::GetFont(S18)(descript.descript).draw((!isLeft) * Window::Width() / 2 + 30, 300, ColorF(L"#ffffff"));

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

		if (LReady) Rect(0, 0, Window::Center().x, Config::HEIGHT).draw(ColorF(L"#f00").setAlpha(0.25));
		if (RReady) Rect(Window::Center().x, 0, Window::Center().x, Config::HEIGHT).draw(ColorF(L"#f00").setAlpha(0.25));
	}

	Vec2 buttonPos(820, 692);

	buttonPos.x += (int)TextureAsset(L"cross_24").draw(buttonPos).w + 5;
	buttonPos.x += (int)TextureAsset(L"stick_24").draw(buttonPos).w + 6;
	buttonPos.x += (int)CicaR::GetFont(C12)(L"Skill選択").draw(buttonPos).w + 15;

	buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos).w + 6;
	buttonPos.x += (int)CicaR::GetFont(C12)(L"Continue").draw(buttonPos).w + 15;

	buttonPos.x += (int)TextureAsset(L"buttonLT_24").draw(buttonPos).w + 3;
	buttonPos.x += (int)TextureAsset(L"buttonRT_24").draw(buttonPos).w + 4;
	buttonPos.x += (int)CicaR::GetFont(C12)(L"Cancel").draw(buttonPos).w + 15;
}

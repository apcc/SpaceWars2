#include "SkillSelect.hpp"

#define V80 { 80, 80 }

SkillDescriptManager SkillSelect::skillDescriptManager;

const Array<String> mainSkillSound = {
	L"shot", L"grenade1", L"grenade2", L"laser1", L"laser2", L"reflection", L"flame"
};
const Array<String> subSkillSound = {
	L"jump", L"shield", L"missile", L"bomb"
};
const Array<String> specialSkillSound = {
	L"JT", L"LO", L"SP", L"IR"
};

bool SkillSelect::isLoaded = false;

void SkillSelect::init() {
	movetoUp[0][0] = movetoUp[1][1] = true;
	movetoUp[0][1] = movetoUp[1][0] = true;

	playerPos[1][0] = playerPos[0][1] = Vec2(80, Window::Height() / 2);
	playerPos[1][1] = playerPos[0][0] = Vec2(1200, Window::Height() / 2);

	Data::LPlayer.init(Vec2(80, Config::HEIGHT / 2), true);  //円の半径
	Data::RPlayer.init(Vec2(1200, Config::HEIGHT / 2), false); //WIDTH-円の半径

	if (!isLoaded) {
		for (auto i : step(7)) {
			TextureAsset::Register(L"main"    + Format(i - 1), L"/800" + Format(i));
			TextureAsset::Register(L"sub"     + Format(i - 1), L"/801" + Format(i));
			TextureAsset::Register(L"special" + Format(i - 1), L"/802" + Format(i));
		}

		TextureAsset::Register(L"l-player", L"/7500");
		TextureAsset::Register(L"r-player", L"/7501");

		const Array<String> sound[3] = { mainSkillSound, subSkillSound, specialSkillSound };
		bool isSoundLoaded[3] = { false, false, false };
		for (int i = 0; i < 3; i++) {
			if (!isSoundLoaded[i]) {
				int j = 0;
				for (const auto& name : sound[i]) {
					SoundAsset::Register(name, L"/82" + Format(i) + Format(j));
					++j;
				}
				isSoundLoaded[i] = true;
			}
		}

		TextReader descReader(L"/8300");

		String str;//毎行用
		int lane = 0;
		while (descReader.readLine(str)) {
			lane++;
			if (lane == 1)continue;
			skillDescriptManager.AddDescript(str);
		}

		for (auto i : step(5)) {
			TextureAsset::Register(L"mainBullet"    + Format(i), L"/810" + Format(i));
			TextureAsset::Register(L"subBullet"     + Format(i), L"/811" + Format(i));
			TextureAsset::Register(L"specialBullet" + Format(i), L"/812" + Format(i));
		}
		TextureAsset::Register(L"ready"          , L"/7400");
		TextureAsset::Register(L"mainTriangle"   , L"/7410");
		TextureAsset::Register(L"subTriangle"    , L"/7411");
		TextureAsset::Register(L"specialTriangle", L"/7412");
		isLoaded = true;
	}

	bulletArea[0] = Rect({ 290 + Window::Size().x / 2 , 90 }, 16 * 19, 9 * 19); //Right
	bulletArea[1] = Rect({ 290 , 90 }, 16 * 19, 9 * 19); //Left
	shrinkRate = (double)bulletArea[0].w / Window::Width();
	LReady = false;
	RReady = false;
}

void SkillSelect::update() {
	changeScene(Debug::InputFnKey(), 100);
	 if (nextStageTime > 100)
	 	changeScene(L"Game", 500);

	if (LReady && RReady) ++nextStageTime;
	else nextStageTime = 0;

	if (Data::LKeySelect.repeat(20, true) && !LReady) {
		LReady = true;
		SoundAsset(L"click1").playMulti();
	}
	if (Data::RKeySelect.repeat(20, true) && !RReady) {
		RReady = true;
		SoundAsset(L"click1").playMulti();
	}
	if (Data::LKeySelect.repeat(20, true)) LReady = true;
	if (Data::RKeySelect.repeat(20, true)) RReady = true;

	// 機体の処理
	for (int isLeft = 0; isLeft < 2; isLeft++) {
		for (int i = 0; i < 2; i++) {
			if (i == 1 && judgementTime[isLeft] != 0) continue;
			if (movetoUp[isLeft][i]) {
				playerPos[isLeft][i] -= Vec2(0, 3);
				if (playerPos[isLeft][i].y < Window::Height()/5) {
					movetoUp[isLeft][i] = false;
				}
			}
			else {
				playerPos[isLeft][i] += Vec2(0, 3);
				if (playerPos[isLeft][i].y > Window::Height()*4/5) {
					movetoUp[isLeft][i] = true;
				}
			}
		}
	}

	for(int isLeft = 0; isLeft < 2; isLeft++){
		Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);

		if(isLeft ? !LReady : !RReady){
			if(PLAYER->skillSelect())	goingTowhiteout[isLeft] = true;
		}

		if (judgementTime[isLeft] == 0) {
			for (auto itr = bullets[isLeft].begin(); itr != bullets[isLeft].end();) {
				Vec2 ppos = playerPos[isLeft][0];
				Vec2 opps = playerPos[isLeft][1];
				if ((**itr).update(ppos, opps)) {
					delete* itr;
					itr = bullets[isLeft].erase(itr);
				}
				else {
					++itr;
				}
			}
		}
		else {
			if (judgementTime[isLeft] % 10 == 0) {
				Bullet* bullet = new Shot(playerPos[isLeft][0], isLeft);
				bullet->Shrink(bulletArea[isLeft]);
				bullets[isLeft].push_back(bullet);
			}
			judgementTime[isLeft]--;
		}
		if(goingTowhiteout[isLeft]){
			whiteOutTime[isLeft]++;
			if(whiteOutTime[isLeft]>=WHITEOUT_TIME){
				goingTowhiteout[isLeft] = false;
				skillsDisplayed[isLeft][0] = PLAYER->whatMainSkill;
				skillsDisplayed[isLeft][1] = PLAYER->whatSubSkill;
				skillsDisplayed[isLeft][2] = PLAYER->whatSpecialSkill;
				skillTypeDisplayed[isLeft] = PLAYER->selectedType;
				goingTowhiteout[isLeft] = false;

				for(auto itr : bullets[isLeft]) {
					delete itr;
				}
				bullets[isLeft].clear();
				coolDownTime[isLeft] = 0;

				movetoUp[0][0] = movetoUp[1][1] = true;
				movetoUp[0][1] = movetoUp[1][0] = true;

				playerPos[1][0] = playerPos[0][1] = Vec2(80, Window::Height() / 2);
				playerPos[1][1] = playerPos[0][0] = Vec2(1200, Window::Height() / 2);
			}
		}else{
			if(whiteOutTime[isLeft]>0)whiteOutTime[isLeft]--;
		}
		if (coolDownTime[isLeft] == 0) {
			Vec2 ppos = playerPos[isLeft][0];
			Bullet* bullet;
			switch (skillTypeDisplayed[isLeft]) {
			case 0://Main
				switch (skillsDisplayed[isLeft][0]) {
				case SHOT://Shot
					bullet = new Shot(ppos, isLeft);
					coolDownTime[isLeft] = 6;
					break;
				case GRENADE:
					bullet = new Grenade(ppos, isLeft);
					coolDownTime[isLeft] = 20;
					break;
				case LASER:
					bullet = new VLaser(ppos, isLeft);
					coolDownTime[isLeft]++;
					break;
				case REFLECTION:
					bullet = new Reflection(ppos, isLeft);
					coolDownTime[isLeft] = 30;
					break;
				case FLAME:
					bullet = new Flame(ppos, isLeft);
					coolDownTime[isLeft] = 20;
					break;
				default: bullet = new Shot(ppos, isLeft); break;
				}
				break;
			case 1://Sub
				switch (skillsDisplayed[isLeft][1]) {
				case JUMP:
					if (movetoUp[isLeft][0]) playerPos[isLeft][0].y -= 160;
					else playerPos[isLeft][0].y += 160;
					coolDownTime[isLeft] = 80;
					bullet = new Jump(ppos, isLeft);
					break;
				case SHIELD:
					bullet = new Shield(ppos, isLeft); break;
				case MISSILE:
					bullet = new Missile(ppos, isLeft);
					coolDownTime[isLeft] = 40;
					break;
				case BOMB:
					for(int i = 0; i < 3; i++){
						Bullet* subBul = new Bomb(ppos, isLeft);
						subBul->Shrink(bulletArea[isLeft]);
						bullets[isLeft].push_back(subBul);
					}
					bullet = new Bomb(ppos, isLeft);
					coolDownTime[isLeft] = 240;
					break;
				default: bullet = new Shot(ppos, isLeft); break;
				}
				break;
			case 2://Special
				switch (skillsDisplayed[isLeft][2]) {
				//case LOCK_ON:	
				//case SUMMON_PARTNER:
				case JUDGMENT_TIME:
					judgementTime[isLeft] = 120;
					coolDownTime[isLeft] = 300;
					bullet = new Shot(ppos, isLeft);
					break;
				//case INVERSION_RECOVERY:
				default:
					bullet = new Shot(ppos, isLeft); break;
				}
				break;
			default:
				bullet = new Shot(ppos, isLeft); break;
			}
			bullet->Shrink(bulletArea[isLeft]);
			bullets[isLeft].push_back(bullet);
		}
		coolDownTime[isLeft]--;
	}
}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();

	for (int isLeft = 0; isLeft <= 1; isLeft++) { // LPlayer, RPlayer

		Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
		int selectingType = PLAYER->selectedType;
		double alpha[3]      = { 0.5, 0.5, 0.5 };
		alpha[selectingType] = 1.0;
		String skillType[3]  = { L"main", L"sub", L"special" };
		int    whatSkill[3]  = { PLAYER->whatMainSkill, PLAYER->whatSubSkill, PLAYER->whatSpecialSkill };
		int    skillNum[3]   = { MAIN_NUM - 1, SUB_NUM - 1, SPECIAL_NUM - 1 };
		String skillColor[3] = { L"#7cfc00", L"#4169e1", L"#ffd000" };
		String skillBackColor[3] = { L"#dfd", L"#ddf", L"#fed" };

		SkillDescript descript = skillDescriptManager.skillDescription[skillTypeDisplayed[isLeft]][skillsDisplayed[isLeft][skillTypeDisplayed[isLeft]]];

		SmartUI::Get(S24)(descript.name).draw({ (!isLeft) * Window::Width() / 2 + 30, 20 }, Color(L"#ffffff"));

		Rect({290 + (!isLeft ? Window::Size().x : 0)/2 , 90}, 16*19, 9*19).draw(ColorF(L"#0000dd"));

		Vec2 chartCenter = Vec2(150, 175);
		const double chartSize = 85;

		if (skillTypeDisplayed[isLeft] == 0) {
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

		SmartUI::Get(S18)(descript.descript).draw({ (!isLeft) * Window::Width() / 2 + 30, 300 }, ColorF(L"#ffffff"));

		Rect({ 15 + (!isLeft) * Window::Width() / 2, 10 }, { 610 + (!isLeft) * Window::Width() / 2, 290 }).draw(ColorF(L"#000000").setAlpha((double)whiteOutTime[isLeft] / WHITEOUT_TIME));


		for (int type = 0; type < 3; type++) { // mainSkill, subSkill, specialSkill

			// 選択中のskillの枠
			Rect(720 + (190 * type) - (640 * isLeft), 470, 100).draw(ColorF(skillBackColor[type]).setAlpha(0.7)).drawFrame(0, 4, ColorF(skillColor[type]).setAlpha(alpha[type]));

			// skillIconの描画
			for (int i = -1; i <= 1; i++) { // -1:前 0:選択中 1:後
				if (i) {
					if(0<=whatSkill[type] + i && whatSkill[type] + i<=skillNum[type])
					Rect({ 770 + (190 * type) - (640 * isLeft) - 40, 520 + 110 * i - 40 }, V80)
						.draw(ColorF(skillBackColor[type]).setAlpha(0.7));
					TextureAsset(skillType[type] + Format((int)whatSkill[type] + i)).resize(V80)
						.drawAt(770 + (190 * type) - (640 * isLeft), 520 + 110 * i);
				}
				else {
					Rect(720 + (190 * type) - (640 * isLeft), 470, 100)
						.draw(ColorF(skillBackColor[type]).setAlpha(0.7))
						.drawFrame(0, 4, ColorF(skillColor[type]).setAlpha(alpha[type]));
					TextureAsset(skillType[type] + Format((int)whatSkill[type]))
						.drawAt(770 + (190 * type) - (640 * isLeft), 520);
				}
			}

			// 三角マークの描画
			if (whatSkill[type] != 0)
				TextureAsset(skillType[type] + L"Triangle")
					.draw(755 + (190 * type) - (640 * isLeft), 455, Alpha((int)(255 * alpha[type])));
			if (whatSkill[type] != skillNum[type])
				TextureAsset(skillType[type] + L"Triangle").flip()
					.draw(755 + (190 * type) - (640 * isLeft), 570, Alpha((int)(255 * alpha[type])));

		}

		for (auto itr : bullets[isLeft]) {
			itr->draw();
		}

		for (int i = 0; i < 2; i++) {
			String text = isLeft ^ i ? L"l-player" : L"r-player";
			TextureAsset(text).resize({ 40, 40 }).drawAt(ShrinkVec2(playerPos[isLeft][i], isLeft));

		}
		if (judgementTime[isLeft]) {
			Rect(bulletArea[isLeft]).draw(ColorF(L"#336699").setAlpha((0.6 - (120 - judgementTime[isLeft]) * (120 - judgementTime[isLeft]) / 28800.0)));

		}
	}

	if (LReady) {
		Rect(0, 0, Window::Center().x, Config::HEIGHT)
			.draw(ColorF(L"#00f").setAlpha(0.1));
		TextureAsset(L"ready").drawAt(Window::Center().x / 2, Window::Center().y);
	}
	if (RReady) {
		Rect(Window::Center().x, 0, Window::Center().x, Config::HEIGHT)
			.draw(ColorF(L"#00f").setAlpha(0.1));
		TextureAsset(L"ready").drawAt(Window::Center().x * 1.5, Window::Center().y);
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

Vec2 SkillSelect::ShrinkVec2(Vec2 _d, int isLeft) const {
	RectF screen(0, 0, Window::Width(), Window::Height());
	Vec2 dis = _d.asPoint() - screen.center;
	_d = dis * shrinkRate + bulletArea[isLeft].center;
	return _d;
}

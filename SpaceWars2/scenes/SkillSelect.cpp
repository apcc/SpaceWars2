#include "SkillSelect.hpp"

#define V80 { 80, 80 }

SkillDescriptManager SkillSelect::skillDescriptionManager;

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
	// スキル説明動画回り
	moveToUp[0][0] = moveToUp[1][1] = true;
	moveToUp[0][1] = moveToUp[1][0] = false;

	playerPos[1][0] = playerPos[0][1] = Vec2(140, Window::Height() / 2);
	playerPos[1][1] = playerPos[0][0] = Vec2(1100, Window::Height() / 2);

	bulletArea[0] = Rect({ 290 + Window::Size().x / 2 , 90 }, 16 * 19, 9 * 19); //Right
	bulletArea[1] = Rect({ 290 , 90 }, 16 * 19, 9 * 19); //Left
	shrinkRate = (double)bulletArea[0].w / Window::Width();
	LReady = false;
	RReady = false;

	// Player init
	Data::LPlayer.init(Vec2(140, Config::HEIGHT / 2), true);  //円の半径
	Data::RPlayer.init(Vec2(1100, Config::HEIGHT / 2), false); //WIDTH-円の半径

	// Dataの読み込み
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
			skillDescriptionManager.AddDescript(str);
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

	Rect rect[4];
	Image img[4];
	String strings[4] = { L"ダメージ", L"発射間隔", L"使いやすさ", L"弾速" };
	for (int i = 0; i < 4; i++) {
		rect[i] = SmartUI::Get(S12).region(strings[i]);
		img[i].resize(rect[i].size);
		SmartUI::Get(S12).overwrite(img[i], strings[i], { 0, 0 }, Color(L"#fff"));
		rotatedDescription[i] = Texture(img[i]);
	}
}

void SkillSelect::update() {
	// シーン変更の操作
	changeScene(Debug::InputFnKey(), 100);
	 if (nextStageTime > 100)
	 	changeScene(L"Game", 500);

	if (LReady && RReady) ++nextStageTime;
	else nextStageTime = 0;

	if (Data::LPlayer.selectedType == 2 && !LReady && Data::LKeySelect.repeat(20, true)) {
		LReady = true;
		SoundAsset(L"click1").setVolume(Config::MASTER_VOLUME * Config::CURSOR_VOLUME);
		SoundAsset(L"click1").playMulti();
	}
	if (Data::RPlayer.selectedType == 2 && !RReady && Data::RKeySelect.repeat(20, true)) {
		RReady = true;
		SoundAsset(L"click1").setVolume(Config::MASTER_VOLUME * Config::CURSOR_VOLUME);
		SoundAsset(L"click1").playMulti();
	}
	if (LReady && Data::LKeyCancel.repeat(20, true)) LReady = false;
	if (RReady && Data::RKeyCancel.repeat(20, true)) RReady = false;

	// 機体の処理
	for (int isLeft = 0; isLeft < 2; isLeft++) {
		for (int i = 0; i < 2; i++) {
			if (i == 1 && judgmentTime[isLeft] != 0) continue;
			if (moveToUp[isLeft][i]) {
				playerPos[isLeft][i] -= Vec2(0, 3);
				if (playerPos[isLeft][i].y < (int)(Window::Height() / 5)) {
					moveToUp[isLeft][i] = false;
					playerPos[isLeft][i].y = (int)(Window::Height() / 5);
				}
			}
			else {
				playerPos[isLeft][i] += Vec2(0, 3);
				if (playerPos[isLeft][i].y > (int)(Window::Height() * 4 / 5)) {
					moveToUp[isLeft][i] = true;
					playerPos[isLeft][i].y = (int)(Window::Height() * 4 / 5);
				}
			}
		}
	}

	for(int player = 0; player < 2; player++){
		bool isLeft = !!player;

		Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);

		// Skill選択操作
		if(isLeft ? !LReady : !RReady){
			if(PLAYER->skillSelect())	goingToBlackOut[isLeft] = true;
		}

		// 説明動画: 弾
		if (judgmentTime[isLeft] == 0) {
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
		} else {
			if (judgmentTime[isLeft] % 10 == 0) {
				Bullet* bullet = new Shot(playerPos[isLeft][0], isLeft);
				bullet->shrink(bulletArea[isLeft]);
				bullets[isLeft].push_back(bullet);
			}
			judgmentTime[isLeft]--;
		}

		// INVERSION_RECOVERY
		if (skillTypeDisplayed[isLeft] == 2 && skillsDisplayed[isLeft][2] == 3) {
			if (timerCount[isLeft] == 0) {
				timerCount[isLeft] = 300;
				playerHP[isLeft] = 600;
				coolDownTime[isLeft] = 0;
				isLeft ? playerPos[1][0] : playerPos[0][1] = Vec2(140, Window::Height() / 2);
				isLeft ? playerPos[1][1] : playerPos[0][0] = Vec2(1100, Window::Height() / 2);
				moveToUp[isLeft][0] = true; moveToUp[isLeft][1] = false;
				for (auto itr : bullets[isLeft]) {
					delete itr;
				}
				bullets[isLeft].clear();
			}
			else if (timerCount[isLeft] < 0) {
				// 虚無時間
				timerCount[isLeft]++;
			}
			else {
				timerCount[isLeft]--;
				if (timerCount[isLeft] < 120) {
					if (playerHP[isLeft] < 600) {
						playerHP[isLeft] += 3;
					}
					else {
						timerCount[isLeft] *= -1;
					}
				}
			}
		}

		// 説明動画: 弾の当たり判定

		for (auto b : bullets[isLeft]) {
			int damage = b->getDamage(getHitCircle(shrinkVec2(playerPos[isLeft][!(b->isLeft^isLeft)], isLeft), isLeft));
			playerHP[isLeft] -= !(b->isLeft^isLeft) ? 0 : (damage?40:0);
		}

		// 上半分のブラックアウト処理
		if(goingToBlackOut[isLeft]){
			blackOutTime[isLeft]++;
			if(blackOutTime[isLeft]>=BLACKOUT_TIME){
				// 真っ暗になったタイミング = 表示させるスキルを切り替えるタイミング
				goingToBlackOut[isLeft] = false;
				skillsDisplayed[isLeft][0] = PLAYER->whatMainSkill;
				skillsDisplayed[isLeft][1] = PLAYER->whatSubSkill;
				skillsDisplayed[isLeft][2] = PLAYER->whatSpecialSkill;
				skillTypeDisplayed[isLeft] = PLAYER->selectedType;
				goingToBlackOut[isLeft] = false;

				for(auto itr : bullets[isLeft]) {
					delete itr;
				}
				bullets[isLeft].clear();
				coolDownTime[isLeft] = 0;

				moveToUp[isLeft][0] = true; moveToUp[isLeft][1] = false;
				judgmentTime[isLeft] = 0;
				timerCount[isLeft] = 0;
				isLeft ? playerPos[1][0] : playerPos[0][1] = Vec2(140, Window::Height() / 2);
				isLeft ? playerPos[1][1] : playerPos[0][0] = Vec2(1100, Window::Height() / 2);
			}
		}else{
			if(blackOutTime[isLeft]>0)blackOutTime[isLeft]--;
		}

		// 動画: 各スキルの発動
		if (coolDownTime[isLeft] == 0) {
			Vec2 ppos = playerPos[isLeft][0];
			Vec2 opps = playerPos[isLeft][1];
			Bullet* bullet;
			switch (skillTypeDisplayed[isLeft]) {
			case 0: { // Main
				switch (skillsDisplayed[isLeft][0]) {
				case SHOT: {
					bullet = new Shot(ppos, isLeft);
					coolDownTime[isLeft] = 6;
					break;
				}
				case GRENADE: {
					bullet = new Grenade(ppos, isLeft);
					coolDownTime[isLeft] = 20;
					break;
				}
				case LASER: {
					bullet = new VLaser(ppos, isLeft);
					coolDownTime[isLeft]++;
					break;
				}
				case REFLECTION: {
					bullet = new Reflection(ppos, isLeft);
					coolDownTime[isLeft] = 30;
					break;
				}
				case FLAME: {
					bullet = new Flame(ppos, isLeft);
					coolDownTime[isLeft] = 20;
					break;
				}
				default:
					bullet = new Shot(ppos, isLeft); break;
				}
				break;
			}

			case 1: { // Sub
				switch (skillsDisplayed[isLeft][1]) {
				case JUMP: {
					if (moveToUp[isLeft][0]) {
						playerPos[isLeft][0].y -= 160;
						if (playerPos[isLeft][0].y < Window::Height() / 5) {
							moveToUp[isLeft][0] = false;
							playerPos[isLeft][0].y = Window::Height() / 5;
						}
					}
					else {
						playerPos[isLeft][0].y += 160;
						if (playerPos[isLeft][0].y > Window::Height() * 4 / 5) {
							moveToUp[isLeft][0] = true;
							playerPos[isLeft][0].y = Window::Height() * 4 / 5;
						}
					}

					coolDownTime[isLeft] = 80;
					bullet = new Jump(ppos, isLeft);
					break;
				}

				case SHIELD: {
					if (bullets[isLeft].empty()) bullet = new Shield(ppos, isLeft);
					else bullet = new Shot(opps, !isLeft);
					coolDownTime[isLeft] = 6;
					break;
				}

				case MISSILE: {
					bullet = new Missile(ppos, isLeft);
					coolDownTime[isLeft] = 40;
					break;
				}

				case BOMB: {
					for (int i = 0; i < 3; i++) {
						Bullet* subBul = new Bomb(ppos, isLeft);
						subBul->shrink(bulletArea[isLeft]);
						bullets[isLeft].push_back(subBul);
					}
					bullet = new Bomb(ppos, isLeft);
					coolDownTime[isLeft] = 240;
					break;
				}

				default:
					bullet = new Shot(ppos, isLeft); break;
				}
				break;
			}

			case 2: { //Special
				switch (skillsDisplayed[isLeft][2]) {
				case LOCK_ON: {
					for (int i = 0; i < 3; i++) {
						bullet = new LockOn(ppos, isLeft, 30 * i);
						if (i == 2)continue;
						bullet->shrink(bulletArea[isLeft]);
						bullets[isLeft].push_back(bullet);
					}
					coolDownTime[isLeft] = 240;
					break;
				}

				case SUMMON_PARTNER: {
					bullet = new SummonPartner(ppos, isLeft);
					coolDownTime[isLeft] = 150;
					break;
				}

				case JUDGMENT_TIME: {
					judgmentTime[isLeft] = 120;
					coolDownTime[isLeft] = 300;
					bullet = new Shot(ppos, isLeft);
					break;
				}

				case INVERSION_RECOVERY: {
					bullet = new Shot(opps, !isLeft);
					coolDownTime[isLeft] = 6;
					break;
				}

				default:
					bullet = new Shot(ppos, isLeft); break;
				}
				break;
			default:
				bullet = new Shot(ppos, isLeft); break;
			}
			}
			bullet->shrink(bulletArea[isLeft]);
			bullets[isLeft].push_back(bullet);
		}
		coolDownTime[isLeft]--;
	}
}

void SkillSelect::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();

	for (int isLeft = 0; isLeft <= 1; isLeft++) { // LPlayer, RPlayer

		Player* PLAYER           = &(isLeft ? Data::LPlayer : Data::RPlayer);
		int selectingType        = PLAYER->selectedType;
		double alpha[3]          = { 0.5, 0.5, 0.5 };
		alpha[selectingType]     = 1.0;
		String skillType[3]      = { L"main", L"sub", L"special" };
		int    whatSkill[3]      = { PLAYER->whatMainSkill, PLAYER->whatSubSkill, PLAYER->whatSpecialSkill };
		int    skillNum[3]       = { MAIN_NUM - 1, SUB_NUM - 1, SPECIAL_NUM - 1 };
		String skillColor[3]     = { L"#7cfc00", L"#4169e1", L"#ffd000" };
		String skillBackColor[3] = { L"#dfd", L"#ddf", L"#fed" };

		SkillDescript description = skillDescriptionManager.skillDescription[skillTypeDisplayed[isLeft]][skillsDisplayed[isLeft][skillTypeDisplayed[isLeft]]];

		// JudgmentTimeの凍結背景描写
		if (judgmentTime[isLeft]) {
			Rect(bulletArea[isLeft]).draw(ColorF(L"#336699").setAlpha((0.6 - (120 - judgmentTime[isLeft]) * (120 - judgmentTime[isLeft]) / 28800.0)));
		}

		// Skillの名前
		SmartUI::Get(S24)(description.name).draw({ (!isLeft) * Window::Width() / 2 + 30, 20 }, Color(L"#fff"));

		// 説明文
		SmartUI::Get(S18)(description.descript).draw({ (!isLeft) * Window::Width() / 2 + 30, 300 }, ColorF(L"#fff"));


		// 動画エリアの背景
		bulletArea[isLeft].drawFrame(0, 4);
		TextureAsset(L"background").resize(bulletArea[isLeft].w, bulletArea[isLeft].h).drawAt(bulletArea[isLeft].center);

		// グラフ描画
		Vec2 chartCenter = Vec2(150, 175);
		const double chartSize = 85;

		if (skillTypeDisplayed[isLeft] == 0) {
			Array<Vec2> chartPos = {
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y - chartSize },
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x + chartSize, chartCenter.y },
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y + chartSize },
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x - chartSize, chartCenter.y }
			};
			Quad(chartPos[0], chartPos[1], chartPos[2], chartPos[3]).draw(ColorF(L"#00bfff").setAlpha(0.4));
			Line(
				(double)(!isLeft) * Window::Width() / 2 + chartCenter.x - chartSize,
				chartCenter.y,
				(double)(!isLeft) * Window::Width() / 2 + chartCenter.x + chartSize,
				chartCenter.y
			).draw();
			Line(
				(double)(!isLeft) * Window::Width() / 2 + chartCenter.x,
				chartCenter.y - chartSize,
				(double)(!isLeft) * Window::Width() / 2 + chartCenter.x,
				chartCenter.y + chartSize
			).draw();


			Array<Vec2> linePos = {
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y - chartSize * description.status[0] / 10 },
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x + chartSize * description.status[1] / 10, chartCenter.y },
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y + chartSize * description.status[2] / 10 },
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x - chartSize * description.status[3] / 10, chartCenter.y },
				{ (double)(!isLeft) * Window::Width() / 2 + chartCenter.x, chartCenter.y - chartSize * description.status[0] / 10 }
			};
			LineString(linePos).draw(5, ColorF(L"#fff").setAlpha(0.9));
			// stats1

			Vec2 data[4] = { {-30,15}, {-15,-30}, {35,-20}, {5,20} };
			for (int i = 0; i < 4; i++) {
				rotatedDescription[i].rotate(i%2 ? Pi/4 : -Pi/4).drawAt(Vec2(chartPos[i]) + data[i]);
			}
		}
		else {
			chartCenter += Vec2((!isLeft) * Window::Width() / 2, 0);
			Triangle(chartCenter, chartSize*sqrt(3), 0_deg).draw(ColorF(L"#00bfff").setAlpha(0.4));
			Vec2 posTriangle[3] = {
				{chartCenter - Vec2(0, chartSize)},
				{chartCenter + Vec2(chartSize, 0).rotated(Pi * 5 / 6)},
				{chartCenter + Vec2(chartSize, 0).rotated(Pi * 1 / 6)},
			};
			String descriptionStr[3] = {L"瞬間ダメージ", L"クールダウン", L"扱いやすさ"};
			Vec2 data[3] = { {0,-10}, {0,15}, {0,15} };
			for (int i = 0; i < 3; i++) {
				Line(chartCenter, posTriangle[i]).draw();
				SmartUI::Get(S12)(descriptionStr[i]).drawAt( Point(posTriangle[i].x, posTriangle[i].y) +data[i]);
			}

			LineString(
				{
					{chartCenter - Vec2(0, chartSize * description.status[0] / 10)},
					{chartCenter + Vec2(chartSize * description.status[1] / 10, 0).rotated(Pi * 5 / 6)},
					{chartCenter + Vec2(chartSize * description.status[2] / 10, 0).rotated(Pi * 1 / 6)},
					{chartCenter - Vec2(0, chartSize * description.status[0] / 10)}
				}
			).draw(5, ColorF(L"#fff").setAlpha(0.9));
		}

		// ブラックアウト処理
		Rect({ 15 + (!isLeft) * Window::Width() / 2, 10 }, { 610 + (!isLeft) * Window::Width() / 2, 290 })
			.draw(ColorF(L"#000").setAlpha((double)blackOutTime[isLeft] / BLACKOUT_TIME));


		for (int type = 0; type < 3; type++) { // mainSkill, subSkill, specialSkill

			// 選択中のskillの枠
			Rect(720 + (190 * type) - (640 * isLeft), 470, 100).draw(ColorF(skillBackColor[type]).setAlpha(0.7))
				.drawFrame(0, 4, ColorF(skillColor[type]).setAlpha(alpha[type]));

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

		// 弾描画
		for (auto itr : bullets[isLeft]) {
			itr->draw();
		}

		// 機体描画
		for (int i = 0; i < 2; i++) {
			String text = isLeft ^ i ? L"l-player" : L"r-player";
			TextureAsset(text).resize({ 40, 40 }).drawAt(shrinkVec2(playerPos[isLeft][i], isLeft));
		}

		if (skillTypeDisplayed[isLeft] == 2 && skillsDisplayed[isLeft][2] == 3)
			drawHPGauge(!!isLeft, playerHP[isLeft]);
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

Vec2 SkillSelect::shrinkVec2(Vec2 _d, int isLeft) const {
	RectF screen(0, 0, Window::Width(), Window::Height());
	Vec2 dis = _d.asPoint() - screen.center;
	_d = dis * shrinkRate + bulletArea[isLeft].center;
	return _d;
}


void SkillSelect::drawHPGauge(bool _isLeft, int HP) const {
	Rect area = bulletArea[_isLeft];
	int height = (int)(60 * shrinkRate);
	Rect(area.x, area.y, area.w, height).draw(Color(L"#f99"));
	Rect(area.x, area.y, area.w * HP / 1000, height).draw(Color(L"#f11"));
}

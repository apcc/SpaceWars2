#include "Game.hpp"
#include "../fontPlus/FontP.hpp"

#define ROUND_DOWN(x, divisor)	((x - x % divisor) / divisor)
#define ROUND_UP(x, divisor)	(ROUND_DOWN(x, divisor) + (x % divisor ? 1 : 0))

const Array<String> mainSkillSound = {
	L"shot", L"grenade1", L"grenade2", L"laser1", L"laser2", L"reflection", L"flame"
};
const Array<String> subSkillSound = {
	L"jump", L"shield", L"missile", L"bomb"
};
const Array<String> specialSkillSound = {
	L"JT", L"LO", L"SP", L"IR"
};


void Game::init() {}

void Game::update() {
	changeScene(Debug::InputFnKey(), 100);

#	ifdef _DEBUG
	if (Input::KeyF5.pressed) status = COUNT_DOWN_INIT;
	if (Input::KeyF6.pressed) status = GAME_INIT;
	if (Input::KeyF7.pressed) status = FINISH_INIT;
#	endif

	switch(status) {
		case COUNT_DOWN_INIT: {
			countDown.start();

			status = COUNT_DOWN;
		}

		case COUNT_DOWN: {
			if (countDown.s() == 3) {
				status = GAME_INIT;
				return;
			}
			// 疑似for
			int i = countDown.s();

			switch(countDown.s()) {
			case 0:
				if (!isLoaded[i]) {
					TextureAsset::Register(L"l-player", L"/7500");
					TextureAsset::Register(L"r-player", L"/7501");
					isLoaded[i] = true;
				}
				break;

			case 1:
				if (!isLoaded[i]) {
					TextureAsset::Register(L"fire", L"/7510");
					TextureAsset::Register(L"stopwatch-frame", L"/7520");
					isLoaded[i] = true;
				}
				break;

			case 2:
				if (!isLoaded[i]) {
					TextureAsset::Register(L"github-light", L"/7600");
					SoundAsset::Register(L"chargeFull", L"/9000");
					isLoaded[i] = true;
				}
				break;

			default:
				break;
			}

			break;
		}

		case GAME_INIT: {
			countDown.reset();
			stopwatch.start();

			if (!TextureAsset::IsRegistered(L"github-light")) {
				status = COUNT_DOWN_INIT;
				return;
			}

			status = GAME;
		}

		case GAME: {
			Data::LPlayer.update(bullets);
			Data::RPlayer.update(bullets);

			if (!Player::inJudgmentTime) {
				for (auto itr = bullets.begin(); itr != bullets.end();) {
					Vec2 myPos = ((**itr).isLeft ? Data::LPlayer : Data::RPlayer).circle().center;
					Vec2 oppPos = ((**itr).isLeft ? Data::RPlayer : Data::LPlayer).circle().center;

					if ((**itr).update(myPos, oppPos)) {
						delete* itr;
						itr = bullets.erase(itr);
					}
					else {
						++itr;
					}
				}
			}

			if (Data::LPlayer.isHPRunOut() || Data::RPlayer.isHPRunOut())
				status = FINISH_INIT;

			break;
		}

		case FINISH_INIT: {
			if (!Data::LPlayer.isHPRunOut() || !Data::RPlayer.isHPRunOut()) {
				status = GAME_INIT;
				return;
			}

			stopwatch.pause();

			double x = 0;
			for (auto HP : Data::LPlayer.HPLog) {
				LHPGraph.push_back({ x, 100 - HP / 10.0 });
				x += 250.0 / Data::LPlayer.HPLog.size();
			}
			x = 0;
			for (auto HP : Data::RPlayer.HPLog) {
				RHPGraph.push_back({ x, 100 - HP / 10.0 });
				x += 250.0 / Data::RPlayer.HPLog.size();
			}
			
			status = FINISH;
		}

		case FINISH: {
			if (Data::KeyEnter.repeat(20))
				changeScene(L"Ending", 500);

			bool sound = true;

			if (Data::KeyDown.repeat(10, true))
				++selecting;
			else if (Data::KeyUp.repeat(10, true))
				--selecting;
			else
				sound = false;
			selecting = Clamp(selecting, 0, 2);
			if (sound)
				SoundAsset(L"cursor1").playMulti();

			if (Data::KeyEnter.repeat(0, true)){
				SoundAsset(L"click2").playMulti();
				switch (selecting) {
				case 0: 
					changeScene(L"SkillSelect", 500);
					break;
				case 1: 
					changeScene(L"Title", 500);
					break;
				case 2:
					System::Exit();
					break;
				default: break;
				}
			}

			break;
		}
	}
}

void Game::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();

	if (status == GAME || status == FINISH) {
		for (auto bul : bullets) {
			bul->draw();
		}

		Data::LPlayer.drawShip();
		Data::RPlayer.drawShip();

		Line(Window::Center().x, 0, Window::Center().x, Config::HEIGHT).draw(3, ColorF(L"#fff").setAlpha(0.8));

		// HP gauge
		drawHPGauge(true);
		drawHPGauge(false);

		// temperature gauge
		drawTemperatureGauge(true);
		drawTemperatureGauge(false);

		// charge gauge
		drawChargeGauge(true);
		drawChargeGauge(false);
    
		// cooldown value
		Letters::Get(L10)(ROUND_UP(Data::LPlayer.coolDownTime, 60)).draw(Arg::topRight, {  230, 62 }, Color(L"#77f"));
		Letters::Get(L10)(ROUND_UP(Data::RPlayer.coolDownTime, 60)).draw(Arg::topRight, { 1085, 62 }, Color(L"#77f"));

		stopwatchFill.draw(Color(L"#052942"));
		TextureAsset(L"stopwatch-frame").draw();

		Letters::Get(L12)(stopwatch.min())
			.draw(Arg::topRight, { Window::Center().x - 10, 35 });
		CicaR::Get(C12)(L":")
			.draw(Arg::topRight, { Window::Center().x, 35 });
		Letters::Get(L12)(twoDigits(stopwatch.s() % 60))
			.draw(Arg::topRight, { Window::Center().x + 38, 35 });
	}

	switch(status) {
		case COUNT_DOWN_INIT: {
			Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.6));
			break;
		}

		case COUNT_DOWN: {
			Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.6));
			drawCountDown(countDown);
			drawLoading({ 1150, 700 }, countDown);

			break;
		}

		case GAME_INIT:	break;

		case GAME: {
			Vec2 buttonPos(890, 692);

			buttonPos.x += (int)TextureAsset(L"stick_24").draw(buttonPos).w + 6;
			buttonPos.x += (int)CicaR::Get(C12)(L"移動").draw(buttonPos).w + 15;

			buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos).w + 6;
			buttonPos.x += (int)CicaR::Get(C12)(L"Main").draw(buttonPos).w + 15;

			buttonPos.x += (int)TextureAsset(L"buttonLB_24").draw(buttonPos).w + 6;
			buttonPos.x += (int)CicaR::Get(C12)(L"Sub").draw(buttonPos).w + 15;

			buttonPos.x += (int)TextureAsset(L"buttonRB_24").draw(buttonPos).w + 6;
			buttonPos.x += (int)CicaR::Get(C12)(L"Special").draw(buttonPos).w + 15;

			break;
		}

		case FINISH_INIT: break;

		case FINISH: {
			Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.7));

			constexpr int y = 125;
			constexpr int hy = 100 + y;
			constexpr int sy = 80 + hy;
			constexpr int ty = 80 + sy;


			if (Data::LPlayer.isHPRunOut() && Data::RPlayer.isHPRunOut())
				SmartUI::Get(S32)(L"引き分け！").drawCenter(y, Color(L"#fff"));
			else {
				if (Data::LPlayer.isHPRunOut())
					SmartUI::Get(S32)(L"RPlayer win !").drawCenter(y, Color(L"#00f"));
				if (Data::RPlayer.isHPRunOut())
					SmartUI::Get(S32)(L"LPlayer win !").drawCenter(y, Color(L"#f00"));
			}

			// 箇条書き
			SmartUI::Get(S28)(L"HP:")
				.draw({ 280, hy });
			SmartUI::Get(S28)(L"Skills:")
				.draw({ 280, sy });
			SmartUI::Get(S28)(L"Time:")
				.draw({ 280, ty });

			// HP
			Letters::Get(L18)(Format(Data::LPlayer.HP))
				.draw(Arg::topRight, { 550, hy + 10 });
			CicaR::Get(C12)(L"/1000")
				.draw(Arg::topRight, { 620, hy + 25 });
			Letters::Get(L18)(Format(Data::RPlayer.HP))
				.draw(Arg::topRight, { 770, hy + 10 });
			CicaR::Get(C12)(L"/1000")
				.draw(Arg::topRight, { 840, hy + 25 });

			// Skills
			for (auto isLeft : step(2)) { // LPlayer, RPlayer
				Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
				String skillType[3] = { L"main", L"sub", L"special" };
				int    whatSkill[3] = { PLAYER->whatMainSkill, PLAYER->whatSubSkill, PLAYER->whatSpecialSkill };
				int	   skillsCnt[3] = { PLAYER->mainSkillCnt, PLAYER->subSkillCnt, PLAYER->specialSkillCnt };
				String skillColor[3] = { L"#0c0", L"#00c", L"#ffd000" };
				for (auto type : step(3)) { // mainSkill, subSkill, specialSkill
					TextureAsset(skillType[type] + Format((int)whatSkill[type])).resize(50, 50)
						.draw(670 + (60 * type) - (220 * isLeft), sy + 2);

					Rect(670 + (60 * type) - (220 * isLeft), sy + 52, 50, 20).draw(Color(skillColor[type]));

					Letters::Get(L7)(skillsCnt[type] < 1000 ? Format(skillsCnt[type]) : L"999+")
						.draw(Arg::topRight, { 717 + (60 * type) - (220 * isLeft), sy + 55 });
				}
			}

			// Time
			Letters::Get(L18)(stopwatch.min())
				.draw(Arg::topRight, { Window::Center().x - 15, ty + 10 });
			CicaR::Get(C18)(L":")
				.draw(Arg::topRight, { Window::Center().x + 3, ty + 10 });
			Letters::Get(L18)(twoDigits(stopwatch.s() % 60))
				.draw(Arg::topRight, { Window::Center().x + 63, ty + 10 });

			// Graph
			drawHPGraph(900, y + 250, LHPGraph, RHPGraph);

			// 装飾
			Line(250, hy - 10, 250, ty + 70).draw(6, ColorF(L"#00BFFF"));

			const String text[3] = { L"RESTART", L"TITLE", L"EXIT" };
			for (auto i : step(3)) {
				SmartUI::Get(S28)(text[i]).draw(Arg::leftCenter, { 280, 540 + 65 * i });
				if (i == selecting) {
					Geometry2D::CreateNgon(3, 13, 90_deg, { 245, 540 + selecting * 65 }).draw();
				}
			}

			Vec2 pos = CicaR::Get(C12)(L"subaru2003/SpaceWars2").draw(Arg::rightCenter, Window::Size() + Vec2(-15, -25)).pos;
			pos.x += -35;
			TextureAsset(L"github-light").scale(0.8).draw(pos);

			break;
		}
	}
}


String Game::twoDigits(int n) {
	if (n < 10) return Format(L"0", n);
	return Format(n);
}


void Game::drawCountDown(const Stopwatch& _countDown) {
	const Vec2 pos(Window::Center().x, Window::Center().y);
	const HSV color(28 + (3 - _countDown.s() * 8), 1.0, 1.0);

	if (_countDown.s() < 3)
		Letters::Get(L32)(3 - _countDown.s()).drawAt(pos, color);
}

void Game::drawLoading(Vec2 _pos, const Stopwatch& _countDown) {
	double radius = 10; // 半径
	const int num = 10; // 個数
	const double speed = 0.05; // speed
	const double dNum = num;
	const double dif = TwoPi / dNum;

	for(auto i : step(num)) {
		const double radian = i * dif;
		const Vec2 tPos = _pos + Circular(radius, radian);
		const double phase = System::FrameCount() * (-speed) + radian / 2.0;
		const double tRadius = atan(Tan(phase)) / Pi + 1.0 / 2.0;

		Circle(tPos, tRadius * radius / 5.0).draw();
	}
	
	const int width = (int)(_countDown.ms() / 3000.0 * 90.0);
	const HSV color(28 + (3 - _countDown.s() * 8), 1.0, 1.0);

	// 外
	RoundRect(_pos.asPoint() + Point(20, -5), { width + 12, 15 }, 7.5)
		.drawShadow({}, 8, 3, color);

	// Loading...
	SmartB::Get(Sb12)(L"Loading...").draw(_pos + Vec2(20, -10));
}

void Game::drawHPGauge(bool _isLeft) {
	Vec2 pos(0, 40);
	double width;
	int reflectionX;
	const int dist = 90;
	if (_isLeft) {
		width = Data::LPlayer.HP / 1000.0 * 360;
		pos.x = Window::Center().x - dist - width;
		reflectionX = Window::Center().x - dist - 360;
	}
	else {
		width = Data::RPlayer.HP / 1000.0 * 360;
		pos.x = Window::Center().x + dist - 15;
		reflectionX = Window::Center().x + dist - 12;
	}

	// 背景
	RoundRect({ reflectionX, pos.y }, { 360 + 12, 15 }, 7.5)
		.draw(ColorF(L"#f99").setAlpha(0.25));

	// 外周
	RoundRect(pos.asPoint(), { width + 15, 15 }, 7.5)
		.drawShadow({}, 8, 3, Color(L"#f22"));

	// 内周
	RoundRect(pos.asPoint() + Vec2(7.5, 7.5).asPoint(), { width, 2 }, 1.5)
		.drawShadow({}, 8, 4, Color(L"#fee"));
}

void Game::drawTemperatureGauge(bool _isLeft) {
	Vec2 pos(0, 65);
	Vec2 valuePos(0, 62);
	Vec2 borderPos(0, 65);
	Player* PLAYER = &(_isLeft ? Data::LPlayer : Data::RPlayer);
	HSV color(Color(L"#2f2"));
	HSV backColor(Color(L"#9f9"));
	const double width = PLAYER->temperature / 1000.0 * 240;
	const int dist = 80;
	int reflectionX;

	if (_isLeft) {
		pos.x = Window::Center().x - dist - width;
		valuePos.x = Window::Center().x - dist - 251;
		reflectionX = Window::Center().x - dist - 240;
		borderPos.x = Window::Center().x - dist - 192;
	}
	else {
		pos.x = Window::Center().x + dist - 15;
		valuePos.x = Window::Center().x + dist + 280;
		reflectionX = Window::Center().x + dist - 15;
		borderPos.x = Window::Center().x + dist;
	}

	if (PLAYER->temperature >300)
		color.h -= (PLAYER->temperature - 300) / 5.5;

	backColor = color;
	backColor.s = 0.4;

	// 背景
	RoundRect({ reflectionX, pos.y }, { 240 + 15, 15 }, 7.5)
		.draw(backColor.toColorF().setAlpha(0.3));

	// 背景２
	RoundRect(borderPos, { 192, 15 }, 7.5)
		.draw(backColor.toColorF().setAlpha(0.4));

	// 外周
	RoundRect(pos.asPoint(), { width + 15, 15 }, 7.5)
		.drawShadow({}, 8, 3, color);

	// 内周
	RoundRect(pos.asPoint() + Vec2(7.5, 7.5).asPoint(), { width, 2 }, 0.5)
		.drawShadow({}, 8, 4, color - HSV(0, 0.8, 0));

	// value
	Letters::Get(L10)(ROUND_UP(PLAYER->temperature, 10)).draw(Arg::topRight, valuePos, color);
	
}

void Game::drawChargeGauge(bool _isLeft) {
	Vec2 pos(0, 60);
	HSV color(48, 1, 1);
	const int dist = 510;

	Player* PLAYER = &(_isLeft ? Data::LPlayer : Data::RPlayer);
	double reqCharge = PLAYER->requireCharge[PLAYER->whatSpecialSkill];
	int arcCnt = 0;
	if (PLAYER->inRecovery)
		arcCnt = (int)reqCharge;
	else
		arcCnt = (int)floor(PLAYER->charge / reqCharge * 30);

	if (_isLeft) pos.x = Window::Center().x - dist;
	else		 pos.x = Window::Center().x + dist;

	color.s = 0.75 + PLAYER->charge / reqCharge * 0.25;
	if (PLAYER->charge >= reqCharge || PLAYER->inRecovery)
		color.h = 42;

	// 内側 破線
	for (auto i : step(18))
		Circle(pos, 15).drawArc(Radians(20 * i + 2), 16_deg, 1, 1, color);

	// 外側 背景
	for (auto i : step(30))
		Circle(pos, 20).drawArc(Radians(12 * i + 1), 10_deg, 0, 4, ColorF(L"#ccc").setAlpha(0.5));

	// 外側 Gauge本体
	for (auto i : step(arcCnt))
		Circle(pos, 18).drawArc(Radians(12 * i + 1), 10_deg, 0, 7, color);

	// % 表示
	if (floor(PLAYER->charge / reqCharge * 100) == 100 || PLAYER->inRecovery)
		Letters::Get(L7)(L"Go").drawAt(pos, color);
	else
		Letters::Get(L7)((int)floor(PLAYER->charge / reqCharge * 100)).draw(Arg::topRight, { (int)pos.x + 10, (int)pos.y - 7 }, color);

	// ただの飾り
	int r = 5;
	Circle(pos, 30)
		.drawArc(0_deg, Radians(180 - r), 0, 1, ColorF(L"#ccc").setAlpha(0.5))
		.drawArc(Radians(180 + r), Radians(180 - r), 0, 1, ColorF(L"#ccc").setAlpha(0.5));

	TextureAsset(L"special" + Format(Data::LPlayer.whatSpecialSkill)).resize(r * 2, r * 2).drawAt(pos + Vec2(0, 30));

}

void Game::drawHPGraph(int _x, int _y, const LineString& _LHPGraph, const LineString& _RHPGraph) {
	constexpr int w = 270;
	constexpr int h = 120;

	// 背景
	Rect(_x, _y - 120 + 2, w, h + 2).draw(ColorF(L"fff").setAlpha(0.5));

	// 目盛り
	Line(_x, _y - 100, _x + w, _y - 100).draw(1, ColorF(L"#fff").setAlpha(0.8));
	Line(_x, _y -  50, _x + w, _y -  50).draw(1, ColorF(L"#fff").setAlpha(0.8));

	// HP graph
	for (auto i : step(_LHPGraph.size() - 1)) {
		_LHPGraph.line(i).movedBy(_x, _y - 100).draw(3, ColorF(L"#f00").setAlpha(0.5));
		_RHPGraph.line(i).movedBy(_x, _y - 100).draw(3, ColorF(L"#00f").setAlpha(0.5));
	}

	// 白い枠
	LineString{ { _x - 2, _y - h + 2}, { _x - 2, _y + 2 }, { _x + 270, _y + 2 } }.draw(4);
}

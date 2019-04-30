#include "Game.hpp"

#define ROUND(x, divisor) ((x + x % divisor) / divisor)

void Game::init() {
	stopwatch.start();
}

void Game::update() {
	changeScene(Debug::InputFnKey(), 250);

	if (!finish) {

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
					itr++;
				}
			}
		}
	}
	else { // finish
		if (!finishInit) {
			stopwatch.pause();

			double x = 900;
			for (auto HP : Data::LPlayer.HPLog) {
				LHPGraph.push_back({ x, 540 - HP / 10 });
				x += 250.0 / Data::LPlayer.HPLog.size();
			}
			x = 900;
			for (auto HP : Data::RPlayer.HPLog) {
				RHPGraph.push_back({ x, 540 - HP / 10 });
				x += 250.0 / Data::RPlayer.HPLog.size();
			}
			finishInit = true;
		}
		if (Data::KeyEnter.repeat(20))
			changeScene(L"Ending", 500);
	}

	if (Data::LPlayer.isHPRunOut() || Data::RPlayer.isHPRunOut())
		finish = true;
}

void Game::draw() const {
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();

	/*Data::LPlayer.DrawMainSkill();
	Data::LPlayer.DrawSubSkill();
	Data::LPlayer.DrawSpecialSkill();
	Data::RPlayer.DrawMainSkill();
	Data::RPlayer.DrawSubSkill();
	Data::RPlayer.DrawSpecialSkill();*/
	for (auto bul : bullets) {
		bul->draw();
	}

	Data::LPlayer.drawShip();
	Data::RPlayer.drawShip();
	// Data::LPlayer.drawGauge();
	// Data::RPlayer.drawGauge();

	Line(Config::WIDTH / 2, 0, Config::WIDTH / 2, Config::HEIGHT).draw(3, ColorF(L"#fff").setAlpha(0.8));

	// HP gauge
	drawHPGauge(true);
	drawHPGauge(false);

	// temperature gauge
	gauge(true,  { 575, 65 }, 215).draw(ColorF(L"#efe").setAlpha(0.5)).drawFrame(2, ColorF(L"#8f8").setAlpha(0.5));
	gauge(false, { 710, 65 }, 215).draw(ColorF(L"#efe").setAlpha(0.5)).drawFrame(2, ColorF(L"#8f8").setAlpha(0.5));
	gauge(true,  { 575, 65 }, Data::LPlayer.temperature / 1000.0 * 215).draw(Color(L"#7f7")).drawFrame(2, Color(L"#0f0"));
	gauge(false, { 710, 65 }, Data::RPlayer.temperature / 1000.0 * 215).draw(Color(L"#7f7")).drawFrame(2, Color(L"#0f0"));

	// temperature value
	rightAlign(L"SmartB12", Format(ROUND(Data::LPlayer.temperature, 10), L"℃"), 350, 62, Color(L"#7f7"));
	FontAsset(L"SmartB12")(ROUND(Data::RPlayer.temperature, 10), L"℃").draw(935, 62, Color(L"#7f7"));

	// cooldown value
	rightAlign(L"SmartB12", Format(ROUND(Data::LPlayer.coolDownTime, 60), L"s"), 235, 62, Color(L"#77f"));
	FontAsset(L"SmartB12")(ROUND(Data::RPlayer.coolDownTime, 60), L"s").draw(1050, 62, Color(L"#77f"));

	if (!finish) {
		Vec2 buttonPos(890, 692);

		buttonPos.x += (int)TextureAsset(L"stick_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"移動").draw(buttonPos).w + 15;

		buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"Main").draw(buttonPos).w + 15;

		buttonPos.x += (int)TextureAsset(L"buttonLB_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"Sub").draw(buttonPos).w + 15;

		buttonPos.x += (int)TextureAsset(L"buttonRB_24").draw(buttonPos).w + 6;
		buttonPos.x += (int)FontAsset(L"CicaR12")(L"Special").draw(buttonPos).w + 15;
	}
	else {
		Rect(0, 0, Config::WIDTH, Config::HEIGHT).draw(ColorF(L"#000").setAlpha(0.7));


		if (Data::LPlayer.isHPRunOut() && Data::RPlayer.isHPRunOut())
			FontAsset(L"Smart32")(L"引き分け！").drawCenter(300, Color(L"#fff"));
		else {
			if (Data::LPlayer.isHPRunOut())
				FontAsset(L"Smart32")(L"RPlayer win !").drawCenter(250, Color(L"#00f"));
			if (Data::RPlayer.isHPRunOut())
				FontAsset(L"Smart32")(L"LPlayer win !").drawCenter(250, Color(L"#f00"));
		}

		// 箇条書き
		FontAsset(L"Smart28")(L"HP:").draw(280, 390);
		FontAsset(L"Smart28")(L"Skills:").draw(280, 470);
		FontAsset(L"Smart28")(L"Time:").draw(280, 550);

		// HP
		rightAlign(L"Smart28", Format(Data::LPlayer.HP), 550, 390);
		rightAlign(L"CicaR12", L"/1000", 620, 415);
		rightAlign(L"Smart28", Format(Data::RPlayer.HP), 770, 390);
		rightAlign(L"CicaR12", L"/1000", 840, 415);

		// Skills
		for (int isLeft = 0; isLeft <= 1; isLeft++) { // LPlayer, RPlayer
			Player* PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
			String skillType[3] = { L"main", L"sub", L"special" };
			int    whatSkill[3] = { PLAYER->whatMainSkill, PLAYER->whatSubSkill, PLAYER->whatSpecialSkill };
			int	   skillsCnt[3] = { PLAYER->mainSkillCnt, PLAYER->subSkillCnt, PLAYER->specialSkillCnt };
			String skillColor[3] = { L"#0c0", L"#00c", L"#ffd000" };
			for (int type = 0; type < 3; type++) { // mainSkill, subSkill, specialSkill
				TextureAsset(skillType[type] + Format((int)whatSkill[type])).resize(50, 50)
					.draw(670 + (60 * type) - (220 * isLeft), 472);

				Rect(670 + (60 * type) - (220 * isLeft), 522, 50, 20).draw(Color(skillColor[type]));

				rightAlign(L"CicaR12", (skillsCnt[type] < 1000 ? Format(skillsCnt[type]) : L"999+"), 718 + (60 * type) - (220 * isLeft), 520);
			}
		}

		// Time
		FontAsset(L"Smart28")(stopwatch.min(), L"分 ", stopwatch.s() % 60, L"秒").drawCenter(550);

		// Graph
		Rect(900, 418, 272, 122).draw(ColorF(L"fff").setAlpha(0.5));
		Line(900, 440, 1170, 440).draw(1, ColorF(L"#fff").setAlpha(0.8));
		Line(900, 490, 1170, 490).draw(1, ColorF(L"#fff").setAlpha(0.8));
		LHPGraph.draw(3, ColorF(L"#f00").setAlpha(0.5));
		RHPGraph.draw(3, ColorF(L"#00f").setAlpha(0.5));
		Line(900, 420,  900, 540).draw(4);
		Line(900, 540, 1170, 540).draw(4);

		// 装飾
		Line(250, 380, 250, 620).draw(6, ColorF(L"#00BFFF"));
	}
}


void Game::rightAlign(String _font, String _text, int _x, int _y, Color _color) {
	FontAsset(_font)(_text).draw(_x - FontAsset(_font)(_text).region().w, _y, _color);
}

Quad Game::gauge(bool _isLeft, Vec2 _topLeft, double _width) {
	int oblique = (_isLeft ? 5 : -5);
	if (_isLeft)
		return Quad(_topLeft + Vec2(-_width, 0), _topLeft, _topLeft + Vec2(oblique, 15), _topLeft + Vec2(-_width + oblique, 15));
	else
		return Quad(_topLeft, _topLeft + Vec2(_width, 0), _topLeft + Vec2(_width + oblique, 15), _topLeft + Vec2(oblique, 15));
}

void Game::drawGauge(bool _isLeft, Vec2 _topLeft, double _width, String _fillColor, String _frameColor) {
	gauge(_isLeft, _topLeft, _width).draw(Color(_fillColor)).drawFrame(2, Color(_frameColor));
}

void Game::drawHPGauge(bool _isLeft) {
	Vec2 pos(0, 40);
	double width;
	if (_isLeft) {
		width = Data::LPlayer.HP / 1000.0 * 360;
		pos.x = 560 - width;
	}
	else {
		width = Data::RPlayer.HP / 1000.0 * 360;
		pos.x = 720;
	}

	RoundRect(pos.asPoint(), { width + 12, 15 }, 7.5)
		.drawShadow({}, 8, 3, Color(L"#f22"));

	RoundRect(pos.asPoint() + Vec2(6, 6).asPoint(), { width, 3 }, 1.5)
		.drawShadow({}, 8, 4, Color(L"#fee"));
}

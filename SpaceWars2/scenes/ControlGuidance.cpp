#include "ControlGuidance.hpp"

void ControlGuidance::init() {
	if (!TextureAsset::IsRegistered(L"keyboard")) {
		TextureAsset::Register(L"keyboard"  , L"/7300");
		TextureAsset::Register(L"controller", L"/7310");
		TextureAsset::Register(L"gauge"     , L"/7320");
	}
}

void ControlGuidance::update() {
	changeScene(Debug::InputFnKey(), 100);
	if (Data::KeyEnter.repeat(20)) {
		if (status != CONTROLLER) {
			status = (ControlType)(status + 1);
		} else {
			changeScene(L"ScreenGuidance", 250);
		}
		SoundAsset(L"move1").setVolume(Config::MASTER_VOLUME * Config::CURSOR_VOLUME);
		SoundAsset(L"move1").playMulti();
	}
	if (Data::KeyBack.repeat(20)) {
		if (status != KEY) {
			status = (ControlType)(status - 1);
			SoundAsset(L"move1").setVolume(Config::MASTER_VOLUME * Config::CURSOR_VOLUME);
			SoundAsset(L"move1").playMulti();
		}
	}
}

void ControlGuidance::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.5));

	Line({ 25, 18 }, { 225, 18 }).draw(5);
	SmartUI::Get(S32)(L"操作方法").draw({ 30, 20 });
	Line({ 25, 82 }, { 225, 82 }).draw(5);

	switch (status) {
	case KEY: {

		SmartUI::Get(S28)(L"～キーボード編～").draw({ 255, 25 });

		TextureAsset(L"keyboard").drawAt(Window::Center() + Vec2(0, 50));

		Rect(620, 20, 630, 80).draw(Color(L"#ffc")).drawFrame(2, 2, Color(L"#fb0"));
		CicaR::Get(C12)(L"",
			L"＊注意事項＊\n", 
			L"- キー配置はキーボードによって異なる場合があります。\n",
			L"- キーの同時押し数に制限がある場合があります。\n"
		).draw({ 630, 25 }, Color(L"#000"));

		break;
	}

	case CONTROLLER: {

		SmartUI::Get(S28)(L"～コントローラー編～").draw({ 255, 25 });

		constexpr int cY = 400; //Y軸の基準(center)

		TextureAsset(L"controller").drawAt(Window::Center().x, cY);

		// stick
		drawPointLine({ 539, cY + 72 }, { 265, cY + 72 });
		TextureAsset(L"stick_64").drawAt(225, cY + 72);
		SmartUI::Get(S28)(L"移動").draw(Arg::rightCenter, { 175, cY + 72 });
		// A
		drawPointLine({ 830, cY + 13 }, { 1015, cY + 72 }, Color(L"#afa"));
		TextureAsset(L"buttonA_64").drawAt(1055, cY + 72);
		SmartUI::Get(S28)(L"決定").draw(Arg::leftCenter, { 1105, cY + 72 });
		// B
		drawPointLine({ 880, cY - 37 }, { 1015, cY - 37 }, Color(L"#faa"));
		TextureAsset(L"buttonB_64").drawAt(1055, cY - 37);
		Line({ 1100, cY - 12 }, { 1210, cY - 12 }).draw(10, Color(L"#7CFC00"));
		SmartUI::Get(S28)(L"main").draw(Arg::leftCenter, { 1105, cY - 37 });
		// LB
		drawPointLine({ 435, cY - 190 }, { 265, cY - 190 });
		TextureAsset(L"buttonLB_64").drawAt(225, cY - 190);
		Line({ 95, cY - 165 }, { 180, cY - 165 }).draw(10, Color(L"#4169E1"));
		SmartUI::Get(S28)(L"sub").draw(Arg::rightCenter, { 175, cY - 190 });
		// RB
		drawPointLine({ 845, cY - 190 }, { 965, cY - 190 });
		TextureAsset(L"buttonRB_64").drawAt(1005, cY - 190);
		Line({ 1050, cY - 165 }, { 1210, cY - 165 }).draw(10, Color(L"#FFD000"));
		SmartUI::Get(S28)(L"special").draw(Arg::leftCenter, { 1055, cY - 190 });

		break;
	}
	}
}


void ControlGuidance::drawPointLine(Vec2 _root, Vec2 _pos, Color _color) {
	int isLeft = 0; // -1:left 0:center 1:right
	int xSlope = 0;
	if (_pos.x > _root.x) isLeft = -1;
	if (_pos.x < _root.x) isLeft = 1;
	if (_pos.y > _root.y) xSlope = -1;
	if (_pos.y < _root.y) xSlope = 1;
	double move = _pos.y - _root.y;

	Circle(_root, 6).draw(_color);
	LineString({ _root, _root.movedBy(move * isLeft * xSlope, move), _pos }).draw(5, _color);
}

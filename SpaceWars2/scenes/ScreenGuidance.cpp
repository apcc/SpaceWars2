#include "ScreenGuidance.hpp"

#define ROUND_DOWN(x, divisor)	((x - x % divisor) / divisor)
#define ROUND_UP(x, divisor)	(ROUND_DOWN(x, divisor) + (x % divisor ? 1 : 0))

constexpr double GAUGE_SCALE = 1.5;

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	changeScene(Debug::InputFnKey(), 100);
	if (Data::KeyEnter.repeat(20, true)) {
		if (status == LETS_GO) changeScene(L"SkillSelect", 500);
		else				   status = (Stat)(status + 1);
		SoundAsset(L"move1").setVolume(Config::MASTER_VOLUME * Config::CURSOR_VOLUME);
		SoundAsset(L"move1").playMulti();
	}
	if (Data::KeyBack.repeat(20, true)) {
		if (status == FULL) changeScene(L"ControlGuidance", 500);
		else				   status = (Stat)(status - 1);
		SoundAsset(L"move1").setVolume(Config::MASTER_VOLUME * Config::CURSOR_VOLUME);
		SoundAsset(L"move1").playMulti();
	}
	changeScene(Debug::InputFnKey(), 250);
}

void ScreenGuidance::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.5));

	Line({ 25, 18 }, { 310, 18 }).draw(5);
	SmartUI::Get(S32)(L"画面の見かた").draw({ 30, 20 });
	Line({ 25, 82 }, { 310, 82 }).draw(5);

	SmartUI::Get(S28)(status + 1, L"/", COUNT).draw({ 340, 25 });

	Vec2 tl = gaugePic.drawAt(Window::Center() + Vec2(0, -70))
					  .drawFrame(0, 3, Palette::White)
					  .tl; // gauge画像左上pos

	if (status == HP || status == TEMPERATURE || status == OVER_HEAT || status == CHARGE) {
		Rect(tl.asPoint(), gaugePic.size).draw(ColorF(L"#000").setAlpha(0.3));
		gaugePic(shadowPos[status][0], shadowPos[status][1])
			.draw(shadowPos[status][0] + tl.asPoint());
		RoundRect(shadowPos[status][0] + tl.asPoint(), shadowPos[status][1], 10)
			.drawFrame(4, 2, frameColor[status]);
	}

	SmartUI::Get(S28)(description[status], L"").draw(tl + Vec2(0, 280), frameColor[status]);
}


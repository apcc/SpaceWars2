#include "ScreenGuidance.hpp"

#define ROUND_DOWN(x, divisor)	((x - x % divisor) / divisor)
#define ROUND_UP(x, divisor)	(ROUND_DOWN(x, divisor) + (x % divisor ? 1 : 0))

constexpr double GAUGE_SCALE = 1.5;

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	if (Data::KeyEnter.repeat(20, true)) {
		if (status == LETS_GO) changeScene(L"SkillSelect");
		else				   status = (Stat)(status + 1);
	}
	changeScene(Debug::InputFnKey(), 250);
}

void ScreenGuidance::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.5));

	Line({ 25, 18 }, { 310, 18 }).draw(5);
	SmartUI::GetFont(S32).draw(L"画面の見かた", { 30, 20 });
	Line({ 25, 82 }, { 310, 82 }).draw(5);

	Vec2 tl = gaugePic.drawAt(Window::Center() + Vec2(0, -70))
					  .drawFrame(0, 3, Palette::White)
					  .tl; // gauge画像左上pos

	if (status == HP || status == TEMPERATURE || status == OVER_HEAT || status == CHARGE) {
		Rect(tl.asPoint(), gaugePic.size).draw(ColorF(L"#000").setAlpha(0.3));
		gaugePic(shadowPos[status][0], shadowPos[status][1]).draw(shadowPos[status][0] + tl.asPoint());
	}

	Rect(shadowPos[status][0] + tl.asPoint(), shadowPos[status][1])
		.drawFrame(3, 2, frameColor[status]);
}


template <typename T>
void ScreenGuidance::rightAlign(Font _font, T _text, int _x, int _y, Color _color) {
	_font(_text).draw(_x - _font(_text).region().w, _y, _color);
}

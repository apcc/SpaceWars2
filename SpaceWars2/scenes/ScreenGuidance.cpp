#include "ScreenGuidance.hpp"

#define ROUND_DOWN(x, divisor)	((x - x % divisor) / divisor)
#define ROUND_UP(x, divisor)	(ROUND_DOWN(x, divisor) + (x % divisor ? 1 : 0))

void ScreenGuidance::init() {

}

void ScreenGuidance::update() {
	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"SkillSelect", 500);
}

void ScreenGuidance::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.5));

	Line({ 25, 18 }, { 310, 18 }).draw(5);
	SmartUI::GetFont(S32).draw(L"画面の見かた", { 30, 20 });
	Line({ 25, 82 }, { 310, 82 }).draw(5);

	TextureAsset(L"gauge").scale(1.5).drawAt(Window::Center() + Vec2(0, -70)).drawFrame(0, 8, Palette::White);
}


template <typename T>
void ScreenGuidance::rightAlign(Font _font, T _text, int _x, int _y, Color _color) {
	_font(_text).draw(_x - _font(_text).region().w, _y, _color);
}

#include "License.hpp"

void License::init() {
}

void License::update() {
	if (increase) {
		alpha += 0.01;
		if (alpha >= 1.0)
			increase = false;
	}
	else {
		alpha -= 0.01;
		if (alpha <= 0.0)
			increase = true;
	}

	changeScene(Debug::InputFnKey(), 250);
	if (Data::KeyEnter.repeat(20))
		changeScene(L"Opening", 250);
}

void License::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	Rect(Window::Size()).draw(ColorF(L"#000").setAlpha(0.4));
	TextureAsset(L"license").draw();

	Vec2 buttonPos(1195, 692);

	buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos, Alpha((int)(255 * alpha))).w + 6;
	buttonPos.x += (int)CicaR::Get(C12)(L"Back").draw(buttonPos, Alpha((int)(255 * alpha))).w + 10;
}

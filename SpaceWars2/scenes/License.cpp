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
	TextureAsset(L"background").resize(Config::WIDTH, Config::HEIGHT).draw();
	Rect(Config::WIDTH, Config::HEIGHT).draw(ColorF(L"#000").setAlpha(0.4));
	TextureAsset(L"license").draw();
	FontAsset(L"CicaR12")(L"Click Enter to back.").draw(1020, 690, ColorF(L"#fff").setAlpha(alpha));
}

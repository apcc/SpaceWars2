#include "Countdown.hpp"

#define WAIT_TIME 30

// ======== Three ========

void Three::init() {}

void Three::update() {
	changeScene(Debug::InputFnKey(), 250);

	++frameCount;
	if (frameCount - startCount == WAIT_TIME)
		changeScene(L"Two", 500);

	Data::LPlayer.skillSelect();
	Data::RPlayer.skillSelect();

}

void Three::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	FontAsset(L"Smart32")(L"3").drawCenter(360, Color(L"#fff"));
}

// ======== Two ========

void Two::init() {}

void Two::update() {
	changeScene(Debug::InputFnKey(), 250);

	++frameCount;
	if (frameCount - startCount == WAIT_TIME)
		changeScene(L"One", 500);

	Data::LPlayer.skillSelect();
	Data::RPlayer.skillSelect();

}

void Two::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	FontAsset(L"Smart32")(L"2").drawCenter(360, Color(L"#fff"));
}

// ======== One ========

void One::init() {}

void One::update() {
	changeScene(Debug::InputFnKey(), 250);

	++frameCount;
	if (frameCount - startCount == WAIT_TIME)
		changeScene(L"Game", 500);

	Data::LPlayer.skillSelect();
	Data::RPlayer.skillSelect();

}

void One::draw() const {
	TextureAsset(L"background").resize(Window::Size()).draw();
	FontAsset(L"Smart32")(L"1").drawCenter(360, Color(L"#fff"));
}

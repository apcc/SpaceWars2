#pragma once
#include "Include.hpp"
#include "Game.hpp"


enum Stat {
	FULL,
	HP,
	TEMPERATURE,
	OVER_HEAT,
	CHARGE,
	LETS_GO
};

class ScreenGuidance final : public SceneManager<String,CommonData>::Scene {
private:
	Stat status = FULL;
	const Texture gaugePic = Texture(Image(L"/7960").scale(1.5));

	const Array<Array<Point>> shadowPos = {
	{ { 0, 0 }, { 0, 0 } }, // FULL
	{ { 180, 48 }, { 600, 48 } }, // HP
	{ { 315, 85 }, { 480, 48 } }, // TEMPERATURE
	{ { 180, 85 }, {  90, 48 } }, // OVER_HEAT
	{ { 45, 30 }, { 120, 120 } }, // CHARGE
	{ { 0, 0 }, { 0, 0 } }, // LETS_GO
	};
	const Array<Color> frameColor = {
		Color(L"#fff"), // FULL
		Color(L"#f33"), // HP
		Color(L"#2f8"), // TEMPERATURE
		Color(L"#88f"), // OVER_HEAT
		Color(L"#ff2"), // CHARGE
		Color(L"#fff"), // LETS_GO
	};

	template<typename T>
	static void rightAlign(Font _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));

public:
	void init() override;
	void update() override;
	void draw() const override;
};

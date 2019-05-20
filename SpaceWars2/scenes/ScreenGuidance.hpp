#pragma once
#include "Include.hpp"
#include "Game.hpp"

class ScreenGuidance final : public SceneManager<String,CommonData>::Scene {
private:

	template<typename T>
	static void rightAlign(Font _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));

public:
	void init() override;
	void update() override;
	void draw() const override;
};

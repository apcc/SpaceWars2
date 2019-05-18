#pragma once
#include "Include.hpp"

class ControlGuidance final : public SceneManager<String, CommonData>::Scene {
private:

	static void drawPointLine(Vec2 _root, Vec2 _pos, Color _color = Color(L"#fff"));
	template<typename T>
	// x:右揃え y:中央揃え
	static void rightCAlign(Font _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));
	template<typename T>
	// x:左揃え y:中央揃え
	static void leftCAlign(Font _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));

public:
	void init() override;
	void update() override;
	void draw() const override;
};

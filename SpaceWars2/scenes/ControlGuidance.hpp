#pragma once
#include "Include.hpp"

enum ControlType {
	KEY,
	CONTROLLER
};

class ControlGuidance final : public SceneManager<String, CommonData>::Scene {
private:
	ControlType status = KEY;

	static void drawPointLine(Vec2 _root, Vec2 _pos, Color _color = Color(L"#fff"));

public:
	void init() override;
	void update() override;
	void draw() const override;
};

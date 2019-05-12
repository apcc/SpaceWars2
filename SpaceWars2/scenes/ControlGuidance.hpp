#pragma once
#include "Include.hpp"

class ControlGuidance final : public SceneManager<String, CommonData>::Scene {
private:

	static void drawPointLine(Vec2 _root, Vec2 _pos, Color _color = Color(L"#fff"));
	static void drawPointLineString(LineString _line, Color _color = Color(L"#fff"));

public:
	void init() override;
	void update() override;
	void draw() const override;
};

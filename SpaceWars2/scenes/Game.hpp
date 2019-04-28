#pragma once
#include "Include.hpp"
#include "../skills/Bullet.hpp"

class Game final : public SceneManager<String,CommonData>::Scene {
private:
	std::vector<Bullet*> bullets;
	bool finish = false;
	bool finishInit = false;
	Stopwatch stopwatch;
	LineString LHPGraph;
	LineString RHPGraph;

	static void rightAlign(String _font, String _text, int _x, int _y, Color _color = Color(L"#fff"));
	static Quad gauge(bool _isLeft, Vec2 _topLeft, double _width);
	static void drawGauge(bool _isLeft, Vec2 _topLeft, double _width, String _fillColor, String _frameColor);

public:
	void init() override;
	void update() override;
	void draw() const override;

	~Game() {
		stopwatch.reset();
		for (auto i : bullets) delete i;
		bullets.clear();
	}
};

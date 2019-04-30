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
	static void drawHPGauge(bool _isLeft);
	static void drawTemperatureGauge(bool _isLeft);

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

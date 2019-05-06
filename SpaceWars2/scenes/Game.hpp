#pragma once
#include "Include.hpp"
#include "../skills/Bullet.hpp"
#include "../Config.hpp"

enum Status {
	COUNT_DOWN,
	GAME,
	FINISH,
};

class Game final : public SceneManager<String,CommonData>::Scene {
private:
	Status status = COUNT_DOWN;
	std::vector<Bullet*> bullets;
	bool finishInit = false;
	Stopwatch stopwatch;
	LineString LHPGraph;
	LineString RHPGraph;

	Image outerFrame = Image(1280, 720, Color(255, 0)); // [stopwatch枠] 外側枠
	Image innerFrame = Image(1280, 720, Color(255, 0)); // [stopwatch枠] 内側枠
	Texture outerFrameTex; // [stopwatch枠] 外側枠
	Texture innerFrameTex; // [stopwatch枠] 内側枠
	const LineString stopwatchFrame {
		{Config::CENTER - 70, 22},
		{Config::CENTER + 70, 22},
		{Config::CENTER + 50, 72},
		{Config::CENTER - 50, 72},
	};
	const Quad stopwatchFill{
		{Config::CENTER - 70, 22},
		{Config::CENTER + 70, 22},
		{Config::CENTER + 50, 72},
		{Config::CENTER - 50, 72}
	};


	template<typename T>
	static void rightAlign(const String& _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));
	template<typename T>
	static void rightAlign(Font _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));
	static String fillZero(int n);
	static void drawHPGauge(bool _isLeft);
	static void drawTemperatureGauge(bool _isLeft);
	static void drawChargeGauge(bool _isLeft);
	static void drawHPGraph(int _x, int _y, const LineString& _LHPGraph, const LineString& _RHPGraph);

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

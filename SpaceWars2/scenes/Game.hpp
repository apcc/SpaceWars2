#pragma once
#include "Include.hpp"
#include "../skills/Bullet.hpp"
#include "../Config.hpp"

enum Status {
	COUNT_DOWN_INIT,
	COUNT_DOWN,
	GAME_INIT,
	GAME,
	FINISH_INIT,
	FINISH,
};

class Game final : public SceneManager<String,CommonData>::Scene {
private:
	Status status = COUNT_DOWN_INIT;
	std::vector<Bullet*> bullets;
	Stopwatch countDown;
	Stopwatch stopwatch;
	LineString LHPGraph;
	LineString RHPGraph;

	Image outerFrame = Image(1280, 720, Color(255, 0)); // [stopwatch枠] 外側枠
	Image innerFrame = Image(1280, 720, Color(255, 0)); // [stopwatch枠] 内側枠
	Texture outerFrameTex; // [stopwatch枠] 外側枠
	Texture innerFrameTex; // [stopwatch枠] 内側枠
	const LineString stopwatchFrame {
		{Window::Center().x - 70, 22},
		{Window::Center().x + 70, 22},
		{Window::Center().x + 50, 72},
		{Window::Center().x - 50, 72},
	};
	const Quad stopwatchFill{
		{Window::Center().x - 70, 22},
		{Window::Center().x + 70, 22},
		{Window::Center().x + 50, 72},
		{Window::Center().x - 50, 72}
	};


	template<typename T>
	static void rightAlign(const String& _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));
	template<typename T>
	static void rightAlign(Font _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));
	static String twoDigits(int n);
	static void drawCountDown(const Stopwatch& _countDown);
	static void drawLoading(Vec2 _pos, const Stopwatch& _countDown);
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

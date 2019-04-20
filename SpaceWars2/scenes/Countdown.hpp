#pragma once
#include "Include.hpp"

class Three final : public SceneManager<String, CommonData>::Scene {
private:
	int frameCount = 0;
	int startCount = 0;

public:
	void init() override;
	void update() override;
	void draw() const override;
};

class Two final : public SceneManager<String, CommonData>::Scene {
private:
	int frameCount = 0;
	int startCount = 0;

public:
	void init() override;
	void update() override;
	void draw() const override;
};

class One final : public SceneManager<String, CommonData>::Scene {
private:
	int frameCount = 0;
	int startCount = 0;

public:
	void init() override;
	void update() override;
	void draw() const override;
};
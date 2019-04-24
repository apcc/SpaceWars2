#pragma once
#include "Include.hpp"

class SkillSelect final : public SceneManager<String, CommonData>::Scene {
private:
	static bool isLoaded;
	int nextStageTime = 0;
	bool LContinue = false;
	bool RContinue = false;
	double LAlpha[3] = { 0.5, 0.5, 0.5 };
	double RAlpha[3] = { 0.5, 0.5, 0.5 };

public:
	void init() override;
	void update() override;
	void draw() const override;
};

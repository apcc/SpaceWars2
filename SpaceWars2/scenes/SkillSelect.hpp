#pragma once
#include "Include.hpp"

class SkillSelect final : public SceneManager<String, CommonData>::Scene {
private:
	bool LContinue = false;
	bool RContinue = false;
	double LMainAlpha = 1.0;
	double LSubAlpha = 0.5;
	double LSpecialAlpha = 0.5;
	double RMainAlpha = 1.0;
	double RSubAlpha = 0.5;
	double RSpecialAlpha = 0.5;

public:
	void init() override;
	void update() override;
	void draw() const override;
};

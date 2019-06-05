#pragma once
#include "Include.hpp"
#include "../functions/SkillDescription.hpp"

class SkillSelect final : public SceneManager<String, CommonData>::Scene {
private:
	static bool isLoaded;
	int nextStageTime = 0;
	bool LReady = false;
	bool RReady = false;
	int skillsDisplayed[2][3] = {}; //[isLeft][skillType]
	int skillTypeDisplayed[2] = {}; //[isLeft]
	int whiteOutTime[2] = {};
	bool goingTowhiteout[2] = {};
	int WHITEOUT_TIME = 6;

	static SkillDescriptManager skillDescriptManager;
public:
	void init() override;
	void update() override;
	void draw() const override;
};

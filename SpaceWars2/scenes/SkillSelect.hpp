#pragma once
#include "Include.hpp"
#include "../functions/SkillDescription.hpp"

class SkillSelect final : public SceneManager<String, CommonData>::Scene {
private:
	static bool isLoaded;
	int nextStageTime = 0;
	bool LReady = false;
	bool RReady = false;
	int whatLselecting = 0;
	int whatRselecting = 0;

	SkillDescriptManager skillDescriptManager;
public:
	void init() override;
	void update() override;
	void draw() const override;
};

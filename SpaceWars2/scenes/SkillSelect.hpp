#pragma once
#include "Include.hpp"

class SkillSelect final : public SceneManager<String, CommonData>::Scene {
private:

public:
	void init() override;
	void update() override;
	void draw() const override;
};

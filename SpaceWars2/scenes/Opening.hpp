#pragma once
#include "Include.hpp"

class Opening final : public SceneManager<String, CommonData>::Scene{
private:
	int selecting = 0;

public:
	void init() override;
	void update() override;
	void draw() const override;
};

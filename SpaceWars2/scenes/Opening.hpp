#pragma once
#include "Include.hpp"

class Opening final : public SceneManager<String, CommonData>::Scene{
private:
	static int selecting;

public:
	void init() override;
	void update() override;
	void draw() const override;
};

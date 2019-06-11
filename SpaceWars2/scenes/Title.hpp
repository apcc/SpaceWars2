#pragma once
#include "Include.hpp"

class Title final : public SceneManager<String, CommonData>::Scene{
private:
	static int selecting;

public:
	void init() override;
	void update() override;
	void draw() const override;
};

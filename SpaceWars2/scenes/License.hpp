#pragma once
#include "Include.hpp"

class License final : public SceneManager<String, CommonData>::Scene {
private:
	double alpha = 0;
	bool increase = true;

public:
	void init() override;
	void update() override;
	void draw() const override;
};

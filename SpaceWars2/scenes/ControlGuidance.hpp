#pragma once
#include "Include.hpp"

class ControlGuidance final : public SceneManager<String,CommonData>::Scene {
private:

public:
	void init() override;
	void update() override;
	void draw() const override;
};

#pragma once
#include "Include.hpp"

class Finish final : public SceneManager<String,CommonData>::Scene {
private:
	bool isDraw = false;
	bool isLeftWin = true;
	String winner;

public:

	void init() override;
	void update() override;
	void draw() const override;
};

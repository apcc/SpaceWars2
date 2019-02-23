#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "../Config.hpp"
#include "../CommonData.hpp"

class Finish : public SceneManager<String,CommonData>::Scene {
private:
	bool isDraw = false;
	bool isLeftWin = true;

	String winner() const;

public:

	void init() override;
	void update() override;
	void draw() const override;
};

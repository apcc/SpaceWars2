#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "../Config.hpp"
#include "../CommonData.hpp"

class Ending : public SceneManager<String, CommonData>::Scene {
private:

public:
	void init() override;
	void update() override;
	void draw() const override;
};


#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include <vector>
#include "../Config.hpp"
#include "../CommonData.hpp"

#include "../skills/Bullet.hpp"

class Game : public SceneManager<String,CommonData>::Scene {
private:

public:
	void init() override;
	void update() override;
	void draw() const override;
};


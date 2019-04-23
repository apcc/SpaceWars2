#pragma once
#include "Include.hpp"
#include "../skills/Bullet.hpp"

class Game final : public SceneManager<String,CommonData>::Scene {
private:
	std::vector<Bullet*> bullets;
	bool finish = false;
	static void rightAlign(String _font, String _text, int _x, int _y);

public:
	void init() override;
	void update() override;
	void draw() const override;

	~Game() {
		for (auto i : bullets) delete i;
		bullets.clear();
	}
};

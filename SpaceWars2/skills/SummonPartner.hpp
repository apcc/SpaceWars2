#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class SummonPartner : public Bullet {
private:
	int LifeTime = 600;
	std::vector<Bullet*> bullets;
	Circle getShape() { return Circle(pos, 40*shrinkRate); }
	Vec2 shrinkVec2(Vec2);
	Vec2 shrinkVec2(Vec2, Rect, Rect);
	double drawRate = 1;
	double moveRate = 1;
public:
	SummonPartner(Vec2 p, bool left) : Bullet(p, left) {
		vel = Vec2(0,0);
		SoundAsset(L"SP").setVolume(Config::MASTER_VOLUME * Config::EFFECT_VOLUME);
		SoundAsset(L"SP").playMulti();
	}
	bool update(Vec2 myPos, Vec2 oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle circle) override;
	~SummonPartner() {
		for (auto i : bullets) delete i;
		bullets.clear();
	}

	Vec2 shrink(Rect _area) {
		LifeTime = 100;
		drawRate = 0.6;
		moveRate = 0.1;
		return Bullet::shrink(_area);
	}
};

#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"

class LockOn : public Bullet {
private:
	int waitTime;
	const int EXPLODE_TIMING = 30;
	int explodeTime = EXPLODE_TIMING;
	Circle getShape() { return Circle(pos, 200); }
public:
	LockOn(Vec2 p, bool left, int Time) : Bullet(p, left) {
		waitTime = Time;
		vel = Vec2(0,0);
		SoundAsset(L"LO").setVolume(Config::masterVolume*Config::effectSoundVolume);
		SoundAsset(L"LO").playMulti();
	}
	bool update(Vec2 myPos, Vec2 oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle circle) override;

};

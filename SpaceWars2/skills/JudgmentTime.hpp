#pragma once
#include <Siv3d.hpp>
#include "Bullet.hpp"
#include "../CommonData.hpp"

#define REVERSE_PLAYER (!isLeft ? Data::LPlayer : Data::RPlayer)

class JudgmentTime : public Bullet {
private:
	int lifeTime = 1;
public:
	JudgmentTime(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		REVERSE_PLAYER.changeSpeed(0);
		SoundAsset(L"JT").setVolume(Config::MASTER_VOLUME * Config::EFFECT_VOLUME);
		SoundAsset(L"JT").play();
	}
	~JudgmentTime(){
		REVERSE_PLAYER.changeSpeed(8);
	}
	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
};

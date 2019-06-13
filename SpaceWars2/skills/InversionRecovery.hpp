#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"
#include "../CommonData.hpp"

#define PLAYER (isLeft ? Data::LPlayer : Data::RPlayer)

class InversionRecovery : public Bullet {
private:
	int initHP;
	int time = 0;
	int RecoverAmount = 1;
	bool inRecovery;

	const int TRICKING_TIME = 120;

public:
	InversionRecovery(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		initHP = PLAYER.HP;
		inRecovery = false;
		PLAYER.inAbsorption = true;
	}

	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
};

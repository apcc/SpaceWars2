#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"
#include "../CommonData.hpp"


class InversionRecovery : public Bullet {
private:
	int initHP;
	int time = 0;
	bool inRecovery;
	Player* PLAYER;

	const int TRICKING_TIME = 150;

public:
	InversionRecovery(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		PLAYER = &(isLeft ? Data::LPlayer : Data::RPlayer);
		initHP = PLAYER->HP;
		inRecovery = false;
		PLAYER->inRecovery = true;
	}
	~InversionRecovery() {
		PLAYER->inRecovery = false;
	}

	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
};

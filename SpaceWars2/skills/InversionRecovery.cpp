#include "InversionRecovery.hpp"

#define GAUGE_LIMIT 1000.0
#define GAUGE_WIDTH (Window::Center().x / GAUGE_LIMIT)

bool InversionRecovery::update(Vec2 _myPos, Vec2 _oppPos) {
	if ((time > TRICKING_TIME) && !inRecovery){
		inRecovery = true;
		RecoverAmount = PLAYER.recoveryDamage * 2.0;
		PLAYER.inAbsorption = false;
		SoundAsset(L"IR").setVolume(Config::MASTER_VOLUME * Config::EFFECT_VOLUME);
		SoundAsset(L"IR").playMulti();
	}

	if (inRecovery){
		if (RecoverAmount < 20) {
			PLAYER.HP += RecoverAmount;
			RecoverAmount = 0;
		}
		else {
			PLAYER.HP += 20;
			RecoverAmount -= 20;
		}
	}
	++time;

	return Bullet::update(_myPos, _oppPos);
}

void InversionRecovery::draw() {
}

bool InversionRecovery::isVisible() {
	return ((!inRecovery) || RecoverAmount > 0);
}

int InversionRecovery::getDamage(Circle _circle) {
	(void)_circle;
	return 0;
}

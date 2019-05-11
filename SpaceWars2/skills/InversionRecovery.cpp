#include "InversionRecovery.hpp"

#define GAUGE_LIMIT 1000.0
#define GAUGE_WIDTH (Config::WIDTH / 2.0 / GAUGE_LIMIT)

bool InversionRecovery::update(Vec2 _myPos, Vec2 _oppPos) {
	if ((time > TRICKING_TIME || PLAYER.HP < 20) && !inRecovery){
		inRecovery = true;
		RecoverAmount = (initHP - PLAYER.HP) * 1.5;
		PLAYER.inRecovery = false;
	}

	if (inRecovery){
		if(RecoverAmount < 10){
			PLAYER.HP += RecoverAmount;
			RecoverAmount = 0;
		}
		else
			PLAYER.HP += 10;
			RecoverAmount -= 10;
	}
	++time;

	return Bullet::update(_myPos, _oppPos);
}

void InversionRecovery::draw() {
	if (isLeft) {
		RectF(0, 60, 1000 * GAUGE_WIDTH, 20).draw(Color(L"#ffd000"));
	}
	else {
		RectF(Config::WIDTH - 1000 * GAUGE_WIDTH, 60, Config::WIDTH, 20).draw(Color(L"#ffd000"));
	}
}

bool InversionRecovery::isVisible() {
	return ((!inRecovery) || RecoverAmount > 0);
}

int InversionRecovery::getDamage(Circle _circle) {
	return 0;
}

#include "InversionRecovery.hpp"

#define GAUGE_LIMIT 1000.0
#define GAUGE_WIDTH (Window::Center().x / GAUGE_LIMIT)

bool InversionRecovery::update(Vec2 _myPos, Vec2 _oppPos) {
	if ((time > TRICKING_TIME || PLAYER->HP < 20) && !inRecovery)
		inRecovery = true;

	if (inRecovery)
		PLAYER->HP += 3;

	++time;

	return Bullet::update(_myPos, _oppPos);
}

void InversionRecovery::draw() {
}

bool InversionRecovery::isVisible() {
	return !(inRecovery && initHP <= PLAYER->HP);
}

int InversionRecovery::getDamage(Circle _circle) {
	(void)_circle;
	return 0;
}

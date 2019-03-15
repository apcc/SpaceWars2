#include "./Bullet.hpp"

// true if destroyed
bool Bullet::update(Vec2 _myPos, Vec2 _oppPos){
	pos += vel;
	if(shouldBeDestroyed)
		return true;

	// avoidance C4100
	(void)_myPos;
	(void)_oppPos;

	return !isVisible();
}

#include "./Bullet.hpp"

// true if destroyed
bool Bullet::update(Vec2 myPos, Vec2 oppPos){
	pos += vel;
	if(shouldBeDestroyed)
		return true;

	return isInvisible();
}

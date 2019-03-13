#include "./Bullet.hpp"

// true if destroyed
bool Bullet::update(Vec2 _myPos, Vec2 _oppPos){
	pos += vel;
	if(shouldBeDestroyed)
		return true;

	return isInvisible();
}

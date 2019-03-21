#include "./Jump.hpp"

bool Jump::isLDoing = false;
bool Jump::isRDoing = false;

bool Jump::update(Vec2 _myPos, Vec2 _oppPos) {
	return Bullet::update(_myPos, _oppPos);
}

void Jump::draw() {
	// no draw
}

bool Jump::isVisible() {
	return ((isLeft ? isLInvalid : isRInvalid) && (System::FrameCount() % 1000 == frameCount));
}

int Jump::getDamage(Circle _circle) {
	return 0; // no damage
}

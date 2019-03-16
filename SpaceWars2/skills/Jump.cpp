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
	if (!(isLeft ? isLDoing : isRDoing) || (System::FrameCount() % 1000 != frameCount))
		return false;
	else
		return true;
}

int Jump::getDamage(Circle _circle) {
	return 0; // no damage
}

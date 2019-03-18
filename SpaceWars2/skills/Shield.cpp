#include "./Shield.hpp"

bool Shield::isLDoing = false;
bool Shield::isRDoing = false;

bool Shield::update(Vec2 _myPos, Vec2 _oppPos) {
	pos = _myPos;
	++frameCount;
	damage = (isLeft ? Data::LPlayer : Data::RPlayer).changeHitSize(108);
	return Bullet::update(_myPos, _oppPos);
}

void Shield::draw() {
	getShape().draw(Color(L"#88888844"));
}

bool Shield::isVisible() {
	if (isLeft ? isLInvalid : isRInvalid)
		return false;

	if (damage > 50)
		return false;

	return true;
}

int Shield::getDamage(Circle _circle) {
	return 0; // no damage
}

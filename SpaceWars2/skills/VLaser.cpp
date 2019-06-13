#include "./VLaser.hpp"
#include "../CommonData.hpp"
#include "../functions/XInput.hpp"

bool VLaser::isLShooting = false;
bool VLaser::isRShooting = false;

bool VLaser::update(Vec2 _myPos, Vec2 _oppPos) {
	myPos = shrinkVec2(_myPos);
	if (isCharging) {
		++energy;
		if (energy >= 60) isCharging = false;
	}
	else {
		--energy;
	}

	return Bullet::update(_myPos, _oppPos);
}

void VLaser::draw() {
	if (!isCharging)
		getShapeShotten().draw(HSV(60 - (energy / 3), 1, 1));
	else
		getShapeCharging().draw(HSV(60 - (energy / 3), 1, 1));
}

int VLaser::getDamage(Circle _circle) {
	if (isCharging)	return 0;
	if (_circle.intersects(getShapeShotten()) || _circle.intersects(getShapeCharging()))
		return 2;
	else
		return 0;
}

bool VLaser::isVisible() {
	if (isLeft ? isLInvalid : isRInvalid) return false;
	if (energy <= 0) return false;
	return true;
}

Vec2 VLaser::shrinkVec2(Vec2 _d) {
	RectF screen(0, 0 , Window::Width(), Window::Height());
	Vec2 dis = _d.asPoint() - screen.center;
	_d = dis * shrinkRate + activeField.center;
	return _d;
}

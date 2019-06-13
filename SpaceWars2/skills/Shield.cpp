#include "./Shield.hpp"

bool Shield::isLDoing = false;
bool Shield::isRDoing = false;

bool Shield::update(Vec2 _myPos, Vec2 _oppPos) {
	pos = shrinkVec2(_myPos);
	++frameCount;
	++(isLeft ? Data::LPlayer : Data::RPlayer).coolDownTime;
	damage = (isLeft ? Data::LPlayer : Data::RPlayer).changeHitSize(108);
	return Bullet::update(_myPos, _oppPos);
}

void Shield::draw() {
	getShape().draw(ColorF(L"#888888").setAlpha(0.5));
}

bool Shield::isVisible() {
	if (isLeft ? isLInvalid : isRInvalid)
		return false;

	if (damage > 200)
		return false;

	return true;
}

int Shield::getDamage(Circle _circle) {
	(void)_circle;
	return 0; // no damage
}

Vec2 Shield::shrinkVec2(Vec2 _d) {
	RectF screen(0, 0 , Window::Width(), Window::Height());
	Vec2 dis = _d.asPoint() - screen.center;
	_d = dis * shrinkRate + activeField.center;
	return _d;
}

Vec2 Shield::shrink(Rect _area){
	Bullet::shrink(_area);
	drawRate = shrinkRate * 2;
	vel *= 2;
	return pos;
}

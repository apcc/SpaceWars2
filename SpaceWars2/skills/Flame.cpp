#include "./Flame.hpp"

bool Flame::update(Vec2 myPos, Vec2 oppPos) {

	return Bullet::update(myPos, oppPos);
}

void Flame::draw() {
	//getShapeFlameBelt().draw(Color(L"#ff8800"));
	getShapeFlameBelt().draw({ Color(L"#ff8800"), Color(0, 32), Color(0, 32), Color(L"#ff8800"), });
	getShape().draw(Color(L"#ffff00"));
};

bool Flame::isVisible() {
	return getShape().intersects(Rect(0 - bulletSpeed * 60, 0, Config::WIDTH + 1 + bulletSpeed * 120, Config::HEIGHT + 1));
	//暗すぎる部分だけの場合は消してます
}

RectF normalizeRect(RectF rect) {// namae kimete chanto basho kaeyoune
	if (rect.w < 0) {
		rect.x = rect.x + rect.w;
		rect.w = -rect.w;
	}

	if (rect.h < 0) {
		rect.y = rect.y + rect.h;
		rect.h = -rect.h;
	}
	return rect;
}


int Flame::getDamage(Circle circle) {
	if (circle.intersects(this->getShape())) {
		shouldBeDestroyed = true;
		return 10;
	}
	if (circle.intersects(normalizeRect(getShapeFlameBelt()))) {
		return 1;
	}
	return 0;
}

#include "./Flame.hpp"

bool Flame::update(Vec2 myPos, Vec2 oppPos) {

	return Bullet::update(myPos, oppPos);
}

void Flame::draw() {
	//getShapeFlameBelt().draw(Color(L"#ff8800"));
	getShapeFlameBelt().draw({ Color(L"#ff8800"), Color(L"#ff8800").setAlpha(16), Color(L"#ff8800").setAlpha(16), Color(L"#ff8800"), });
	//getShape().draw(Color(L"#ffff00"));
	if (isLeft) {
		TextureAsset(L"mainBullet4").resize(200 * shrinkRate, 200 * shrinkRate).drawAt(pos - Vec2(40*shrinkRate, 10*shrinkRate));
	}
	else {
		TextureAsset(L"mainBullet4").resize(200 * shrinkRate, 200 * shrinkRate).mirror().drawAt(pos - Vec2(-40*shrinkRate, 10*shrinkRate));
	}
};

bool Flame::isVisible() {
	return getShape().intersects(shrinkRate==1 ? Rect(0 - bulletSpeed * 60, 0, Config::WIDTH + 1 + bulletSpeed * 120, Config::HEIGHT + 1) : activeField);
	//暗すぎる部分だけの場合は消してます
	//説明時は、実装の都合で球がエリア内にあるかないかで判断しています
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
		return 50;
	}
	if (circle.intersects(normalizeRect(getShapeFlameBelt()))) {
		return 2;
	}
	return 0;
}

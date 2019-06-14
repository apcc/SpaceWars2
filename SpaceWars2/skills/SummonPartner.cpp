#include "./SummonPartner.hpp"
#include "Grenade.hpp"
#include "../CommonData.hpp"

bool SummonPartner::update(Vec2 myPos, Vec2 oppPos) {
	pos.x = shrinkVec2(myPos).x;
	pos.y += (shrinkVec2(oppPos).y > pos.y ? 3*moveRate : -3*moveRate);
	LifeTime--;
	if (!(LifeTime % 30)) {
		Bullet* bul = new Grenade(shrinkVec2(pos, activeField, Rect(0, 0, Window::Width(), Window::Height())), isLeft);
		if(shrinkRate!=1) bul->shrink(activeField);
		bullets.push_back(bul);
	}
	for(auto itr = bullets.begin(); itr != bullets.end();){
		if((**itr).update(myPos, oppPos)){
			delete *itr;
			itr = bullets.erase(itr);
		}else{
			++itr;
		}
	}

	return Bullet::update(myPos, oppPos);
}

void SummonPartner::draw() {
	for(auto bul : bullets){
		bul->draw();
	}
	if (isLeft) {
		if (shrinkRate == 1)TextureAsset(L"fire").drawAt(pos + Vec2(-60, 0));
		TextureAsset(L"specialBullet2").resize(60*drawRate, 60*drawRate).drawAt(pos);
	}
	else {
		if (shrinkRate == 1)TextureAsset(L"fire").mirror().drawAt(pos + Vec2(60, 0));
		TextureAsset(L"specialBullet3").resize(60*drawRate, 60*drawRate).drawAt(pos);
	}
	//getShape().draw(ColorF(isLeft?L"#ff0000":L"#0000ff").setAlpha(0.5));
}

bool SummonPartner::isVisible() {
	return LifeTime>0;
}

int SummonPartner::getDamage(Circle circle) {
	int _damage = 0;
	for (auto i : bullets) {
		_damage += i->getDamage(circle);
	}
	return _damage;
}

Vec2 SummonPartner::shrinkVec2(Vec2 _d) {
	RectF screen(0, 0, Window::Width(), Window::Height());
	Vec2 dis = _d.asPoint() - screen.center;
	_d = dis * shrinkRate + activeField.center;
	return _d;
}

Vec2 SummonPartner::shrinkVec2(
	Vec2 _d, 
	Rect _from, 
	Rect _to
) {
	Vec2 dis = _d.asPoint() - _from.center;
	double rate = (double)_to.w / _from.w;
	_d = dis * rate + _to.center;
	return _d;
}

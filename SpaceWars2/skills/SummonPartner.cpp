#include "./SummonPartner.hpp"
#include "Grenade.hpp"
#include "../CommonData.hpp"

bool SummonPartner::update(Vec2 myPos, Vec2 oppPos) {
	pos.x = myPos.x;
	pos.y += (oppPos.y > pos.y ? 3 : -3);
	LifeTime--;
	if(!(LifeTime%30)) bullets.push_back(new Grenade(pos, isLeft));
	for(auto itr = bullets.begin(); itr != bullets.end();){
		if((**itr).update(myPos, oppPos)){
			delete *itr;
			itr = bullets.erase(itr);
		}else{
			itr++;
		}
	}

	return Bullet::update(myPos, oppPos);
}

void SummonPartner::draw() {
	for(auto bul : bullets){
		bul->draw();
	}
	getShape().draw(ColorF(isLeft?L"#ff0000":L"#0000ff").setAlpha(0.5));
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

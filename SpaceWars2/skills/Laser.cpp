#include "./Laser.hpp"
#include "../CommonData.hpp"
#include "../functions/XInput.hpp"

bool Laser::isLShooting = false;
bool Laser::isRShooting = false;

bool Laser::update(Vec2 _myPos, Vec2 _oppPos) {
	myPos = _myPos;
	if(isCharging){
		if (GamePad::Key(isLeft, L"MainSkill") && (isLeft ? Data::LPlayer : Data::RPlayer).temperature < 800 && !(isLeft ? isLInvalid : isRInvalid)) {
			++energy;
			(isLeft ? Data::LPlayer : Data::RPlayer).temperature += 6;
		}
		else {
			isCharging = false;
		}
	}else{
		--energy;
		if (energy < 0) energy = 0;
		if (!(isLeft ? isLInvalid : isRInvalid))
			(isLeft ? Data::LPlayer : Data::RPlayer).temperature -= 2;
	}

	if(energy >= 180) isCharging = false;

	return Bullet::update(_myPos, _oppPos);
}

void Laser::draw(){
	if(!isCharging)
		getShapeShotten().draw(HSV(60 - (energy / 3), 1, 1));
	else
		getShapeCharging().draw(HSV(60 - (energy / 3), 1, 1));
}

int Laser::getDamage(Circle _circle){
	if(isCharging)	return 0;
	if(_circle.intersects(getShapeShotten()) || _circle.intersects(getShapeCharging()))
		return 2;
	else
		return 0;
}

bool Laser::isVisible(){
	if (isLeft ? isLInvalid : isRInvalid) return false;
	if (energy <= 0) return false;
	return true;
}

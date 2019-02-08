#include "./Laser.hpp"

bool Laser::isInvoked = false;

bool Laser::update() {
	if(isCharging){
		if((isLeft && Input::KeyQ.pressed) || (!isLeft && Input::KeyI.pressed)){
			++energy;
		}else{
			isCharging = false;
		}
	}else{
		--energy;
		if (energy < 0) energy = 0;
	}

	if(energy >= 180) isCharging = false;

	return Bullet::update();
}

void Laser::draw(){
	if(!isCharging)
		getShapeShooten().draw(HSV(60 - (energy / 3), 1, 1));
	else
		getShapeCharging().draw(HSV(60 - (energy / 3), 1, 1));
}

int Laser::getDamage(Circle circle){
	if(isCharging)	return 0;
	if(circle.intersects(getShapeShooten()) || circle.intersects(getShapeCharging()))
		return 1;
	else
		return 0;
}

bool Laser::isInvisible(){
	if (isInvalid)   return true;
	if (energy <= 0) return true;
	return false;
}

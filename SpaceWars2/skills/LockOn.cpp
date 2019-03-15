#include "./LockOn.hpp"

bool LockOn::update(Vec2 myPos, Vec2 oppPos) {
	if(waitTime<0){
		if(--explodeTime <= -30){
			shouldBeDestroyed = true;
		}
	}else if(waitTime == 0){
		pos = oppPos;
		waitTime--;
	}else{
		waitTime--;
		pos = oppPos;
	}
	return Bullet::update(myPos, oppPos);
}

void LockOn::draw() {
	if(waitTime <= 0){
		if(explodeTime > 0){
			getShape().draw(ColorF(L"#ff8800").setAlpha(((double)30 - explodeTime) / EXPLODE_TIMING / 2));
		}else{
			getShape().draw(ColorF(L"#ff0000").setAlpha(((double)30 + explodeTime)/ EXPLODE_TIMING / 2));
		}
	}else{
	}
	return;
}

bool LockOn::isInvisible() {
	return false;
}

int LockOn::getDamage(Circle circle) {
	if(explodeTime == 0){
		if(circle.intersects(this->getShape())){
			return 30;
		}
	}
	return 0;
}

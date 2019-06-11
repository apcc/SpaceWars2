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
			TextureAsset(L"specialBullet1").resize(400, 400).drawAt(pos);
		}else{
			getShape().draw(ColorF(L"#ff0000").setAlpha(((double)30 + explodeTime)/ EXPLODE_TIMING / 2));
		}
	}else{
	}
	return;
}

bool LockOn::isVisible() {
	return true;
}

int LockOn::getDamage(Circle circle) {
	if(explodeTime == 0){
		if(circle.intersects(this->getShape())){
			return 75;
		}
	}
	return 0;
}

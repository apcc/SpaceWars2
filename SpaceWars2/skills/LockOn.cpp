#include "./LockOn.hpp"

bool LockOn::update(Vec2 myPos, Vec2 oppPos) {
	oppPos = ShrinkVec2(oppPos);
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
			TextureAsset(L"specialBullet1").resize(400*shrinkRate, 400*shrinkRate).drawAt(pos);
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

Vec2 LockOn::ShrinkVec2(Vec2 _d) {
	RectF screen(0, 0, Window::Width(), Window::Height());
	Vec2 dis = _d.asPoint() - screen.center;
	_d = dis * shrinkRate + activeField.center;
	return _d;
}

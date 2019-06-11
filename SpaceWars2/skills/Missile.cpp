#include "./Missile.hpp"
#include "../functions/Vec2Utils.hpp"

bool Missile::update(Vec2 myPos, Vec2 oppPos) {
	/*angle += */bend(/*Circle(myPos, 300), */ShrinkVec2(oppPos), 300*shrinkRate);
	return Bullet::update(myPos, oppPos);
}

void Missile::draw() {
	getShape().draw(Color(L"#00ff00"));
}

bool Missile::isVisible() {
	return getShape().intersects(activeField);
}

int Missile::getDamage(Circle circle) {
	if (circle.intersects(this->getShape())) {
		shouldBeDestroyed = true;
		return 20;
	}
	return 0;
}

/*int*/void Missile::bend(Vec2 oppPos, double thre) {
	if ((pos - oppPos).length() < thre) {
		//(vel.normalized()*100).draw(ColorF(L"ff0000"));

		double angle = AngleNormalize(Vec2Angle(vel) - Vec2Angle(oppPos - pos));// Atan2(vel.y, vel.x);

		if (angle > EPS) {
			//return -20;
			vel.rotate(-ROTATEPOWER);
		}
		else  if (angle < -EPS) {
			//return 20;
			vel.rotate(ROTATEPOWER);
		}
	}
	else {

		//return 0;
	}
}

Vec2 Missile::ShrinkVec2(Vec2 _d) {
	RectF screen(0, 0 , Window::Width(), Window::Height());
	Vec2 dis = _d.asPoint() - screen.center;
	_d = dis * shrinkRate + activeField.center;
	return _d;
}

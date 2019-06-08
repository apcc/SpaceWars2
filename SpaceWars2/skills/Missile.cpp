#include "./Missile.hpp"
#include "../functions/Vec2Utils.hpp"

bool Missile::update(Vec2 myPos, Vec2 oppPos) {
	/*angle += */bend(/*Circle(myPos, 300), */oppPos, 300);
	return Bullet::update(myPos, oppPos);
}

void Missile::draw() {
	if (isLeft)
		TextureAsset(L"subBullet2").resize(30, 30).rotate(Vec2Angle(vel)).drawAt(pos);
	else
		TextureAsset(L"subBullet2").resize(30, 30).rotate(Vec2Angle(vel)).drawAt(pos);
}

bool Missile::isVisible() {
	return getShape().intersects(Rect(0, 0, Config::WIDTH + 1, Config::HEIGHT + 1));
}

int Missile::getDamage(Circle circle) {
	if (circle.intersects(this->getShape())) {
		shouldBeDestroyed = true;
		return 20;
	}
	return 0;
}

void Missile::bend(Vec2 oppPos, double thre) {
	if ((pos - oppPos).length() < thre) {
		//(vel.normalized()*100).draw(ColorF(L"ff0000"));

		double angle = AngleNormalize(Vec2Angle(vel) - Vec2Angle(oppPos - pos));// Atan2(vel.y, vel.x);

		if (angle > EPS) {
			vel.rotate(-ROTATEPOWER);
		}
		else  if (angle < -EPS) {
			vel.rotate(ROTATEPOWER);
		}
	}
}

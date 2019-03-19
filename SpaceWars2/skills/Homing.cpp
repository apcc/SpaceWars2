#include "./Homing.hpp"
#include "../functions/Vec2Utils.hpp"

bool Homing::update(Vec2 myPos, Vec2 oppPos) {
	/*angle += */bend(/*Circle(myPos, 300), */oppPos, 300);
	return Bullet::update(myPos, oppPos);
}

void Homing::draw() {
	getShape().draw(Color(L"#00ff00"));
}

bool Homing::isVisible() {
	return getShape().intersects(Rect(0, 0, Config::WIDTH + 1, Config::HEIGHT + 1));
}

int Homing::getDamage(Circle circle) {
	if (circle.intersects(this->getShape())) {
		shouldBeDestroyed = true;
		return 1;
	}
	return 0;
}

/*int*/void Homing::bend(Vec2 oppPos, double thre) {
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
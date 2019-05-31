#include "./Bomb.hpp"

int Bomb::numberOfLUsed = 0;
int Bomb::numberOfRUsed = 0;

bool Bomb::update(Vec2 _myPos, Vec2 _oppPos) {
	BombUsed = (isLeft) ? numberOfLUsed : numberOfRUsed;
	if (explosion) {
		fuse++;
	}
	if (isLeft) {
		if (pos.x >= Window::Center().x + 75 + nowBombNumber % 4 * 160) {
			vel.set(0, 0);
		}
	}
	else {
		if (pos.x <= Window::Center().x - 75 - nowBombNumber % 4 * 160) {
			vel.set(0, 0);
		}
	}
	return Bullet::update(_myPos, _oppPos);

}

void Bomb::draw() {
	if (explosion) {
		getShape().draw(ColorF(L"#ff8800").setAlpha((255 - (double)fuse * 4) / 64));
	}
	else {
		getShape().draw(ColorF(L"#00ff00"));
	}
}

bool Bomb::isVisible() {
	if (nowBombNumber <= BombUsed - 4) {
		return false;
	}
	if (fuse == 60) {
		fuse = 0;
		explosion = false;
		return false;
	}
	else {
		return getShape().intersects(Rect(0, 0, Config::WIDTH + 1, Config::HEIGHT + 1));
	}
}

int Bomb::getDamage(Circle _circle) {
	if (_circle.intersects(this->getShape())) {
		explosion = true;
		vel.set(0, 0);
		if (explosion) {
			if (fuse == 0) {
				return 70;
			}
		}
	}
	return 0;
}

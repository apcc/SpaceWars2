#include "./JudgmentTime.hpp"

bool JudgmentTime::update(Vec2 _myPos, Vec2 _oppPos){
	pos = _oppPos;
	--lifeTime;

	return Bullet::update(_myPos, _oppPos);
}

void JudgmentTime::draw(){
	Rect(Window::Size()).draw(ColorF(L"#cccccc").setAlpha(REVERSE_PLAYER.judgmentLife / 100.0));
}

bool JudgmentTime::isVisible() {
	return lifeTime != 0;
}

int JudgmentTime::getDamage(Circle _circle){
	(void)_circle;
	return 0;
}

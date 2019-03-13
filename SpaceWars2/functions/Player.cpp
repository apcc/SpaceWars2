#include "./Player.hpp"

#define PLAYER_SPEED 15
#define NUMBER_OF_SKILL 3
#define HP_LIMIT 100.0
#define GAUGE_WIDTH (Config::WIDTH / 2.0 / HP_LIMIT)

void Player::init(Vec2 _pos, bool _isLeft){
	pos = _pos;
	isLeft = _isLeft;
	HP = 100;
	whatMainSkill = static_cast<MainSkill>(0);
	whatSubSkill = static_cast<SubSkill>(0);
	whatSpecialSkill = static_cast<SpecialSkill>(0);
}

Circle Player::circle(){
	return Circle(pos, 30);
}

void Player::receiveDamage(int _damage){
	HP -= _damage;
	if (HP < 0) HP = 0;
}

bool Player::isHPRunOut(){
	return !HP;
}

void Player::update(std::vector<Bullet*> &bullets){
	Rect zone;
	Vec2 tmp = pos;
	if(isLeft){
		zone = Rect(0, 0, Config::WIDTH / 2 + 1, Config::HEIGHT + 1);
		if(Input::KeyD.pressed)			pos.x += PLAYER_SPEED;
		if(Input::KeyA.pressed)			pos.x -= PLAYER_SPEED;
		if (!zone.contains(Player::circle()))
			pos = tmp;
		tmp = pos;
		if(Input::KeyW.pressed)			pos.y -= PLAYER_SPEED;
		if(Input::KeyS.pressed)			pos.y += PLAYER_SPEED;
		if (!zone.contains(Player::circle()))
			pos = tmp;
		tmp = pos;
	}else{
		zone = Rect(Config::WIDTH/2, 0, Config::WIDTH / 2 + 1, Config::HEIGHT + 1);
		if(Input::KeySemicolon.pressed)	pos.x += PLAYER_SPEED;
		if(Input::KeyK.pressed)			pos.x -= PLAYER_SPEED;
		if (!zone.contains(Player::circle()))
			pos = tmp;
		tmp = pos;
		if(Input::KeyO.pressed)			pos.y -= PLAYER_SPEED;
		if(Input::KeyL.pressed)			pos.y += PLAYER_SPEED;
		if (!zone.contains(Player::circle()))
			pos = tmp;
		tmp = pos;
	}
	//pos.x=max(tmpZoon.x)


	if(isLeft){
		if(Input::KeyQ.pressed)			doMainSkill(bullets);
		if(Input::KeyE.pressed)			doSubSkill(bullets);
		if(Input::KeyLShift.pressed)	doSpacialSkill(bullets);
	}else{
		if(Input::KeyI.pressed)			doMainSkill(bullets);
		if(Input::KeyP.pressed)			doSubSkill(bullets);
		if(Input::KeyRShift.pressed)	doSpacialSkill(bullets);
	}

	for (auto i : bullets) {
		if(isLeft == i->isLeft) continue;
		int damage = i->getDamage(this->circle());
		if(damage){
			this->receiveDamage(damage);
		}

	}
}

void Player::skillSelect(){

	switch(selectedType){
		case 0:	//MainSkill
			if(isLeft){
				//if(Input::KeyW.clicked)
				if(Input::KeyS.clicked)	++selectedType;
				if(Input::KeyA.clicked && whatMainSkill < NUMBER_OF_SKILL)	whatMainSkill = static_cast<MainSkill>(whatMainSkill + 1);
				if(Input::KeyD.clicked && whatMainSkill > 0)				whatMainSkill = static_cast<MainSkill>(whatMainSkill - 1);
			}else{
				//if(Input::KeyO.clicked)
				if(Input::KeyL.clicked)	++selectedType;
				if(Input::KeyK.clicked && whatMainSkill < NUMBER_OF_SKILL)	whatMainSkill = static_cast<MainSkill>(whatMainSkill + 1);
				if(Input::KeySemicolon.clicked && whatMainSkill > 0)		whatMainSkill = static_cast<MainSkill>(whatMainSkill - 1);
			}
		break;

		case 1:	//SubSkill
			if(isLeft){
				if(Input::KeyW.clicked)	--selectedType;
				if(Input::KeyS.clicked)	++selectedType;
				if(Input::KeyA.clicked && whatSubSkill < NUMBER_OF_SKILL)	whatSubSkill = static_cast<SubSkill>(whatSubSkill + 1);
				if(Input::KeyD.clicked && whatSubSkill > 0)					whatSubSkill = static_cast<SubSkill>(whatSubSkill - 1);
			}else{
				if(Input::KeyO.clicked)	--selectedType;
				if(Input::KeyL.clicked)	++selectedType;
				if(Input::KeyK.clicked && whatSubSkill < NUMBER_OF_SKILL)	whatSubSkill = static_cast<SubSkill>(whatSubSkill + 1);
				if(Input::KeySemicolon.clicked && whatSubSkill > 0)			whatSubSkill = static_cast<SubSkill>(whatSubSkill - 1);
			}
		break;

		case 2:	//SpecialSkill
			if(isLeft){
				if(Input::KeyW.clicked)	--selectedType;
				//if(Input::KeyS.clicked)
				if(Input::KeyA.clicked && whatSpecialSkill < NUMBER_OF_SKILL)	whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill + 1);
				if(Input::KeyD.clicked && whatSpecialSkill > 0)					whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill - 1);
			}else{
				if(Input::KeyO.clicked)	--selectedType;
				//if(Input::KeyL.clicked)
				if(Input::KeyK.clicked && whatSpecialSkill < NUMBER_OF_SKILL)	whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill + 1);
				if(Input::KeySemicolon.clicked && whatSpecialSkill > 0)			whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill - 1);
			}
		break;

		default:
			LOG(L"[ERROR] SkillSelecterで意図しない値が参照されました。");
	}
}

void Player::drawShip(){
	if(isLeft){
		circle().draw(Color(L"#ff0000"));
	}else{
		circle().draw(Color(L"#0000ff"));
	}
}

void Player::drawGauge(){
	if(isLeft){
		RectF(0, 0,  HP * GAUGE_WIDTH, 20).draw(Color(L"#ff0000"));
	}else{
		RectF(Config::WIDTH - HP * GAUGE_WIDTH, 0,  Config::WIDTH, 20).draw(Color(L"#ff0000"));
	}
}

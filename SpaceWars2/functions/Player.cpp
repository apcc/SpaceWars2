#include "./Player.hpp"
#include "./XInput.hpp"

#define PLAYER_SPEED 15
#define NUMBER_OF_SKILL 6
#define HP_LIMIT 100.0
#define GAUGE_WIDTH (Config::WIDTH / 2.0 / HP_LIMIT)

void Player::init(Vec2 _pos, bool _isLeft){
	pos = _pos;
	isLeft = _isLeft;
	HP = 100;
	speed = PLAYER_SPEED;
	whatMainSkill = static_cast<MainSkill>(0);
	whatSubSkill = static_cast<SubSkill>(0);
	whatSpecialSkill = static_cast<SpecialSkill>(0);

	Controller::SetAxis();
	Controller::SetButton();
}

Circle Player::circle(){
	return Circle(pos, PLAYER_SIZE);
}

Circle Player::hitCircle(){
	return Circle(pos, hitSize);
}


void Player::receiveDamage(int _damage){
	if (hitSize == 30)	// hitSize is default
		HP -= _damage;
	else
		shieldDamage += _damage;
	
	if (HP < 0) HP = 0;
}

void Player::changeSpeed(int _speed) {
	speed = _speed;
}

int Player::changeHitSize(int _hitSize){
	hitSize = _hitSize;

	if (hitSize == 30)
		shieldDamage = 0;

	return shieldDamage;
}


bool Player::isHPRunOut(){
	return !HP;
}

void Player::update(std::vector<Bullet*> &bullets){
	pos += Controller::Move(isLeft, speed);

	/*
	// Rect zone;
	// Vec2 tmp = pos;
	if(isLeft){
		// zone = Rect(0, 0, Config::WIDTH / 2 + 1, Config::HEIGHT + 1);

		

		// if (!zone.contains(Player::circle()))	pos.x  = Config::WIDTH / 2 - PLAYER_SIZE;
		// if (!zone.contains(Player::circle()))	pos.x  = 0 + PLAYER_SIZE;

		// if (!zone.contains(Player::circle()))	pos.y  = 0 + PLAYER_SIZE;
		// if (!zone.contains(Player::circle()))	pos.y  = Config::HEIGHT - PLAYER_SIZE;
	}else{
		// zone = Rect(Config::WIDTH/2, 0, Config::WIDTH / 2 + 1, Config::HEIGHT + 1);


		// if (!zone.contains(Player::circle()))	pos.x  = Config::WIDTH - PLAYER_SIZE;
		// if (!zone.contains(Player::circle()))	pos.x  = Config::WIDTH / 2 + PLAYER_SIZE;

		// if (!zone.contains(Player::circle()))	pos.y = 0 + PLAYER_SIZE;
		// if (!zone.contains(Player::circle()))	pos.y = Config::HEIGHT - PLAYER_SIZE;
	}
	*/


	if (Controller::Skill(isLeft, L"MainSkill"))		doMainSkill(bullets);
	if (Controller::Skill(isLeft, L"SubSkill"))		doSubSkill(bullets);
	if (Controller::Skill(isLeft, L"SpecialSkill"))	doSpacialSkill(bullets);

	for (auto i : bullets) {
		if(isLeft == i->isLeft) continue;
		int damage = i->getDamage(this->hitCircle());
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

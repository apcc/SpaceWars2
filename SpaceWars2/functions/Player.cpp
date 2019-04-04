#include "./Player.hpp"
#include "../CommonData.hpp"
#define PLAYER_SPEED 15
#define NUMBER_OF_SKILL 6
#define GAUGE_LIMIT 1000.0
#define GAUGE_WIDTH (Config::WIDTH / 2.0 / GAUGE_LIMIT)

void Player::init(Vec2 _pos, bool _isLeft){
	pos = _pos;
	isLeft = _isLeft;
	HP = 1000;
	temperature = 200;
	coolDownTime = 0;
	charge = 0;
	speed = PLAYER_SPEED;
	whatMainSkill = static_cast<MainSkill>(0);
	whatSubSkill = static_cast<SubSkill>(0);
	whatSpecialSkill = static_cast<SpecialSkill>(0);

	GamePad::SetAxis();
	GamePad::SetButton();

	KeyUp = KeyRepeat(isLeft, L"KeyUp");
	KeyLeft = KeyRepeat(isLeft, L"KeyLeft");
	KeyDown = KeyRepeat(isLeft, L"KeyDown");
	KeyRight = KeyRepeat(isLeft, L"KeyRight");

	KeyMainSkill = KeyRepeat(isLeft, L"MainSkill");
	KeySubSkill = KeyRepeat(isLeft, L"SubSkill");
	KeySpecialSkill = KeyRepeat(isLeft, L"SpecialSkill");
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
	pos += GamePad::Move(isLeft, speed);


	if(isLeft) {
		if (pos.x < 0 + PLAYER_SIZE)
			pos.x = 0 + PLAYER_SIZE;
		if (pos.x > Config::WIDTH / 2 - PLAYER_SIZE)
			pos.x = Config::WIDTH / 2 - PLAYER_SIZE;
	} else {
		if (pos.x < Config::WIDTH / 2 + PLAYER_SIZE)
			pos.x = Config::WIDTH / 2 + PLAYER_SIZE;
		if (pos.x > Config::WIDTH - PLAYER_SIZE)
			pos.x = Config::WIDTH - PLAYER_SIZE;
	}

	if (pos.y < 0 + PLAYER_SIZE)
		pos.y = 0 + PLAYER_SIZE;
	if (pos.y > Config::HEIGHT - PLAYER_SIZE)
		pos.y = Config::HEIGHT - PLAYER_SIZE;

	if (temperature > 100)
		--temperature;

	if (temperature  <  800) doMainSkill(bullets);
	if (coolDownTime <    0) doSubSkill(bullets);
	doSpacialSkill(bullets);

	for (auto i : bullets) {
		if(isLeft == i->isLeft) continue;
		int damage = i->getDamage(this->hitCircle());
		if(damage){
			this->receiveDamage(damage);
			charge += damage;
			if(charge >= requireCharge[whatSpecialSkill]){
				charge = requireCharge[whatSpecialSkill];
			}
		}

	}
}

void Player::skillSelect(){

	switch(selectedType){
	case 0:	//MainSkill
		if (KeyDown.repeat(20))	++selectedType;
		if (KeyLeft.repeat(20) && whatMainSkill < NUMBER_OF_SKILL)	whatMainSkill = static_cast<MainSkill>(whatMainSkill + 1);
		if (KeyRight.repeat(20) && whatMainSkill > 0)				whatMainSkill = static_cast<MainSkill>(whatMainSkill - 1);
		break;

	case 1:	//SubSkill
		if (KeyUp.repeat(20))	--selectedType;
		if (KeyDown.repeat(20))	++selectedType;
		if (KeyLeft.repeat(20) && whatSubSkill < NUMBER_OF_SKILL)	whatSubSkill = static_cast<SubSkill>(whatSubSkill + 1);
		if (KeyRight.repeat(20) && whatSubSkill > 0)				whatSubSkill = static_cast<SubSkill>(whatSubSkill - 1);
		break;

	case 2:	//SpecialSkill
		if (KeyUp.repeat(20))	--selectedType;
		if (KeyLeft.repeat(20) && whatSpecialSkill < NUMBER_OF_SKILL)	whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill + 1);
		if (KeyRight.repeat(20) && whatSpecialSkill > 0)				whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill - 1);
		break;

	default:
			LOG_ERROR(L"SkillSelecterで意図しない値が参照されました。");
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
	if (isLeft) {
		RectF(0, 0, HP * GAUGE_WIDTH, 20).draw(Color(L"#ff0000"));
		RectF(0, 25, temperature * GAUGE_WIDTH, 20).draw(Color(L"#00ff00"));
		RectF(0, 50, coolDownTime * GAUGE_WIDTH, 20).draw(Color(L"#0000ff"));
		RectF(0, 75, (charge * 100) / requireCharge[whatSpecialSkill] * GAUGE_WIDTH, 20).draw(Color(L"#ffff00"));
	}
	else {
		RectF(Config::WIDTH - HP * GAUGE_WIDTH, 0, Config::WIDTH, 20).draw(Color(L"#ff0000"));
		RectF(Config::WIDTH - temperature * GAUGE_WIDTH, 25, Config::WIDTH, 20).draw(Color(L"#00ff00"));
		RectF(Config::WIDTH - coolDownTime * GAUGE_WIDTH, 05, Config::WIDTH, 80).draw(Color(L"#0000ff"));
		RectF(Config::WIDTH - (charge * 100) / requireCharge[whatSpecialSkill] * GAUGE_WIDTH, 75, Config::WIDTH, 20).draw(Color(L"#ffff00"));
	}
}

#include "./Player.hpp"
#include "../CommonData.hpp"
#define PLAYER_SPEED 15
#define NUMBER_OF_SKILL 6
#define GAUGE_LIMIT 1000.0
#define GAUGE_WIDTH (Config::WIDTH / 2.0 / GAUGE_LIMIT)

bool Player::inJudgmentTime = false;

void Player::init(Vec2 _pos, bool _isLeft){
	pos = _pos;
	isLeft = _isLeft;
	HP = 1000;
	temperature = 200;
	coolDownTime = 0;
	charge = 0;
	speed = PLAYER_SPEED;
	inRecovery = false;
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
	if(speed == 0) {
		inJudgmentTime = true;
		judgmentLife = JT_TIME;
	}
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

	if (speed != 0) {
		if (temperature < 800) doMainSkill(bullets);
		if (coolDownTime == 0) doSubSkill(bullets);
		else	coolDownTime--;
		doSpacialSkill(bullets);
	}

	if (inJudgmentTime) {
		if(judgmentLife == 0) {
			inJudgmentTime = false;
		}
		--judgmentLife;
		Println(judgmentLife);
	}

	if (!inJudgmentTime) {
		for (auto i : bullets) {
			if (isLeft == i->isLeft) continue;
			int damage = i->getDamage(this->hitCircle());
			if (damage) {
				this->receiveDamage(damage);
				charge += damage;
				if (charge >= requireCharge[whatSpecialSkill]) {
					charge = requireCharge[whatSpecialSkill];
				}
			}
		}
	}
}

void Player::skillSelect(){

	switch(selectedType){
	case 0:	//MainSkill
		if (KeyDown	.repeat(20, true)) ++selectedType;
		if (KeyLeft	.repeat(20, true) && whatMainSkill < NUMBER_OF_SKILL)	whatMainSkill = static_cast<MainSkill>(whatMainSkill + 1);
		if (KeyRight.repeat(20, true) && whatMainSkill > 0)				whatMainSkill = static_cast<MainSkill>(whatMainSkill - 1);
		break;

	case 1:	//SubSkill
		if (KeyUp	.repeat(20, true)) --selectedType;
		if (KeyDown	.repeat(20, true)) ++selectedType;
		if (KeyLeft	.repeat(20, true) && whatSubSkill < NUMBER_OF_SKILL)	whatSubSkill = static_cast<SubSkill>(whatSubSkill + 1);
		if (KeyRight.repeat(20, true) && whatSubSkill > 0)					whatSubSkill = static_cast<SubSkill>(whatSubSkill - 1);
		break;

	case 2:	//SpecialSkill
		if (KeyUp	.repeat(20, true)) --selectedType;
		if (KeyLeft	.repeat(20, true) && whatSpecialSkill < NUMBER_OF_SKILL)	whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill + 1);
		if (KeyRight.repeat(20, true) && whatSpecialSkill > 0)					whatSpecialSkill = static_cast<SpecialSkill>(whatSpecialSkill - 1);
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
	Color chargeColor = Color(charge==requireCharge[whatSpecialSkill]? L"#ffd000" : L"#ffff00" );
	if (isLeft) {
		RectF(0, 0, HP * GAUGE_WIDTH, 20).draw(Color(L"#ff0000"));
		RectF(0, 20, temperature * GAUGE_WIDTH, 20).draw(Color(L"#00ff00"));
		RectF(0, 40, (coolDownTime>1000 ? 1000 : coolDownTime) * GAUGE_WIDTH, 20).draw(Color(L"#0000ff"));
		RectF(0, 60, (charge * GAUGE_LIMIT) / requireCharge[whatSpecialSkill] * GAUGE_WIDTH, 20).draw(chargeColor);
	}
	else {
		RectF(Config::WIDTH - HP * GAUGE_WIDTH, 0, Config::WIDTH, 20).draw(Color(L"#ff0000"));
		RectF(Config::WIDTH - temperature * GAUGE_WIDTH, 20, Config::WIDTH, 20).draw(Color(L"#00ff00"));
		RectF(Config::WIDTH - coolDownTime * GAUGE_WIDTH, 40, Config::WIDTH, 20).draw(Color(L"#0000ff"));
		RectF(Config::WIDTH - (charge * GAUGE_LIMIT) / requireCharge[whatSpecialSkill] * GAUGE_WIDTH, 60, Config::WIDTH, 20).draw(chargeColor);
	}
}

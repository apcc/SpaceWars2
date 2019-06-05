#include "./Player.hpp"
#include "../CommonData.hpp"
#define PLAYER_SPEED 15
#define GAUGE_LIMIT 1000.0
#define GAUGE_WIDTH (Window::Center().x / GAUGE_LIMIT)

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
	mainSkillCnt = 0;
	subSkillCnt = 0;
	specialSkillCnt = 0;

	GamePad::SetAxis();
	GamePad::SetButton();

	HPLog.clear();

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
	if (hitSize == 30) {	// hitSize is default
		HP -= _damage;
		if(!inRecovery)
			charge += _damage;
		if (charge >= requireCharge[whatSpecialSkill]) {
			charge = requireCharge[whatSpecialSkill];
		}
	}
	else {
		shieldDamage += _damage;
	}
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
		if (pos.x > Window::Center().x - PLAYER_SIZE)
			pos.x = Window::Center().x - PLAYER_SIZE;
	} else {
		if (pos.x < Window::Center().x + PLAYER_SIZE)
			pos.x = Window::Center().x + PLAYER_SIZE;
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
	}

	if (!inJudgmentTime) {
		for (auto i : bullets) {
			if (isLeft == i->isLeft) continue;
			int damage = i->getDamage(this->hitCircle());
			if (damage) {
				this->receiveDamage(damage);
			}
		}
	}

	HPLog.push_back(HP);
}

bool Player::skillSelect() {

	bool returnFlag = false;

	if (selectedType != 2) {
		if (KeyRight.repeat(20, true)) {
			++selectedType;
			returnFlag = true;
		}
	}
	if (selectedType != 0) {
		if (KeyLeft.repeat(20, true)) {
			--selectedType;
			returnFlag = true;
		}
	}
	int numberOfSkill[3] = { MAIN_NUM, SUB_NUM, SPECIAL_NUM };
	int skills[3] = { whatMainSkill, whatSubSkill, whatSpecialSkill };
	if (skills[selectedType] > 0) {
		if (KeyUp.repeat(20, true)) {
			--skills[selectedType];
			returnFlag = true;
		}
	}if (skills[selectedType] < numberOfSkill[selectedType]-1) {
		if (KeyDown.repeat(20, true)) {
			++skills[selectedType];
			returnFlag = true;
		}
	}
	whatMainSkill = (MainSkill)skills[0];
	whatSubSkill = (SubSkill)skills[1];
	whatSpecialSkill = (SpecialSkill)skills[2];

	return returnFlag;
}
void Player::drawShip(){
	if(isLeft){
		circle().draw(Color(L"#ff0000"));
	}else{
		circle().draw(Color(L"#0000ff"));
	}
}

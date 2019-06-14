#include "./Player.hpp"
#include "../CommonData.hpp"
#define PLAYER_SPEED 8
#define GAUGE_LIMIT 1000.0
#define GAUGE_WIDTH (Window::Center().x / GAUGE_LIMIT)

bool Player::inJudgmentTime = false;

void Player::init(Vec2 _pos, bool _isLeft) {
	pos             = _pos;
	isLeft          = _isLeft;
	HP              = 1000;
	temperature     = 100;
	coolDownTime    = 0;
	charge          = 0;
	recoveryDamage  = 0;
	speed           = PLAYER_SPEED;
	inAbsorption    = false;
	mainSkillCnt    = 0;
	subSkillCnt     = 0;
	specialSkillCnt = 0;
	selectedType    = 0;

	HPLog.clear();

	GamePad::SetAxis();
	GamePad::SetButton();
	KeyUp           = KeyRepeat(isLeft, L"KeyUp");
	KeyLeft         = KeyRepeat(isLeft, L"KeyLeft");
	KeyDown         = KeyRepeat(isLeft, L"KeyDown");
	KeyRight        = KeyRepeat(isLeft, L"KeyRight");
	KeyMainSkill    = KeyRepeat(isLeft, L"MainSkill");
	KeySubSkill     = KeyRepeat(isLeft, L"SubSkill");
	KeySpecialSkill = KeyRepeat(isLeft, L"SpecialSkill");
}

void Player::initSkill() {
	whatMainSkill = static_cast<MainSkill>(0);
	whatSubSkill = static_cast<SubSkill>(0);
	whatSpecialSkill = static_cast<SpecialSkill>(0);
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
		if (!inAbsorption) {
			charge += _damage;
			recoveryDamage = 0;
		}
		else {
			recoveryDamage += _damage;
			if (HP < 5)
				HP = 5;
		}

		if (charge >= requireCharge[whatSpecialSkill]) {
			charge = requireCharge[whatSpecialSkill];
		}
	}
	else {
		shieldDamage += _damage;
	}
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

	isMoving = (pos != pos + GamePad::Move(isLeft, speed));
	pos += GamePad::Move(isLeft, speed);

	howFrameAfterShooting++;

	pos = Clamp(pos,
				{
					(isLeft ? PLAYER_SIZE : Window::Center().x + PLAYER_SIZE),
					PLAYER_SIZE
				},
				{
					(isLeft ? Window::Center().x - PLAYER_SIZE : Window::Width() - PLAYER_SIZE),
					Window::Height() - PLAYER_SIZE
				}
		  );

	if (howFrameAfterShooting >= 60) {
		temperature -= 5;
	}

	if (speed != 0) { // [自機] normal
		if (temperature < 800) doMainSkill(bullets);
		if (coolDownTime == 0) doSubSkill(bullets); else coolDownTime--;
		doSpacialSkill(bullets);
	}

	if (inJudgmentTime) { // [全体] J.T.
		if (judgmentLife == 0) {
			inJudgmentTime = false;
		}
		--judgmentLife;
	}
	else { // [全体] normal
		for (auto i : bullets) {
			if (isLeft == i->isLeft) continue;
			int damage = i->getDamage(this->hitCircle());
			if (damage) {
				this->receiveDamage(damage);
			}
		}
	}

	if (floor(charge / requireCharge[whatSpecialSkill] * 100) == 100) {
		if (!isSounded) {
			SoundAsset(L"chargeFull").setVolume(Config::MASTER_VOLUME * Config::EFFECT_VOLUME);
			SoundAsset(L"chargeFull").playMulti();
			isSounded = true;
		}
	}
	else
		isSounded = false;

	HP           = Clamp(HP,           0,   1000);
	temperature  = Clamp(temperature,  100, 1000);
	coolDownTime = Clamp(coolDownTime, 0,   1000);
	charge       = Clamp(charge,       0,   1000);

	HPLog.push_back(HP);
}

bool Player::skillSelect() {
	bool returnFlag = false;

	if (selectedType != 2) {
		if (
			KeyRight.repeat(20, true) ||
			 (isLeft ? Data::LKeySelect.repeat(20, true) : Data::RKeySelect.repeat(20, true))
			) {
			++selectedType;
			returnFlag = true;
		}
	}
	if (selectedType != 0) {
		if (
			KeyLeft.repeat(20, true) ||
			 (isLeft ? Data::LKeyCancel.repeat(20, true) : Data::RKeyCancel.repeat(20, true))
			) {
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

	if (returnFlag){
		SoundAsset(L"cursor1").setVolume(Config::MASTER_VOLUME * Config::CURSOR_VOLUME);
		SoundAsset(L"cursor1").playMulti();
	}

	return returnFlag;
}
void Player::drawShip(){
	const String name = isLeft ? L"l" : L"r";
	TextureAsset(name + L"-player").drawAt(pos);

	if (isMoving) {
		if (isLeft) {
			TextureAsset(L"fire").drawAt(pos + Vec2(-60, 0));
		}
		else {
			TextureAsset(L"fire").mirror().drawAt(pos + Vec2(60, 0));
		}
	}
}

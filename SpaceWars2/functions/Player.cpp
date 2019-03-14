#include "./Player.hpp"

#define PLAYER_SPEED 15
#define NUMBER_OF_SKILL 3
#define HP_LIMIT 100.0
#define GAUGE_WIDTH (Config::Width / 2.0 / HP_LIMIT)

void Player::Init(Vec2 p, bool _isLeft){
	pos = p;
	isLeft = _isLeft;
	HP = 100;
	temperature = 0;
	charge = 0;
	coolDown = 0;
	whatMainSkill = static_cast<MainSkill>(0);
	whatSubSkill = static_cast<SubSkill>(0);
	whatSpecialSkill = static_cast<SpecialSkill>(0);
}

Circle Player::circle(){
	return Circle(pos, 30);
}

void Player::receiveDamage(int damage){
	HP -= damage;
	if (HP < 0) HP = 0;
}

bool Player::isHPRunOut(){
	if(HP == 0){
		return true;
	}else{
		return false;
	}
}

void Player::Update(std::vector<Bullet*> &bullets){
	Rect zone;
	Vec2 tmp = pos;
	if(isLeft){
		zone = Rect(0, 0, Config::Width / 2 + 1, Config::Height + 1);
		if(Input::KeyD.pressed)			pos.x += PLAYER_SPEED;
		if(Input::KeyA.pressed)			pos.x -= PLAYER_SPEED;
		if (zone.contains(Player::circle()) == false)
			pos = tmp;
		tmp = pos;
		if(Input::KeyW.pressed)			pos.y -= PLAYER_SPEED;
		if(Input::KeyS.pressed)			pos.y += PLAYER_SPEED;
		if (zone.contains(Player::circle()) == false)
			pos = tmp;
		tmp = pos;
	}else{
		zone = Rect(Config::Width/2, 0, Config::Width / 2 + 1, Config::Height + 1);
		if(Input::KeySemicolon.pressed)	pos.x += PLAYER_SPEED;
		if(Input::KeyK.pressed)			pos.x -= PLAYER_SPEED;
		if (zone.contains(Player::circle()) == false)
			pos = tmp;
		tmp = pos;
		if(Input::KeyO.pressed)			pos.y -= PLAYER_SPEED;
		if(Input::KeyL.pressed)			pos.y += PLAYER_SPEED;
		if (zone.contains(Player::circle()) == false)
			pos = tmp;
		tmp = pos;
	}
	//pos.x=max(tmpZoon.x)


	if(isLeft){
		if(Input::KeyQ.pressed)			DoMainSkill(bullets);
		if(Input::KeyE.pressed)			DoSubSkill(bullets);
		if(Input::KeyLShift.pressed)	DoSpacialSkill(bullets);
	}else{
		if(Input::KeyI.pressed)			DoMainSkill(bullets);
		if(Input::KeyP.pressed)			DoSubSkill(bullets);
		if(Input::KeyRShift.pressed)	DoSpacialSkill(bullets);
	}

	for (auto i : bullets) {
		if(isLeft == i->isLeft) continue;
		int damage = i->getDamage(this->circle());
		if(damage){
			this->receiveDamage(damage);
			charge+=damage;
			if(charge>= requireCharge[whatSpecialSkill]){
				charge = requireCharge[whatSpecialSkill];
			}
		}

	}
}

void Player::SkillSelect(){

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

void Player::DrawShip(){
	if(isLeft){
		circle().draw(Color(L"#ff0000"));
	}else{
		circle().draw(Color(L"#0000ff"));
	}
}

void Player::DrawGauge(){
	if(isLeft){
		RectF(0, 0,  HP * GAUGE_WIDTH, 20).draw(Color(L"#ff0000"));
		RectF(0, 20, temperature * GAUGE_WIDTH, 20).draw(Color(L"#00ff00"));
		RectF(0, 40, (charge*100) / requireCharge[whatSpecialSkill] * GAUGE_WIDTH, 20).draw(Color(L"#ffff00"));
		RectF(0, 60, coolDown * GAUGE_WIDTH, 20).draw(Color(L"#0000ff"));
	}else{
		RectF(Config::Width - HP * GAUGE_WIDTH, 0,  Config::Width, 20).draw(Color(L"#ff0000"));
		RectF(Config::Width - temperature * GAUGE_WIDTH, 20, Config::Width, 20).draw(Color(L"#00ff00"));
		RectF(Config::Width - (charge*100) / requireCharge[whatSpecialSkill] * GAUGE_WIDTH, 40, Config::Width, 20).draw(Color(L"#ffff00"));
		RectF(Config::Width - coolDown * GAUGE_WIDTH, 20, Config::Width, 80).draw(Color(L"#0000ff"));
	}
}

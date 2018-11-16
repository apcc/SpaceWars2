#pragma once
#include "Player.hpp"

#define PLAYER_SPEED 10
#define NUMBER_OF_SKILL 3
#define HP_LIMIT 100.0
#define GAUGE_WIDTH (Config::Width / 2.0 / HP_LIMIT)


void Player::DoMainSkill(){
	switch(this->whatMainSkill){
		case SHOT:
			Player::Shot();
		break;

		case GRENADE:
			Player::Grenade();
		break;

		case LASER:
			Player::Laser();
		break;

		case CRUSHER:
			Player::Crusher();
		break;

		default:
		LOG(L"[ERROR] MainSkillで意図しない値が参照されました。");
	}
}

void Player::DoSubSkill(){
	switch(this->whatSubSkill){
		case JUMP:
			Player::Jump();
		break;

		case SHIELD:
			Player::Shield();
		break;

		case MISSILE:
			Player::Missile();
		break;

		case BOMB:
			Player::Bomb();
		break;

		default:
		LOG(L"[ERROR] SubSkillで意図しない値が参照されました。");
	}
}

void Player::DoSpacialSkill(){
	switch(this->whatSpecialSkill){
		case JUDGEMENT_TIME:
			Player::JudgementTime();
		break;

		case LOCK_ON:
			Player::LockOn();
		break;

		case SUMMON_PARTNER:
			Player::SummonPartner();
		break;

		case INVERESION_RECOVERY:
			Player::InversionRecovery();
		break;

		default:
		LOG(L"[ERROR] SpecialSkillで意図しない値が参照されました。");
	}
}

void Player::Init(int32 _x, int32 _y, bool _isLeft){	
	posX = _x;
	posY = _y;
	isLeft = _isLeft;
	HP = 100;
	temperature = 0;
	charge = 0;
	coolDown = 0;
}

void Player::Control(){
	Rect tmpZoon;

	if(isLeft){
		tmpZoon = Rect(0, 0, Config::Width / 2 + 1, Config::Height + 1);
		if(Input::KeyD.pressed && tmpZoon.contains(Circle(posX + PLAYER_SPEED, posY, 40)))			posX += PLAYER_SPEED;
		if(Input::KeyA.pressed && tmpZoon.contains(Circle(posX - PLAYER_SPEED, posY, 40)))			posX -= PLAYER_SPEED;
		if(Input::KeyW.pressed && tmpZoon.contains(Circle(posX, posY - PLAYER_SPEED, 40)))			posY -= PLAYER_SPEED;
		if(Input::KeyS.pressed && tmpZoon.contains(Circle(posX, posY + PLAYER_SPEED, 40)))			posY += PLAYER_SPEED;
	}else{
		tmpZoon = Rect(Config::Width/2, 0, Config::Width / 2 + 1, Config::Height + 1);
		if(Input::KeySemicolon.pressed && tmpZoon.contains(Circle(posX + PLAYER_SPEED, posY, 40)))	posX += PLAYER_SPEED;
		if(Input::KeyK.pressed && tmpZoon.contains(Circle(posX - PLAYER_SPEED, posY, 40)))			posX -= PLAYER_SPEED;
		if(Input::KeyO.pressed && tmpZoon.contains(Circle(posX, posY - PLAYER_SPEED, 40)))			posY -= PLAYER_SPEED;
		if(Input::KeyL.pressed && tmpZoon.contains(Circle(posX, posY + PLAYER_SPEED, 40)))			posY += PLAYER_SPEED;
	}
	ship = Circle(posX, posY, 40);
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
		ship.draw(Color(L"#ff0000"));
	}else{
		ship.draw(Color(L"#0000ff"));
	}
}

void Player::DrawGauge(){
	if(isLeft){
		RectF(0, 0,  HP * GAUGE_WIDTH, 20).draw(Color(L"#ff0000"));
		RectF(0, 20, temperature * GAUGE_WIDTH, 40).draw(Color(L"#00ff00"));
		RectF(0, 40, charge * GAUGE_WIDTH, 60).draw(Color(L"#ffff00"));
		RectF(0, 60, coolDown * GAUGE_WIDTH, 80).draw(Color(L"#0000ff"));
	}else{
		RectF(Config::Width - HP * GAUGE_WIDTH, 0,  Config::Width, 20).draw(Color(L"#ff0000"));
		RectF(Config::Width - temperature * GAUGE_WIDTH, 20, Config::Width, 40).draw(Color(L"#00ff00"));
		RectF(Config::Width - charge * GAUGE_WIDTH, 40, Config::Width, 60).draw(Color(L"#ffff00"));
		RectF(Config::Width - coolDown * GAUGE_WIDTH, 60, Config::Width, 80).draw(Color(L"#0000ff"));
	}
}

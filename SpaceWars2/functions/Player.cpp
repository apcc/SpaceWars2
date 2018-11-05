#pragma once
#include "Player.hpp"

#define PLAYER_SPEED 10

void Player::DoMainSkill(){
	switch(this->whatMainSKill){
		case Shot:

		break;

		case Grenade:

		break;

		case Laser:

		break;

		case Crusher:

		break;

		default:
		LOG(L"[ERROR] MainSkillで意図しない値が参照されました。");
	}
}

void Player::DoSubSkill(){
	switch(this->whatSubSkill){
		case Jump:

		break;

		case Shield:

		break;

		case Missile:

		break;

		case Bomb:

		break;

		default:
		LOG(L"[ERROR] SubSkillで意図しない値が参照されました。");
	}
}

void Player::DoSpacialSkill(){
	switch(this->whatSpecialSKill){
		case JudgmentTime:

		break;

		case LockOn:

		break;

		case SummonPartner:

		break;

		case InversionRecovery:

		break;

		default:
		LOG(L"[ERROR] SpecialSkillで意図しない値が参照されました。");
	}
}

void Player::Init(int32 _x, int32 _y, bool _isLeft){	
	posX = _x;
	posY = _y;
	isLeft = _isLeft;
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

void Player::DrawShip(){
	if(isLeft){
		ship.draw(Color(L"#ff0000"));
	}else{
		ship.draw(Color(L"#0000ff"));
	}
}

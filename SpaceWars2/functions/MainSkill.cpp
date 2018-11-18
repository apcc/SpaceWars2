#pragma once

#include "./Player.hpp"


void Player::DoMainSkill(){
	switch(this->whatMainSkill){
		case SHOT:
		break;

		case GRENADE:
		break;

		case LASER:
		break;

		case CRUSHER:
		break;

		default:
		LOG(L"[ERROR] DoMainSkillで意図しない値が参照されました。");
	}
}

void Player::UpdateMainSkill(){
	switch(this->whatMainSkill){
		case SHOT:
		break;

		case GRENADE:
		break;

		case LASER:
		break;

		case CRUSHER:
		break;

		default:
		LOG(L"[ERROR] UpdateMainSkillで意図しない値が参照されました。");
	}
}

void Player::DrawMainSkill(){
	switch(this->whatMainSkill){
		case SHOT:
		break;

		case GRENADE:
		break;

		case LASER:
		break;

		case CRUSHER:
		break;

		default:
		LOG(L"[ERROR] DrawMainSkillで意図しない値が参照されました。");
	}
}

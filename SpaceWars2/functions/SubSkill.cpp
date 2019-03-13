#include "./Player.hpp"


void Player::doSubSkill(std::vector<Bullet*>& bullets){
	switch(this->whatSubSkill){
		case JUMP:
		break;

		case SHIELD:
		break;

		case MISSILE:
		break;

		case BOMB:
		break;

		default:
		LOG(L"[ERROR] doSubSkillで意図しない値が参照されました。");
	}
}

void Player::updateSubSkill(){
	switch(this->whatSubSkill){
		case JUMP:
		break;

		case SHIELD:
		break;

		case MISSILE:
		break;

		case BOMB:
		break;

		default:
		LOG(L"[ERROR] updateSubSkillで意図しない値が参照されました。");
	}
}

void Player::drawSubSkill(){
	switch(this->whatSubSkill){
		case JUMP:
		break;

		case SHIELD:
		break;

		case MISSILE:
		break;

		case BOMB:
		break;

		default:
		LOG(L"[ERROR] drawSubSkillで意図しない値が参照されました。");
	}
}

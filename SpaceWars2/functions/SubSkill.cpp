#include "./Player.hpp"


void Player::DoSubSkill(std::vector<Bullet*>& bullets){
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
		LOG(L"[ERROR] DoSubSkillで意図しない値が参照されました。");
	}
}

void Player::UpdateSubSkill(){
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
		LOG(L"[ERROR] UpdateSubSkillで意図しない値が参照されました。");
	}
}

void Player::DrawSubSkill(){
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
		LOG(L"[ERROR] DrawSubSkillで意図しない値が参照されました。");
	}
}

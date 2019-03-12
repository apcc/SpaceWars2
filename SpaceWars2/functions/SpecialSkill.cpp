#include "./Player.hpp"


void Player::DoSpacialSkill(std::vector<Bullet*>& bullets){
	switch(this->whatSpecialSkill){
		case JUDGMENT_TIME:
		break;

		case LOCK_ON:
		break;

		case SUMMON_PARTNER:
		break;

		case INVERSION_RECOVERY:
		break;

		default:
		LOG(L"[ERROR] DoSpecialSkillで意図しない値が参照されました。");
	}
}

void Player::UpdateSpecialSkill(){
	switch(this->whatSpecialSkill){
		case JUDGMENT_TIME:
		break;

		case LOCK_ON:
		break;

		case SUMMON_PARTNER:
		break;

		case INVERSION_RECOVERY:
		break;

		default:
		LOG(L"[ERROR] UpdateSpecialSkillで意図しない値が参照されました。");
	}
}

void Player::DrawSpecialSkill(){
	switch(this->whatSpecialSkill){
		case JUDGMENT_TIME:
		break;

		case LOCK_ON:
		break;

		case SUMMON_PARTNER:
		break;

		case INVERSION_RECOVERY:
		break;

		default:
		LOG(L"[ERROR] DrawSpecialSkillで意図しない値が参照されました。");
	}
}

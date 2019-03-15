#include "./Player.hpp"
#include "../skills/LockOn.hpp"


void Player::DoSpacialSkill(std::vector<Bullet*>& bullets){
	if(charge >= this->requireCharge[whatSpecialSkill]){
		switch(this->whatSpecialSkill){
			case JUDGEMENT_TIME:
			break;
			case LOCK_ON:
			for(int i=0; i<3; i++){
				bullets.push_back(new LockOn(pos, isLeft, 30*i));
			}
			break;

			case SUMMON_PARTNER:
			break;

			case INVERESION_RECOVERY:
			break;

			default:
			LOG(L"[ERROR] DoSpecialSkillで意図しない値が参照されました。");
		}
		charge = 0;
	}
}

void Player::UpdateSpecialSkill(){
	switch(this->whatSpecialSkill){
		case JUDGEMENT_TIME:
		break;

		case LOCK_ON:
		break;

		case SUMMON_PARTNER:
		break;

		case INVERESION_RECOVERY:
		break;

		default:
		LOG(L"[ERROR] UpdateSpecialSkillで意図しない値が参照されました。");
	}
}

void Player::DrawSpecialSkill(){
	switch(this->whatSpecialSkill){
		case JUDGEMENT_TIME:
		break;

		case LOCK_ON:
		break;

		case SUMMON_PARTNER:
		break;

		case INVERESION_RECOVERY:
		break;

		default:
		LOG(L"[ERROR] DrawSpecialSkillで意図しない値が参照されました。");
	}
}

#include "./Player.hpp"
#include "../skills/LockOn.hpp"


void Player::doSpacialSkill(std::vector<Bullet*>& bullets){
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
			LOG(L"[ERROR] doSpecialSkillで意図しない値が参照されました。");
		}
		charge = 0;
	}
}

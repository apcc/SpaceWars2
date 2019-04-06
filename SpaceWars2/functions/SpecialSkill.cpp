#include "./Player.hpp"
#include "../skills/LockOn.hpp"
#include "../skills/SummonPartner.hpp"
#include "../skills/JudgmentTime.hpp"
#include "../skills/InversionRecovery.hpp"

void Player::doSpacialSkill(std::vector<Bullet*>& bullets){
	if(charge >= this->requireCharge[whatSpecialSkill] && KeySpecialSkill.repeat(0)){
		switch(this->whatSpecialSkill){
		case JUDGMENT_TIME:
			bullets.push_back(new JudgmentTime(pos, isLeft));
			break;

		case LOCK_ON:
			for(int i=0; i<3; i++){
				bullets.push_back(new LockOn(pos, isLeft, 30*i));
			}
			break;

		case SUMMON_PARTNER:
				bullets.push_back(new SummonPartner(pos, isLeft));
			break;

		case INVERSION_RECOVERY:
			bullets.push_back(new InversionRecovery(pos, isLeft));
			break;

		default:
			LOG(L"[ERROR] doSpecialSkillで意図しない値が参照されました。");
		}
		charge = 0;
	}
}

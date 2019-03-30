#include "./Player.hpp"


void Player::doSpacialSkill(std::vector<Bullet*>& bullets){
	switch(this->whatSpecialSkill){
	case JUDGMENT_TIME:
		if (KeySubSkill.repeat(0))
			
		break;

	case LOCK_ON:
		if (KeySubSkill.repeat(0))

		break;

	case SUMMON_PARTNER:
		if (KeySubSkill.repeat(0))

		break;

	case INVERSION_RECOVERY:
		if (KeySubSkill.repeat(0))
			
		break;

	default:
		LOG(L"[ERROR] doSpecialSkillで意図しない値が参照されました。");
	}
}

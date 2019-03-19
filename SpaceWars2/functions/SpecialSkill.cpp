#include "./Player.hpp"


void Player::doSpacialSkill(std::vector<Bullet*>& bullets){
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
		LOG(L"[ERROR] doSpecialSkillで意図しない値が参照されました。");
	}
}

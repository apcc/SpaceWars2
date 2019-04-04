#include "./Player.hpp"
#include "../skills/Jump.hpp"
#include "../skills/Shield.hpp"
#include "../skills/Missile.hpp"


void Player::doSubSkill(std::vector<Bullet*>& bullets){
	switch(this->whatSubSkill){
	case JUMP:
		if (KeySubSkill.repeat(50))
			bullets.push_back(new Jump(pos, isLeft));
		break;

	case SHIELD:
		if (KeySubSkill.repeat(10))
			bullets.push_back(new Shield(pos, isLeft));
		break;

	case MISSILE:
		if (KeySubSkill.repeat(30))
			bullets.push_back(new Missile(pos, isLeft));
		break;

	case BOMB:
		if (KeySubSkill.repeat(0))

		break;

	default:
		LOG_ERROR(L"doSubSkillで意図しない値が参照されました。");
	}
}

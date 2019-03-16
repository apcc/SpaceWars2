#include "./Player.hpp"
#include "../skills/Jump.hpp"


void Player::doSubSkill(std::vector<Bullet*>& bullets){
	switch(this->whatSubSkill){
		case JUMP:
		if (System::FrameCount() % 90 == 0)
			bullets.push_back(new Jump(pos, isLeft));
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

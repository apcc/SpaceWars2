#include "./Player.hpp"
#include "../skills/Shot.hpp"

void Player::DoMainSkill(std::vector<Bullet*>& bullets){
	switch(this->whatMainSkill){
		case SHOT:
			if(System::FrameCount() % 5 == 0)
				bullets.push_back(new Shot(pos, isLeft));
		break;

		case GRENADE:
		break;

		case LASER:
		break;

		case CRUSHER:
		break;

		default:
		LOG(L"[ERROR] DoMainSkillで意図しない値が参照されました。");
	}
}

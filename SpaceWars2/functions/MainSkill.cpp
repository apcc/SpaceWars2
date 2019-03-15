#include "./Player.hpp"
#include "../skills/Shot.hpp"
#include "../skills/Grenade.hpp"
#include "../skills/Bullet.hpp"
#include "../skills/Laser.hpp"


void Player::doMainSkill(std::vector<Bullet*>& bullets){
	switch(this->whatMainSkill){
		case SHOT:
			if(System::FrameCount() % 5 == 0)
				bullets.push_back(new Shot(pos, isLeft));
		break;

		case GRENADE:
			if(System::FrameCount() % 20 == 0)
				bullets.push_back(new Grenade(pos, isLeft));
		break;

		case LASER:
			bullets.push_back(new Laser(pos, isLeft));
		break;

		case CRUSHER:
		break;

		default:
		LOG(L"[ERROR] doMainSkillで意図しない値が参照されました。");
	}
}

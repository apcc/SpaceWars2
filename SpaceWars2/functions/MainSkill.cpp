#include "./Player.hpp"
#include "../skills/Shot.hpp"
#include "../skills/Grenade.hpp"
#include "../skills/Bullet.hpp"
#include "../skills/Laser.hpp"
#include "../skills/Homing.hpp"
#include "../skills/Reflection.hpp"
#include "../skills/Flame.hpp"


void Player::DoMainSkill(std::vector<Bullet*>& bullets){
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

		case HOMING:
			if (System::FrameCount() % 10 == 0)
				bullets.push_back(new Homing(pos, isLeft));
		break;
		case REFLECTION:
			if (System::FrameCount() % 30 == 0)
				bullets.push_back(new Reflection(pos, isLeft));
		break;
		case FLAME:
			if (System::FrameCount() % 40 == 0)
				bullets.push_back(new Flame(pos, isLeft));
		break;
		default:
		LOG(L"[ERROR] DoMainSkillで意図しない値が参照されました。");
	}
}

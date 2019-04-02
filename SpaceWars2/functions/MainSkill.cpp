#include "./Player.hpp"
#include "../skills/Shot.hpp"
#include "../skills/Grenade.hpp"
#include "../skills/Bullet.hpp"
#include "../skills/Laser.hpp"
#include "../skills/Homing.hpp"
#include "../skills/Reflection.hpp"
#include "../skills/Flame.hpp"

void Player::doMainSkill(std::vector<Bullet*>& bullets){
	switch(this->whatMainSkill){
	case SHOT:
		if (KeyMainSkill.repeat(5)) {
			bullets.push_back(new Shot(pos, isLeft));
			temperature += 5;
		}
		break;

	case GRENADE:
		if (KeyMainSkill.repeat(20)) {
			bullets.push_back(new Grenade(pos, isLeft));
			temperature += 8;
		}
		break;

	case LASER:
		if (KeyMainSkill.repeat(0)) {
			bullets.push_back(new Laser(pos, isLeft));
			temperature += 4;
		}
		break;

	case CRUSHER:
		break;

	case HOMING:
		if (KeyMainSkill.repeat(10)) {
			bullets.push_back(new Homing(pos, isLeft));
			temperature += 10;
		}
		break;

	case REFLECTION:
		if (KeyMainSkill.repeat(30)) {
			bullets.push_back(new Reflection(pos, isLeft));
			temperature += 8;
		}
		break;

	case FLAME:
		if (KeyMainSkill.repeat(20)) {
			bullets.push_back(new Flame(pos, isLeft));
			temperature += 5;
		}
		break;

	default:
		LOG_ERROR(L"doMainSkillで意図しない値が参照されました。");
	}
}

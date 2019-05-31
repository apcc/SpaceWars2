#include "./Player.hpp"
#include "../skills/Jump.hpp"
#include "../skills/Shield.hpp"
#include "../skills/Missile.hpp"
#include "../skills/Bomb.hpp"

void Player::doSubSkill(std::vector<Bullet*>& bullets){
	if(KeySubSkill.repeat(0)){
		switch(this->whatSubSkill){
		case JUMP:
			if (GamePad::Move(isLeft, 1) != Vec2(0, 0)) {
				bullets.push_back(new Jump(pos, isLeft));
				coolDownTime = 250;
				++subSkillCnt;
			}
			break;

		case SHIELD:
			bullets.push_back(new Shield(pos, isLeft));
			coolDownTime = 600;
			++subSkillCnt;
			break;

		case MISSILE:
			bullets.push_back(new Missile(pos, isLeft));
			coolDownTime = 50;
			++subSkillCnt;
			break;

		case BOMB:
			for (int i = 0; i < 4; i++)
				bullets.push_back(new Bomb(pos, isLeft));
			coolDownTime = 500;
			++subSkillCnt;
			break;

		default:
			LOG_ERROR(L"doSubSkillで意図しない値が参照されました。");
		}
	}

}

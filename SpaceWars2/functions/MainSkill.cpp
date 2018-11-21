#pragma once

#include "./MainSkill.hpp"
#include "./Player.hpp"
#include "../skills/Shot.hpp"

void Player::DoMainSkill(){
	switch(this->whatMainSkill){
		case SHOT:
			if(System::FrameCount() % 8 == 0)
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

void Player::UpdateMainSkill(Circle rivalCircle){
	switch(this->whatMainSkill){
		case SHOT:
			for(auto itr = bullets.begin(); itr != bullets.end();){
				(**itr).update(rivalCircle);
				if (!Circle((**itr).pos, 10).intersects(Rect(0, 0, Config::Width + 1, Config::Height + 1))){
					delete *itr;
					itr = bullets.erase(itr);
				}else{
					itr++;
				}
			}
		break;

		case GRENADE:
		break;

		case LASER:
		break;

		case CRUSHER:
		break;

		default:
		LOG(L"[ERROR] UpdateMainSkillで意図しない値が参照されました。");
	}
}

void Player::DrawMainSkill(){
	for(auto bul : bullets){
		bul->draw();
	}
}

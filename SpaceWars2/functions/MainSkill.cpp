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

int Player::UpdateMainSkill(Circle rivalCircle){
	int damage = 0;
	switch(this->whatMainSkill){
		case SHOT:
			for(auto itr = bullets.begin(); itr != bullets.end();){
				(**itr).update();
				if(!Circle((**itr).pos, 8).intersects(Rect(0, 0, Config::Width + 1, Config::Height + 1))){
					// ウィンドウからのはみ出し
					delete *itr;
					itr = bullets.erase(itr);
				}else if(rivalCircle.intersects(Circle((**itr).pos, 8))){
					// 敵Playerへのダメージ
					delete *itr;
					itr = bullets.erase(itr);
					damage += 2;
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
	return damage;
}

void Player::DrawMainSkill(){
	for(auto bul : bullets){
		bul->draw();
	}
}
